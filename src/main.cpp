//
// Created by jbuisine on 09/08/17.
//

#include "Algorithms/Heuristics.hpp"

// Number of element
const int SOL_SIZE = 100;

// Number of iteration
const int ITERATION = 1000;

// Function of Fitness type
double compute (long ptrToParam) {

    BinaryCombinatorySolution<int>* s = (BinaryCombinatorySolution<int>*)ptrToParam;

    double c = 0.0;

    int t = s->getSize();
    for (int i = 0; i < t; ++i) {
        c += sqrt(s->getArr()[i])*sqrt(i);
    }

    return c;
}

/**
 * Hill climber best improvement example
 */
void mainHCBest() {
    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness)compute);

    Heuristics<BinaryCombinatorySolution<int>>* h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int>* s = h->HillClimberBestImprovement(ITERATION);

    cout << "Best solution found so far : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long)s) << endl;

    delete s;

    double seconds_since_start = difftime( time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec." << endl;
}

/**
 * Hill climber first improvement example
 */
void mainHCFirst() {
    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness)compute);

    Heuristics<BinaryCombinatorySolution<int>>* h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int>* s = h->HillClimberFirstImprovement(ITERATION);

    cout << "Best solution found so far : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long)s) << endl;

    delete s;

    double seconds_since_start = difftime( time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec.";
}

/**
 * Iterated local search example
 */
void mainILS() {

    const int HC_ITERATION = 1000;
    const int NB_PERTURBATION = 10;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness)compute);

    Heuristics<BinaryCombinatorySolution<int>>* h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int>* s = h->IteratedLocalSearch(ITERATION, HC_ITERATION, NB_PERTURBATION);

    cout << "Best solution found so far : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long)s) << endl;

    delete s;

    double seconds_since_start = difftime( time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec." << endl;
}

/**
 * Main function which loads all examples
 * @return
 */
int main() {

    //mainHCFirst();
    //mainHCBest();
    mainILS();

    return 0;
}
