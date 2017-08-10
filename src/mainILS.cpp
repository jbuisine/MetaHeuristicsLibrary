//
// Created by jbuisine on 10/08/17.
//

#include "Algorithms/Heuristics.hpp"
#include "configuration.h"

using namespace std;

// Useful const for ILS meta heuristic
const int HC_I = 1000;
const int NB_PERTURBATION = 10;

// Function of Fitness type
double computeILS (long ptrToParam) {

    CombinatorySolution<int>* s = (CombinatorySolution<int>*)ptrToParam;

    double c = 0.0;

    int t = s->getSize();
    for (int i = 0; i < t; ++i) {
        c += sqrt(s->getArr()[i])*sqrt(i);
    }

    return c;
}

void mainILS() {
    time_t start = time(0);


    vector<Fitness> f;
    f.push_back((Fitness)computeILS);

    Heuristics<CombinatorySolution<int>>* h = new Heuristics<CombinatorySolution<int>>(false, f, N);

    CombinatorySolution<int>* s1 = h->IteratedLocalSearch(I, HC_I, NB_PERTURBATION);

    cout << "Best solution found so far : ";
    s1->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << computeILS((long)s1) << endl;

    delete s1;

    double seconds_since_start = difftime( time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec.";
}
