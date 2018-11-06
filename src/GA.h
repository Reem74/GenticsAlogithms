#ifndef GA_H_
#define GA_H_

class GA {
public:
	int population_size;
	int chromosome_size;
	int number_of_generations;
	std::vector<std::vector<double> > chromosome;
	std::vector<double> chromosome_fitness;
	GA();
	GA(int, int, int);
	double generateRandom(double, double);
	virtual std::pair<std::vector<double>, double> run() = 0;
	virtual void evaluate() = 0;
	std::vector<int> select();
	std::vector<std::vector<double> > crossover(std::vector<int>);
	virtual std::vector<std::vector<double> > mutate(
			std::vector<std::vector<double> >, int) = 0;
	virtual double calcFitness(std::vector<double>, int) = 0;
};
#endif
