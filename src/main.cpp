#include <functional>
#include <iostream>
#include <math.h>
#include "Heuristics.h"

using namespace std;

const size_t N = 100;

double compute (CombinatorySolution<int, N>* s) {

    double c = 0.0;

    for (int i = 0; i < s->getSize(); ++i) {
        c += sqrt(s->getArr()[i])*sqrt(i);
    }

    return c;
}

int main() {

    function<double(CombinatorySolution<int, N>*)> compute_obj = compute;

    vector<function<double(CombinatorySolution<int, N>*)>> f;

    f.push_back(compute_obj);

    Heuristics<CombinatorySolution<int, N>> *h = new Heuristics<CombinatorySolution<int, N>>(false, f, 100);

    CombinatorySolution<int, N>* s1 = h->HillClimberBestImprovement(1000);
    s1->displaySolution();
    cout << "HC best improvement with Binary combinatory solution : " <<f[0](s1) << endl;

    cout << endl;

    return 0;
}
