//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include "../solutions/CombinatorySolution.hpp"
#include "../solutions/BinaryCombinatorySolution.hpp"
#include "Heuristics.hpp"
#include <algorithm>

template<typename C>
class TabooSearch : public Heuristics<C> {

private:

    struct TabooMovement{
        C* t;
        C* s;
    };

    struct TabooMovementCounter{
        C* t;
        C* s;
        int counter;
    };

    /**
     * Method which checks if movement is defined as taboo
     * @param movements : taboo list of movement
     * @param t : movement t
     * @param s : movement s
     * @return true if movement is taboo otherwise false
     */
    bool checkMovementExists(vector<TabooMovement*>* movements, C* t, C* s){

        for (int i = 0; i < movements->size(); ++i) {
            if(Utilities<C>::sameSolution(movements->at(i)->t, t) && Utilities<C>::sameSolution(movements->at(i)->s, s)){
                return true;
            }
        }

        return false;
    }

    /**
     * Method which checks if movement is defined as taboo and decrease taboo counter if it is
     * @param movements : taboo list of movement
     * @param t : movement t
     * @param s : movement s
     * @return true if movement is taboo otherwise false
     */
    bool checkMovementCounterExists(vector<TabooMovementCounter*>* movements, C* s, C* t, int tabooCounter){
        for (int i = 0; i < movements->size(); ++i) {
            if(Utilities<C>::sameSolution(movements->at(i)->t, t) && Utilities<C>::sameSolution(movements->at(i)->s, s)){
                movements->at(i)->counter--;

                if(movements->at(i)->counter == 0){
                    movements->at(i)->counter = tabooCounter;
                    return true;
                }
            }
        }

        return false;
    }

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    TabooSearch(bool problem_type, vector<Fitness>& funcs, int size) : Heuristics<C>(problem_type, funcs, size){}

    /**
     * Taboo search simple implementation
     * @param nbEvaluation : number of iteration
     * @param nbMovement : number of movement expected at each iteration to obtain new solution
     * @param nbPerturbation : number of elements permuted into a solution at each movement
     * @return
     */
    C* tabooSearchSimple(int nbEvaluation, int nbMovement, int nbPerturbation){

        // Best solution to return
        C *best = new C(this->size);

        // Variable used to store best solution of each iteration
        C* s = C::copy(best);

        vector<TabooMovement*>* tabooList = new vector<TabooMovement*>();

        int nbEval = 0;

        while(nbEval < nbEvaluation) {

            // 1. Do N non taboo movement to obtain new solution to start iteration with
            for (int i = 0; i < nbMovement; ++i) {
                begin:

                C* currentMov = C::copy(s);
                currentMov->swapIndex(nbPerturbation);

                if(!checkMovementExists(tabooList, s, currentMov)){
                    s = C::copy(currentMov);

                    delete currentMov;
                }else{
                    delete currentMov;
                    goto begin;
                }
            }

            // 2. Getting best neighbor into neighborhood of S
            vector<C*>* neighborHood = (vector<C*>*) best->getNeighbors();
            C* t = neighborHood->at(0);

            for (int i = 1; i < neighborHood->size(); ++i) {

                if (this->checkSolution(t, neighborHood->at(i))) {
                    t = C::copy(neighborHood->at(i));
                }

                nbEval++;
            }

            // 3. Update best solution if it is
            if (this->checkSolution(best, t)) {
                delete best;
                best = C::copy(t);
            }

            // 4. Mark as taboo this movement
            TabooMovement* mov = new TabooMovement;

            mov->t = C::copy(t);
            mov->s = C::copy(s);

            tabooList->push_back(mov);
            delete neighborHood;

            // 5. Set new context for next iteration
            s = C::copy(t);
            delete t;
        }

        return best;
    }


    /**
     * Taboo search implementation with memory counter
     * @param nbEvaluation : number of iteration
     * @param nbMovement : number of movement expected at each iteration to obtain new solution
     * @param nbPerturbation : number of elements permuted into a solution at each movement
     * @param tabooCounter : number of times a movement is defined as taboo
     * @return
     */
    C* tabooSearchCounter(int nbEvaluation, int nbMovement, int nbPerturbation, int tabooCounter){

        // Best solution to return
        C *best = new C(this->size);

        // Variable used to store best solution of each iteration
        C* s = C::copy(best);

        vector<TabooMovementCounter*>* tabooList = new vector<TabooMovementCounter*>();

        int nbEval = 0;

        while(nbEval < nbEvaluation) {

            // 1. Do N non taboo movement to obtain new solution to start iteration with
            for (int i = 0; i < nbMovement; ++i) {
                begin:

                C* currentMov = C::copy(s);
                currentMov->swapIndex(nbPerturbation);

                if(!checkMovementCounterExists(tabooList, s, currentMov, tabooCounter)){
                    s = C::copy(currentMov);

                    delete currentMov;
                }else{
                    delete currentMov;
                    goto begin;
                }
            }

            // 2. Getting best neighbor into neighborhood of S
            vector<C*>* neighborHood = (vector<C*>*) best->getNeighbors();
            C* t = neighborHood->at(0);

            for (int i = 1; i < neighborHood->size(); ++i) {

                if (this->checkSolution(t, neighborHood->at(i))) {
                    t = C::copy(neighborHood->at(i));
                }

                nbEval++;
            }

            // 3. Update best solution if it is
            if (this->checkSolution(best, t)) {
                delete best;
                best = C::copy(t);
            }

            // 4. Mark as taboo this movement
            TabooMovementCounter* mov = new TabooMovementCounter;

            mov->t = t;
            mov->s = s;
            mov->counter = tabooCounter;

            tabooList->push_back(mov);
            delete neighborHood;

            // 5. Set new context for next iteration
            s = C::copy(t);
            delete t;
        }

        return best;
    }
};