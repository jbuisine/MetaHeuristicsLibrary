//
// Created by jbuisine on 09/08/17.
//

#include "metaheuristics.h"
#include <fstream>
#include <sstream>

int nbElements;
vector<double>* profits = new vector<double>();
vector<double>* weights = new vector<double>();
int capacity;

// Fitness for knapsack problem
double compute (long ptrToParam) {

    auto * s = (BinaryCombinatorySolution<int>*)ptrToParam;

    double beta = 0.0;

    double sumProfits = 0.0;
    double sumWeights = 0.0;

    for (int i = 0; i < nbElements; ++i) {

        if(s->getArr()[i]){
            sumProfits += profits->at(i);
            sumWeights += weights->at(i);
        }

        double ratio = profits->at(i) / weights->at(i);

        if(ratio > beta){
            beta = ratio;
        }
    }

    if(sumWeights > capacity){
        sumProfits -= beta * (sumWeights - capacity);
    }

    return sumProfits;
}


/**
 * Local search example
 */
void mainLS() {

    const int ILS_ITERATION = 10000;
    const int HC_ITERATION = 100;
    const int NB_PERTURBATION = 50;
    const int K_MAX = 100;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness)compute);

    auto * ls = new MetaLocalSearch<BinaryCombinatorySolution<int>>(true, f, nbElements);

    BinaryCombinatorySolution<int>* s = ls->runILS(ILS_ITERATION,
                                                       K_MAX,
                                                       LocalSearch<BinaryCombinatorySolution<int>>::hillClimberFirstImprovement,
                                                       HC_ITERATION);

    cout << "Best solution found so far SVN Base : ";
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

    const int TSS_ITERATION = 1000;
    const int NB_MOVEMENT = 10;
    const int NB_PERTURBATION = 10;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *h = new TabuSearch<BinaryCombinatorySolution<int>>(true, f, nbElements);

    BinaryCombinatorySolution<int>* s = h->runStrongMemory(TSS_ITERATION, NB_MOVEMENT, NB_PERTURBATION);

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

    const int TABU_ITERATION = 1000;
    const int NB_MOVEMENT = 10;
    const int NB_PERTURBATION = 10;
    const int TABU_COUNTER = 3;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *h = new TabuSearch<BinaryCombinatorySolution<int>>(true, f, nbElements);

    BinaryCombinatorySolution<int>* s = h->runAdaptableMemory(TABU_ITERATION, NB_MOVEMENT, NB_PERTURBATION,
                                                              TABU_COUNTER);

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
 * Simulated annealing algorithm with counter memory
 */
void mainSA() {

    const int NB_EVAL_PER_TEMP   = 10;
    const double TEMPERATURE     = 300.0;
    const double MIN_TEMPERATURE = 0.003;
    const double DECREASE_FACTOR = 0.98;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *sa = new SimulatedAnnealing<BinaryCombinatorySolution<int>>(true, f, nbElements);

    BinaryCombinatorySolution<int>* s = sa->run(NB_EVAL_PER_TEMP, TEMPERATURE, MIN_TEMPERATURE, DECREASE_FACTOR);

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
 * EA simple algorithm run
 */
void mainEASimple() {

    const int MU_ELEMENT = 100;
    const int LAMBDA_ELEMENT = 50;
    const int NB_ITERATION = 1000;
    const int NB_LOCAL_ITERATION = 100;

    time_t start = time(0);

    vector<Fitness> f;
    f.push_back((Fitness) compute);

    auto *ea = new EvolutionaryAlgorithmSearch<BinaryCombinatorySolution<int>>(true, f, nbElements);

    BinaryCombinatorySolution<int>* s = ea->runSimple(MU_ELEMENT,
                                                      LAMBDA_ELEMENT,
                                                      NB_ITERATION,
                                                      Selectors<BinaryCombinatorySolution<int>>::simpleSelector,
                                                      Selectors<BinaryCombinatorySolution<int>>::simpleSelector,
                                                      Operators<BinaryCombinatorySolution<int>>::simpleCrossover,
                                                      Operators<BinaryCombinatorySolution<int>>::simpleMutation,
                                                      LocalSearch<BinaryCombinatorySolution<int>>::hillClimberBestImprovement,
                                                      NB_LOCAL_ITERATION);

    cout << "Best solution found so far for EA simple search : ";
    s->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long) s) << endl;
    delete s;

    double seconds_since_start = difftime(time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec." << endl;
}

void gettingValues(vector<double>* v, string val){

    istringstream f(val);
    string s;
    while(getline(f, s, ' ')){
        v->push_back(stod(s));
    }
}

void loadKnapsackInfo(string path){
    ifstream file(path);

    string strNbElements;
    getline(file, strNbElements);
    nbElements = stoi(strNbElements);

    string strProfits;
    getline(file, strProfits);

    string strWeights;
    getline(file, strWeights);

    gettingValues(profits, strProfits);
    gettingValues(weights, strWeights);

    string strCapacity;
    getline(file, strCapacity);
    capacity = stoi(strCapacity);
}

/**
 * Main function which loads all examples
 * @return
 */
int main() {

    srand(10);

    loadKnapsackInfo("./../resources/knapsack/ks_1000.txt");

    //mainLS();
    //mainSA();
    mainEASimple();

    return 0;
}
