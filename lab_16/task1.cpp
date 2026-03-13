#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct Individual {
    int x;
    int y;
    int fitness;
};

int equation(int x, int y) {
    return x * x - 3 * x * y + 2 * y * y;
}

int fitnessFunction(int x, int y) {
    return abs(equation(x, y) - 3);
}

Individual createIndividual(int minVal, int maxVal) {
    Individual ind;
    ind.x = minVal + rand() % (maxVal - minVal + 1);
    ind.y = minVal + rand() % (maxVal - minVal + 1);
    ind.fitness = fitnessFunction(ind.x, ind.y);
    return ind;
}

int main() {
    srand((unsigned)time(0));

    const int POP_SIZE = 100;
    const int GENERATIONS = 500;
    const int MIN_VAL = -10;
    const int MAX_VAL = 10;
    const double MUTATION_RATE = 0.1;

    vector<Individual> population;

    for (int i = 0; i < POP_SIZE; i++) {
        population.push_back(createIndividual(MIN_VAL, MAX_VAL));
    }

    Individual best = population[0];

    for (int gen = 0; gen < GENERATIONS; gen++) {
        vector<Individual> newPopulation;

        for (int i = 0; i < POP_SIZE; i++) {
            Individual p1 = population[rand() % POP_SIZE];
            Individual p2 = population[rand() % POP_SIZE];

            Individual child;
            child.x = (p1.x + p2.x) / 2;
            child.y = (p1.y + p2.y) / 2;

            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                child.x += (rand() % 3) - 1; // -1, 0, 1
                child.y += (rand() % 3) - 1;
            }

            if (child.x < MIN_VAL) child.x = MIN_VAL;
            if (child.x > MAX_VAL) child.x = MAX_VAL;
            if (child.y < MIN_VAL) child.y = MIN_VAL;
            if (child.y > MAX_VAL) child.y = MAX_VAL;

            child.fitness = fitnessFunction(child.x, child.y);

            newPopulation.push_back(child);

            if (child.fitness < best.fitness) {
                best = child;
            }
        }

        population = newPopulation;

        if (best.fitness == 0) {
            break;
        }
    }

    cout << "Найкращий знайдений розв'язок:\n";
    cout << "x = " << best.x << endl;
    cout << "y = " << best.y << endl;
    cout << "Значення лівої частини = " << equation(best.x, best.y) << endl;
    cout << "Похибка = " << best.fitness << endl;

    if (best.fitness == 0) {
        cout << "Рівняння задовольняється.\n";
    } else {
        cout << "Точний розв'язок не знайдено, знайдено лише наближений.\n";
    }

    return 0;
}