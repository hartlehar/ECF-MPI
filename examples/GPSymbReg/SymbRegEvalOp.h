#ifndef SymbRegEvalOp_h
#define SymbRegEvalOp_h


/**
 * \defgroup symbreg Symbolic regression (GP)
 * \ingroup examples
 * \brief Symbolic regression example - illustration for Tree genotype (see more on this example in help/tutorial.html)
 *
 * \par Description
 * The objective is to find a symbolic form of an unknown function (i.e. find a mapping between the given set 
 * of input and output values). 
 * The fitness is defined with total error for the given set of output values.
 * 
 * \par Tree genotype parameters (in the config file)
 * - set of functions (inner tree nodes)
 * - set of terminals (variables and constants, tree leaves)
 * - min and max tree depth
 *
 */
 
 
/**
 * \ingroup symbreg
 * \brief Symbolic regression evaluation operator.
 */
class SymbRegEvalOp : public EvaluateOp
{
public:
	struct dataRow {
		double hh, Oi, r0, dr, zz, a1;
	};

	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);
	std::vector<dataRow> domain;
	std::vector<double> codomain;
	uint nSamples;
	double yMean;
	int numThreads;

	void computeChunk(int, int, Tree::Tree*, double&, double&); 
};
typedef std::shared_ptr<SymbRegEvalOp> SymbRegEvalOpP;

#endif // SymbRegEvalOp_h
