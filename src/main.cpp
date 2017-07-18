#include <functional>
#include <iostream>
#include "Heuristics.h"

using namespace std;

double compute (Solution* s) {

    double c = 0.0;

    for (int i = 0; i < s->getArr().size(); ++i) {
        c += s->getArr()[i]*s->getArr()[i]*(i-2);
    }

    return c;
}

int main() {

    function<double(Solution*)> compute_obj = compute;

    vector<function<double(Solution*)>> f;

    f.push_back(compute_obj);

    Heuristics *h = new Heuristics(false, f, 20);

    Solution* s1 = h->HillClimberBestImprovement<BinaryCombinatorySolution>(1000);
    s1->displaySolution();
    cout << "HC best improvement with Binary combinatory solution : " <<f[0](s1) << endl;

    cout << endl;

    Solution* s2 = h->HillClimberBestImprovement<CombinatorySolution>(1000);
    s2->displaySolution();
    cout << "HC best improvement with Combinatory solution : " <<f[0](s2) << endl;

    cout << endl;

    Solution* s3 = h->HillClimberFirstImprovement<BinaryCombinatorySolution>(1000);
    s1->displaySolution();
    cout << "HC first improvement with Binary combinatory solution : " <<f[0](s3) << endl;

    cout << endl;

    Solution* s4 = h->HillClimberFirstImprovement<CombinatorySolution>(1000);
    s2->displaySolution();
    cout << "HC first improvement with Combinatory solution : " <<f[0](s4) << endl;

    return 0;
}
