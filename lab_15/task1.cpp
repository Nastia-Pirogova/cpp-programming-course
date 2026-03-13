#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Individual {
    double x1;
    double x2;
    double fitness;
};

double objectiveFunction(double x1, double x2) {
    return x2 - x1 * x1 + 4 * x1;
}

bool isValid(double x1, double x2) {
    return (2 * x1 + 3 * x2 <= 30 &&
            x1 + 2 * x2 <= 15 &&
            x1 >= 0 &&
            x2 >= 0);
}

double randomDouble(double minVal, double maxVal) {
    return minVal + (double)rand() / RAND_MAX * (maxVal - minVal);
}

Individual createIndividual() {
    Individual ind;
    ind.x1 = randomDouble(0.0, 15.0);
    ind.x2 = randomDouble(0.0, 15.0);

    if (isValid(ind.x1, ind.x2))
        ind.fitness = objectiveFunction(ind.x1, ind.x2);
    else
        ind.fitness = -1000000.0;

    return ind;
}

int main() {
    srand((unsigned)time(0));

    const int POP_SIZE = 1000;
    const int GENERATIONS = 200;
    const double MUTATION_RATE = 0.1;

    vector<Individual> population;

    for (int i = 0; i < POP_SIZE; i++) {
        population.push_back(createIndividual());
    }

    Individual best = population[0];

    for (int gen = 0; gen < GENERATIONS; gen++) {
        vector<Individual> newPopulation;

        for (int i = 0; i < POP_SIZE; i++) {
            Individual parent1 = population[rand() % POP_SIZE];
            Individual parent2 = population[rand() % POP_SIZE];

            Individual child;
            child.x1 = (parent1.x1 + parent2.x1) / 2.0;
            child.x2 = (parent1.x2 + parent2.x2) / 2.0;

            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                child.x1 += randomDouble(-0.5, 0.5);
                child.x2 += randomDouble(-0.5, 0.5);
            }

            if (child.x1 < 0) child.x1 = 0;
            if (child.x2 < 0) child.x2 = 0;

            if (isValid(child.x1, child.x2))
                child.fitness = objectiveFunction(child.x1, child.x2);
            else
                child.fitness = -1000000.0;

            newPopulation.push_back(child);

            if (child.fitness > best.fitness) {
                best = child;
            }
        }

        population = newPopulation;
    }

    cout << fixed << setprecision(4);
    cout << "Найкращий знайдений розв'язок:" << endl;
    cout << "x1 = " << best.x1 << endl;
    cout << "x2 = " << best.x2 << endl;
    cout << "f(x1, x2) = " << best.fitness << endl;

    cout << "\nТочний розв'язок для порівняння:" << endl;
    cout << "x1 = 1.7500" << endl;
    cout << "x2 = 6.6250" << endl;
    cout << "fmax = 10.5625" << endl;

    return 0;
}