#include <bits/stdc++.h>

#include "CurveFitting.h"
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	srand(time(NULL));
	int t;
	scanf("%d", &t);
	for (int test_case = 1; test_case <= t; ++test_case) {
		int population_size;
		int chromosome_size;
		const int number_of_generations = 200;
		population_size = 10000;
		int number_of_points;
		scanf("%d%d", &number_of_points, &chromosome_size);
		chromosome_size++;
		vector<pair<double, double> > points(number_of_points + 1);
		for (int i = 0; i < number_of_points; ++i) {
			scanf("%lf%lf", &points[i].first, &points[i].second);
		}
		CurveFitting curveFitting = CurveFitting(population_size,
				chromosome_size, number_of_generations, points);
		puts("chromosome values");
		pair<vector<double>, double> best_chromosome = curveFitting.run();
		cout << "Case " << test_case << ": \n";
		for (int i = 0; i < (int) best_chromosome.first.size(); ++i) {
			cout << "a" << i << ":" << fixed << setprecision(10)
					<< best_chromosome.first[i] << endl;
		}
		puts("Mean: ");
		cout << best_chromosome.second << endl;
	}
}
