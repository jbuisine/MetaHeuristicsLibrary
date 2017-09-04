//
// Created by jbuisine on 09/08/17.
//

#include "algorithms/Heuristics.hpp"
#include "algorithms/TabuSearch.hpp"
#include "algorithms/SimulatedAnnealing.hpp"

// Number of element
const int SOL_SIZE = 100;

// Number of iteration
const int ITERATION = 100;

// Function of Fitness type
double compute (long ptrToParam) {

    auto * s = (BinaryCombinatorySolution<int>*)ptrToParam;

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

    auto * h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int>* s = h->hillClimberBestImprovement(ITERATION);

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

    auto * h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int>* s = h->hillClimberFirstImprovement(ITERATION);

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

    auto * h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int>* s = h->iteratedLocalSearch(ITERATION, HC_ITERATION, NB_PERTURBATION);

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
 * Tabu search algorithm simple
 */
void mainTSSimple() {

    const int NB_MOVEMENT = 10;
    const int NB_PERTURBATION = 10;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *h = new TabuSearch<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int> *s = h->tabuSearchSimple(ITERATION, NB_MOVEMENT, NB_PERTURBATION);

    cout << "Best solution found so far for Tabu search simple : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long) s) << endl;
    delete s;

    double seconds_since_start = difftime(time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec." << endl;
}

/**
 * Tabu search algorithm with counter memory
 */
void mainTSCounter() {

    const int NB_MOVEMENT = 10;
    const int NB_PERTURBATION = 10;
    const int Tabu_COUNTER = 3;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *h = new TabuSearch<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int> *s = h->tabuSearchCounter(ITERATION, NB_MOVEMENT, NB_PERTURBATION, Tabu_COUNTER);

    cout << "Best solution found so far for Tabu search with counter : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long) s) << endl;
    delete s;

    double seconds_since_start = difftime(time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec." << endl;
}

/**
 * Tabu search algorithm with counter memory
 */
void mainSA() {

    const int NB_EVAL_PER_TEMP   = 100;
    const double TEMPERATURE     = 10000.0;
    const double MIN_TEMPERATURE = 0.003;
    const double DECREASE_FACTOR = 0.9;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *h = new SimulatedAnnealing<BinaryCombinatorySolution<int>>(false, f, SOL_SIZE);

    BinaryCombinatorySolution<int> *s = h->SimulatedAnnealingSimple(NB_EVAL_PER_TEMP, TEMPERATURE, MIN_TEMPERATURE, DECREASE_FACTOR);

    cout << "Best solution found so far for Simulated Annealing search : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long) s) << endl;
    delete s;

    double seconds_since_start = difftime(time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec." << endl;
}

/**
 * Main function which loads all examples
 * @return
 */
int main() {

    srand((unsigned)time(NULL));

    //mainHCFirst();
    //mainHCBest();
    //mainILS();
    //mainTSSimple();
    //mainTSCounter();
    mainSA();

    return 0;
}
