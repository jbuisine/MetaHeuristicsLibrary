//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include "Heuristics.hpp"
#include <algorithm>

template<typename C>
class IteratedLocal : public Heuristics<C> {

    typedef C* (Local)(int nbEvaluation, Heuristics<C> *heuristics, C* s);

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    IteratedLocal(bool problem_type, vector<Fitness>& funcs, int size) : Heuristics<C>(problem_type, funcs, size){}


    /**
     * Iterated local search implementation
     *
     * @param nbEvaluation : number of iteration for ILS
     * @param nbPerturbation : number of element permute to create new solution
     * @param localSearch : Local search heuristics chosen
     * @param nbIterationLocal : number iteration for the local search
     * @return the best solution found
     */
    C* run(int nbEvaluation, int nbPerturbation, Local localSearch, int nbIterationLocal) {
        int nbEval = 0;

        C *s;
        C *best = new C(this->size);

        do{
            s = C::copy(best);
            s->swapIndex(nbPerturbation);

            C *n = localSearch(nbIterationLocal, this, s);

            if(this->checkSolution(best, n)){
                best = C::copy(n);
                delete n;
            }

            cout << "ILS " << ((double)nbEval*100.0)/nbEvaluation << "%" << endl;

            nbEval++;

        }while (nbEvaluation > nbEval);

        cout << "100.000%" << endl;

        return best;
    }
};