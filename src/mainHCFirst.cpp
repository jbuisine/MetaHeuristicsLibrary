#include "Algorithms/Heuristics.hpp"
#include "utils.h"

using namespace std;

void mainHCFirst() {
    time_t start = time(0);


    vector<Fitness> f;
    f.push_back((Fitness)compute);

    Heuristics<CombinatorySolution<int>>* h = new Heuristics<CombinatorySolution<int>>(false, f, N);

    CombinatorySolution<int>* s1 = h->HillClimberFirstImprovement(I);

    cout << "Best solution found so far : ";
    s1->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long)s1) << endl;

    delete s1;

    double seconds_since_start = difftime( time(0), start);

    cout << "Time consumed " << seconds_since_start << " sec.";
}
