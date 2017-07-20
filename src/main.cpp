#include <functional>
#include <iostream>
#include <math.h>
#include "Heuristics.h"

using namespace std;

double compute (CombinatorySolution<10>* s) {

    double c = 0.0;

    for (int i = 0; i < s->getArr().size(); ++i) {
        c += sqrt(s->getArr()[i])*sqrt(i);
    }

    return c;
}

int main() {

    function<double(CombinatorySolution<10>*)> compute_obj = compute;

    vector<function<double(CombinatorySolution<10>*)>> f;

    f.push_back(compute_obj);

    Heuristics<CombinatorySolution<10>, 10> *h = new Heuristics<CombinatorySolution<10>, 10>(false, f, 100);

    CombinatorySolution<10>* s1 = h->HillClimberBestImprovement(1000);
    s1->displaySolution();
    cout << "HC best improvement with Binary combinatory solution : " <<f[0](s1) << endl;

    cout << endl;

    return 0;
}
