#include <bits/stdc++.h>
#include "CurveFitting.h"

using namespace std;
CurveFitting::CurveFitting(int population_size, int chromosome_size,
		int number_of_generations, vector<pair<double, double> > points) :
		GA(population_size, chromosome_size, number_of_generations) {
	this->points = points;
}
double CurveFitting::calcFitness(vector<double> chromo, int x = 1) {
	double fitness = 0;
	for (int i1 = 0; i1 < (int) points.size(); ++i1) {
		int y_calc = 0;
		x = 1;
		for (int j = 0; j < (int) chromo.size(); ++j, x *= points[i1].first) {
			y_calc += chromo[j] * x;
		}
		fitness += pow(abs((points[i1].second - y_calc)), 2);
	}
	return (fitness / (int) points.size());
}
void CurveFitting::evaluate() {
	for (int i = 0; i < population_size; ++i) {
		chromosome_fitness[i] = calcFitness(chromosome[i]);
		///cout << chromosome_fitness[i] << endl;
	}
}
pair<vector<double>, double> CurveFitting::run() {
	evaluate();
	for (int generation_number = 0; generation_number < number_of_generations;
			++generation_number) {
		vector<int> selected_chromo_for_crossovering = select();
		vector<vector<double> > chromosomes_to_be_mututed = crossover(
				selected_chromo_for_crossovering);
		vector<vector<double> > new_generation = mutate(
				chromosomes_to_be_mututed, generation_number);
		int i = selected_chromo_for_crossovering[0], j =
				selected_chromo_for_crossovering[1];
		double val1 = calcFitness(chromosome[i]), val2 = calcFitness(
				chromosome[j]);
		double val3 = calcFitness(new_generation[0]), val4 = calcFitness(
				new_generation[1]);
		if (val1 + val2 < val3 + val4) {
			chromosome[i] = new_generation[0];
			chromosome[j] = new_generation[1];
			chromosome_fitness[i] = val1;
			chromosome_fitness[j] = val2;
		}
	}
	int best_chromosome_pos = calcBestChromosome();
	return {chromosome[best_chromosome_pos], calcFitness(chromosome[best_chromosome_pos])};
}
int CurveFitting::calcBestChromosome() {
	double mn = chromosome_fitness[0];
	int ind = 0;
	for (int i = 1; i < population_size; ++i) {
		if (chromosome_fitness[i] < mn) {
			mn = chromosome_fitness[i];
			ind = i;
		}
	}
	return ind;
}
double CurveFitting::calc_mutation_delta(double x, double gneration_number) {
	int deltaL = abs(x - (-10));
	int deltaU = abs(x - 10);
	double random_number = generateRandom(0, 1);
	int y;
	if (random_number <= 0.5)
		y = deltaL;
	else
		y = deltaU;
	double power = pow(generateRandom(0, 1),
			pow(1 - (gneration_number / number_of_generations),
					generateRandom(0.5, 5)));
	double delta = y * (1 - power);
	return (random_number <= 0.5 ? -delta : delta);
}
vector<vector<double> > CurveFitting::mutate(
		vector<vector<double> > chromosomes_to_be_mututed,
		int gneration_number) {
	for (int i = 0; i < (int) chromosomes_to_be_mututed.size(); ++i) {
		for (int j = 0; j < (int) chromosomes_to_be_mututed[i].size(); ++j) {
			chromosomes_to_be_mututed[i][j] += calc_mutation_delta(
					chromosomes_to_be_mututed[i][j], gneration_number);
		}
	}
	vector<vector<double> > muteted_chromosomes = chromosomes_to_be_mututed;
	return muteted_chromosomes;
}

