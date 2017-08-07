#include "Heuristics.hpp"

using namespace std;

// Number of element
const int N = 10;

// Number of iteration
const int I = 1000;

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


    vector<VoidFunctionLong> f;
    f.push_back((VoidFunctionLong)compute);

    Heuristics<CombinatorySolution<int>>* h = new Heuristics<CombinatorySolution<int>>(false, f, N);

    CombinatorySolution<int>* s1 = h->HillClimberBestImprovement(I, true);

    cout << "Best solution found so far : ";
    s1->displaySolution();
    cout << " with a score of ";
    cout << compute((long)s1);

    delete s1;
    cout << endl;

    return 0;
}
