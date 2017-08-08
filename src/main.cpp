#include "Algorithms/Heuristics.hpp"

using namespace std;

// Number of element
const int N = 100;

// Number of iteration
const int I = 100000;

// Function of Fitness type
double compute (long ptrToParam) {

    CombinatorySolution<int>* s = (CombinatorySolution<int>*)ptrToParam;

    double c = 0.0;

    int t = s->getSize();
    for (int i = 0; i < t; ++i) {
        c += sqrt(s->getArr()[i])*sqrt(i);
    }

    return c;
}

int main() {
    time_t start = time(0);


    vector<Fitness> f;
    f.push_back((Fitness)compute);

    Heuristics<BinaryCombinatorySolution<int>>* h = new Heuristics<BinaryCombinatorySolution<int>>(false, f, N);


    BinaryCombinatorySolution<int>* s1 = h->HillClimberFirstImprovement(I);

    cout << "Best solution found so far : ";
    s1->displaySolution();
    cout << endl;
    cout << "Score of ";
    cout << compute((long)s1);

    delete s1;

    cout << endl;

    BinaryCombinatorySolution<int>* s2 = h->HillClimberBestImprovement(I);

    cout << "Best solution found so far : ";
    s2->displaySolution();
    cout << " with a score of ";
    cout << compute((long)s2);

    delete s2;

    cout << endl;


    double seconds_since_start = difftime( time(0), start);

    cout << "Time consumed " << seconds_since_start;

    return 0;
}
