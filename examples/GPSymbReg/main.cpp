#include <ECF/ECF.h>
#include "SymbRegEvalOp.h"
#include <iostream>
using namespace Tree;
using namespace Primitives;

class SinH : public Primitive {
	public:

	SinH(void) {
		nArguments_ = 1;
		name_ = "sinh";
	}

	void execute(void* result, Tree::Tree& tree) {
		double& arg = *(double*)result;
		getNextArgument(&arg, tree);
		// radians as argument
		arg = sinh(arg);
	}

	~SinH() {}
};

class CosH : public Primitive {
	public:

	CosH(void) {
		nArguments_ = 1;
		name_ = "cosh";
	}

	void execute(void* result, Tree::Tree& tree) {
		double& arg = *(double*)result;
		getNextArgument(&arg, tree);
		// radians as argument
		arg = cosh(arg);
	}

	~CosH() {}
};

template <class T>
class PowerT : public Primitive
{
public:
	PowerT() {
		nArguments_ = 2;
		name_ = "power";
	}
	
	void execute(void* result, Tree::Tree& tree) {
		T first, second;
		T& p = *(T*)result;
		getNextArgument(&first, tree);
		getNextArgument(&second, tree);
		p = pow(first, second);
	}

	~PowerT() {}
};
typedef PowerT<double> Power;

class Exp : public Primitive {
	public:

	Exp(void) {
		nArguments_ = 1;
		name_ = "exp";
	}

	void execute(void* result, Tree::Tree& tree) {
		double arg;
		double& res = *(double*)result;
		getNextArgument(&arg, tree);
		res = exp(arg);
	}

	~Exp() {}
};


int main(int argc, char **argv)
{
	StateP state (new State);
	state->numThreads = 16;

	// set the evaluation operator
	state->setEvalOp(new SymbRegEvalOp);

	TreeP tree = (TreeP) new Tree::Tree;

	// sinh operator
	PrimitiveP sinH = (PrimitiveP) new SinH;
	tree->addFunction(sinH);

	// cosh operator
	PrimitiveP cosH = (PrimitiveP) new CosH;
	tree->addFunction(cosH);

	// power operator
	PrimitiveP power = (PrimitiveP) new Power;
	tree->addFunction(power);

	// exp operator
	PrimitiveP exp = (PrimitiveP) new Exp;
	tree->addFunction(exp);

	state->addGenotype(tree);

	state->initialize(argc, argv);
	state->run();

	return 0;
}
