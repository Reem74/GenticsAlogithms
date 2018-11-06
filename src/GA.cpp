#include <bits/stdc++.h>
#include "GA.h"

using namespace std;

double GA::generateRandom(double low, double high) {
	return ((double) rand() / RAND_MAX) * (high - low) + low;
}
GA::GA() {
	population_size = 0;
	chromosome_size = 0;
	number_of_generations = 0;
}
GA::GA(int population_size, int chromosome_size, int number_of_generations) {
	this->population_size = population_size;
	this->chromosome_size = chromosome_size;
	this->number_of_generations = number_of_generations;

	chromosome.resize(population_size);
	chromosome_fitness.resize(population_size);
	for (int i = 0; i < population_size; ++i) {
		chromosome[i].resize(chromosome_size);
		for (int j = 0; j < chromosome_size; ++j) {
			chromosome[i][j] = generateRandom(-10, 10);
		}
	}

}

vector<int> GA::select() {
	vector<pair<double, int> > sorted_chromosome_fitness;
	sorted_chromosome_fitness.resize(population_size + 1);
	for (int i = 0; i < population_size; ++i) {
		sorted_chromosome_fitness[i] = {chromosome_fitness[i], i};
	}
	sort(sorted_chromosome_fitness.begin(), sorted_chromosome_fitness.end());
	vector<int> ret;
	ret.push_back(sorted_chromosome_fitness[0].second);
	ret.push_back(sorted_chromosome_fitness[1].second);
	return ret;
}
vector<vector<double> > GA::crossover(vector<int> selected_vals) {
	vector<vector<double> > ret;
	ret.push_back(chromosome[selected_vals[0]]);
	ret.push_back(chromosome[selected_vals[1]]);
	double random_number = generateRandom(0, 1);
	if (random_number > 0.5) {
		return ret;
	}
	int random_position = generateRandom(0, chromosome_size);
	for (int i = random_position; i < chromosome_size; ++i) {
		ret[0][i] = chromosome[selected_vals[1]][i];
		ret[1][i] = chromosome[selected_vals[0]][i];
	}
	return ret;
}
