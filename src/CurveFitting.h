#include "GA.h"
using namespace std;
class CurveFitting: GA {
public:
	vector<pair<double, double> > points;
	CurveFitting(int, int, int, vector<pair<double, double> >);
	pair<vector<double>, double> run();
	void evaluate();
	vector<vector<double> > mutate(vector<vector<double> >, int);
	double calc_mutation_delta(double, double);
	double calcFitness(vector<double> chromo, int);
	int calcBestChromosome();
};
