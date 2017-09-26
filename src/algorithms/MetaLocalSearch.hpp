//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include "Heuristics.hpp"
#include <algorithm>

template<typename C>
class MetaLocalSearch : public Heuristics<C> {

    typedef C* (Local)(int nbEvaluation, Heuristics<C> *heuristics, C* s);

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    MetaLocalSearch(bool problem_type, vector<Fitness>& funcs, int size) : Heuristics<C>(problem_type, funcs, size){}


    /**
     * Iterated local search implementation
     *
     * @param nbEvaluation : number of iteration for ILS
     * @param nbPerturbation : number of element permute to create new solution
     * @param localSearch : Local search heuristics chosen
     * @param nbIterationLocal : number iteration for the local search
     * @return the best solution found
     */
    C* runILS(int nbEvaluation, int nbPerturbation, Local localSearch, int nbIterationLocal) {
        int nbEval = 0;

        C *s;
        auto *best = new C(this->size);

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

    /**
     *  Descent variable neighborhoods (computation time depends on size of your problem)
     *
     * @param solution : current solution
     * @param localSearch : Local search heuristics chosen
     * @return the best solution found
     */
    C* runDVN(C* solution, Local localSearch, int nbIterationLocal) {


        C* best = C::copy(solution);

        bool descent = true;

        while(descent){
            descent = false;
            vector<C*>* neighborHood = (vector<C*>*) best->getNeighbors();

            for (int i = 0; i < neighborHood->size(); ++i) {

                // Local search for improvement
                C *s = localSearch(nbIterationLocal, this, neighborHood->at(i));

                if(this->checkSolution(best, s)){
                    best = C::copy(neighborHood->at(i));
                    descent = true;
                }
            }

            delete neighborHood;
        }

        return best;
    }

    /**
     * Multi start local search implementation
     *
     * @param nbEvaluation : number of iteration for multi start
     * @param localSearch : Local search heuristics chosen
     * @param nbIterationLocal : number iteration for the local search
     * @return the best solution found
     */
    C* runMultiStart(int nbEvaluation, Local localSearch, int nbIterationLocal) {
        int nbEval = 0;

        auto *best = new C(this->size);

        do{
            C s = new C(this->size);

            C *n = localSearch(nbIterationLocal, this, s);

            if(this->checkSolution(best, n)){
                best = C::copy(n);
                delete n;
            }

            cout << "Multi start " << ((double)nbEval*100.0)/nbEvaluation << "%" << endl;

            nbEval++;

        }while (nbEvaluation > nbEval);

        cout << "100.000%" << endl;

        return best;
    }

    /**
     * Search for variable neighborhoods base version
     *
     * @param nbEvaluation : number of iteration for multi start
     * @param kMax : limit perturbation criteria
     * @param localSearch : Local search heuristics chosen
     * @param nbIterationLocal : number iteration for the local search
     * @return the best solution found
     */
    C* runSVNBase(int nbEvaluation, int kMax, Local localSearch, int nbIterationLocal) {
        int nbEval = 0;
        int k = 1;

        auto *best = new C(this->size);

        do{
            C *s = C::copy(best);
            s->swapIndex(k);

            C *n = localSearch(nbIterationLocal, this, s);

            if(this->checkSolution(best, n)){
                best = C::copy(n);
                delete n;
            }
            else{
                k++;

                if(k > kMax){
                    k = 1;
                }
            }

            cout << "SVN Base " << ((double)nbEval*100.0)/nbEvaluation << "%" << endl;

            nbEval++;

        }while (nbEvaluation > nbEval);

        cout << "100.000%" << endl;

        return best;
    }

    /**
     * Search for variable neighborhoods general version
     *
     * @param nbEvaluation : number of iteration for multi start
     * @param kMax : limit perturbation criteria
     * @param localSearch : Local search heuristics chosen
     * @param nbIterationLocal : number iteration for the local search
     * @return the best solution found
     */
    C* runSVNGeneral(int nbEvaluation, int kMax, Local localSearch, int nbIterationLocal) {
        int nbEval = 0;
        int k = 1;

        auto *best = new C(this->size);

        do{
            C *s = C::copy(best);
            s->swapIndex(k);

            C *n = runDVN(s, localSearch, nbIterationLocal);

            if(this->checkSolution(best, n)){
                best = C::copy(n);
                delete n;
            }
            else{
                k++;

                if(k > kMax){
                    k = 1;
                }
            }

            cout << "SVN Base " << ((double)nbEval*100.0)/nbEvaluation << "%" << endl;

            nbEval++;

        }while (nbEvaluation > nbEval);

        cout << "100.000%" << endl;

        return best;
    }

    /**
     * Search for variable neighborhoods reduce version (without local search)
     *
     * @param nbEvaluation : number of iteration for multi start
     * @param kMax : limit perturbation criteria
     * @return the best solution found
     */
    C* runSVNReduce(int nbEvaluation, int kMax) {
        int nbEval = 0;
        int k = 1;

        auto *best = new C(this->size);

        do{
            C *s = C::copy(best);
            s->swapIndex(k);

            if(this->checkSolution(best, s)){
                best = C::copy(s);
                delete s;
            }
            else{
                k++;

                if(k > kMax){
                    k = 1;
                }
            }

            cout << "SVN Reduce " << ((double)nbEval*100.0)/nbEvaluation << "%" << endl;

            nbEval++;

        }while (nbEvaluation > nbEval);

        cout << "100.000%" << endl;

        return best;
    }
};