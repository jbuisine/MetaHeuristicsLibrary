//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include "../solutions/CombinatorySolution.hpp"
#include "../solutions/BinaryCombinatorySolution.hpp"
#include "Heuristics.hpp"
#include <algorithm>

template<typename C>
class TabuSearch : public Heuristics<C> {

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    TabuSearch(bool problem_type, vector<Fitness>& funcs, int size) : Heuristics<C>(problem_type, funcs, size){}

    /**
     * tabu search simple implementation
     * @param nbEvaluation : number of iteration
     * @param nbMovement : number of movement expected at each iteration to obtain new solution
     * @param nbPerturbation : number of elements permuted into a solution at each movement
     * @return
     */
    C* runStrongMemory(int nbEvaluation, int nbMovement, int nbPerturbation){

        // Best solution to return
        auto* best = new C(this->size);

        // Variable used to store best solution of each iteration
        C* s = C::copy(best);

        vector<TabuMovement*>* tabuList = new vector<TabuMovement*>();

        int nbEval = 0;

        while(nbEval < nbEvaluation) {

            // 1. Do N non tabu movement to obtain new solution to start iteration with
            for (int i = 0; i < nbMovement; ++i) {
                begin:

                C* currentMov = C::copy(s);
                currentMov->swapIndex(nbPerturbation);

                if(!checkMovementExists(tabuList, s, currentMov)){
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

            // 4. Mark as tabu this movement
            TabuMovement* mov = new TabuMovement;

            mov->t = C::copy(t);
            mov->s = C::copy(s);

            tabuList->push_back(mov);
            delete neighborHood;

            // 5. Set new context for next iteration
            s = C::copy(t);
            delete t;
        }

        delete tabuList;
        delete s;

        return best;
    }


    /**
     * tabu search implementation with memory counter
     * @param nbEvaluation : number of iteration
     * @param nbMovement : number of movement expected at each iteration to obtain new solution
     * @param nbPerturbation : number of elements permuted into a solution at each movement
     * @param tabuCounter : number of times a movement is defined as tabu
     * @return
     */
    C* runAdaptableMemory(int nbEvaluation, int nbMovement, int nbPerturbation, int tabuCounter){

        // Best solution to return
        C* best = new C(this->size);

        // Variable used to store best solution of each iteration
        C* s = C::copy(best);

        vector<TabuMovementCounter*>* tabuList = new vector<TabuMovementCounter*>();

        int nbEval = 0;

        while(nbEval < nbEvaluation) {

            // 1. Do N non tabu movement to obtain new solution to start iteration with
            for (int i = 0; i < nbMovement; ++i) {
                begin:

                C* currentMov = C::copy(s);
                currentMov->swapIndex(nbPerturbation);

                if(!checkMovementCounterExists(tabuList, s, currentMov, tabuCounter)){
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

            // 4. Mark as tabu this movement
            auto* mov = new TabuMovementCounter;

            mov->t = t;
            mov->s = s;
            mov->counter = tabuCounter;

            tabuList->push_back(mov);
            delete neighborHood;

            // 5. Set new context for next iteration
            s = C::copy(t);
            delete t;
        }

        delete tabuList;
        delete s;

        return best;
    }

private:

    struct TabuMovement{
        C* t;
        C* s;
    };

    struct TabuMovementCounter{
        C* t;
        C* s;
        int counter;
    };

    /**
     * Method which checks if movement is defined as tabu
     * @param movements : tabu list of movement
     * @param t : movement t
     * @param s : movement s
     * @return true if movement is tabu otherwise false
     */
    bool checkMovementExists(vector<TabuMovement*>* movements, C* t, C* s){

        for (int i = 0; i < movements->size(); ++i) {
            if(Utilities<C>::sameSolution(movements->at(i)->t, t) && Utilities<C>::sameSolution(movements->at(i)->s, s)){
                return true;
            }
        }

        return false;
    }

    /**
     * Method which checks if movement is defined as tabu and decrease tabu counter if it is
     * @param movements : tabu list of movement
     * @param t : movement t
     * @param s : movement s
     * @return true if movement is tabu otherwise false
     */
    bool checkMovementCounterExists(vector<TabuMovementCounter*>* movements, C* s, C* t, int tabuCounter){
        for (int i = 0; i < movements->size(); ++i) {
            if(Utilities<C>::sameSolution(movements->at(i)->t, t) && Utilities<C>::sameSolution(movements->at(i)->s, s)){
                movements->at(i)->counter--;

                if(movements->at(i)->counter == 0){
                    movements->at(i)->counter = tabuCounter;
                    return true;
                }
            }
        }

        return false;
    }

};