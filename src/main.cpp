#include "Heuristics.hpp"

#include "solutions/CombinatorySolution.hpp"
#include "solutions/BinaryCombinatorySolution.hpp"

using namespace std;

const size_t N = 100;

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

    Heuristics<CombinatorySolution<int>>* h = new Heuristics<CombinatorySolution<int>>(false, f, 100);

    CombinatorySolution<int>* s1 = h->HillClimberBestImprovement(1000, true);
    s1->displaySolution();
    //long best = f[0](s1);
    //cout << "HC best improvement with Binary combinatory solution : " << best << endl;
    delete s1;
    cout << endl;

    return 0;
}
