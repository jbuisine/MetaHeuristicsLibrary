#include <functional>
#include <iostream>
#include "Heuristics.h"

using namespace std;

double compute (Solution* s) {

    double c = 0.0;

    for (int i = 0; i < s->getArr().size(); ++i) {
        c += s->getArr()[i]*i*0.05;
    }

    return c;
}

int main() {

    function<double(Solution*)> compute_obj = compute;

    vector<function<double(Solution*)>> f;

    f.push_back(compute_obj);

    Heuristics *h = new Heuristics(false, f, 10);

    Solution* s = h->HillClimberBestImprovement<CombinatorySolution>(100);

    cout << f[0](s) << endl;
    return 0;
}
