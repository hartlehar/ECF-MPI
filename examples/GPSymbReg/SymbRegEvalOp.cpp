#include <cmath>
#include <ECF/ECF.h>
#include "SymbRegEvalOp.h"
#include <fstream>
#include <sstream>
#include <functional>

// called only once, before the evolution � generates training data
bool SymbRegEvalOp::initialize(StateP state)
{
	numThreads = state->numThreads;
	nSamples = 0;
	yMean = 0;
	std::ifstream polyFile("SR_Ana_Hartley_test_bbl_data_a1.txt", std::fstream::in);
	std::string line = "";
	getline(polyFile, line);

	while (getline(polyFile, line)) {
		nSamples++;

		std::istringstream iss(line);

		dataRow entry;

		if (iss >> entry.hh >> entry.Oi >> entry.r0 >> entry.dr >> entry.zz >> entry.a1) {
			domain.push_back(entry);
		}

		yMean += entry.a1;
	}

	yMean = yMean / nSamples;

	polyFile.close();

	return true;
}

void SymbRegEvalOp::computeChunk(int start, int end, Tree::Tree* treeCopy, double& ssTot, double& ssRes) {
	for (int i = start; i < end; ++i) {
		treeCopy->setTerminalValue("hh", &domain[i].hh);
		treeCopy->setTerminalValue("Oi", &domain[i].Oi);
		treeCopy->setTerminalValue("r0", &domain[i].r0);
		treeCopy->setTerminalValue("dr", &domain[i].dr);
		treeCopy->setTerminalValue("zz", &domain[i].zz);

		double result;
		treeCopy->execute(&result);

		ssTot += (domain[i].a1 - yMean) * (domain[i].a1 - yMean);
		ssRes += (domain[i].a1 - result) * (domain[i].a1 - result);
	}
}

FitnessP SymbRegEvalOp::evaluate(IndividualP individual)
{
	// we try to minimize the function value, so we use FitnessMin fitness (for minimization problems)
	FitnessP fitness (new FitnessMin);

	// get the genotype we defined in the configuration file
	Tree::Tree* tree = (Tree::Tree*) individual->getGenotype().get();
	// (you can also use smart pointers:)
	//TreeP tree = std::static_pointer_cast<Tree::Tree> (individual->getGenotype());

	double ssRes = 0, ssTot = 0;
	std::vector<std::thread> computeThreads;
	std::mutex mtx;
	std::vector<Tree::Tree*> treeCopies;

	int chunk = domain.size() / numThreads;
	
	for (int i=0; i < numThreads; ++i) {
		int start = i * chunk;
		int end = (i == numThreads - 1) ? domain.size() : start + chunk;

		Tree::Tree* treeCopy = tree->copy();
		treeCopies.push_back(treeCopy);

		computeThreads.emplace_back([this, start, end, treeCopy, &ssTot, &ssRes, &mtx]() {
			double local_ssTot = 0;
			double local_ssRes = 0;

			this->computeChunk(start, end, treeCopy, local_ssTot, local_ssRes);

			std::lock_guard<std::mutex> lock(mtx);
			ssTot += local_ssTot;
			ssRes += local_ssRes;
		});
	}

	for (auto& thread : computeThreads) {
		thread.join();
	}

	for (auto& tr : treeCopies) {
		delete tr;
	}

	double error = ssRes / ssTot;
	double complexity = tree->size() * 1e-10;

	fitness->setValue(error + complexity);

	return fitness;
}
