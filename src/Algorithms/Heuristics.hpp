//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include "../solutions/CombinatorySolution.hpp"
#include "../solutions/BinaryCombinatorySolution.hpp"
#include "Utilities.hpp"
#include <algorithm>

template<typename C>
class Heuristics {

private:
    /**
     * 'false' specify minimizing problem and 'true' maximizing
     */
    bool problem_type;

    vector<Fitness> funcs;

    int size;

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    Heuristics(bool problem_type, vector<Fitness>& funcs, int size) {
        this->funcs = funcs;
        this->size = size;
        this->problem_type = problem_type;
    }


    /**
     * Method used for getting all non dominated solutions from set of solutions
     *
     * @param sols : the set of solutions
     * @return solutions : new set of non dominated solutions
     */
    vector<C*>* getNonDominatedSols(vector<C*>* sols) {

        vector<C*>* solutions = new vector<C>();

        for (int i = 0; i < sols->size(); ++i) {

            vector<double> scores;

            // Store scores of i solution to avoid redundant compute statements
            for (int j = 0; j < this->funcs.size(); ++j)
                scores.push_back(this->funcs[j](sols->at(i)));

            for (int j = 0; j < sols->size(); ++j) {

                if(this->checkSolution(scores, sols[j]) && !Utilities<C>::checkExists(solutions, sols->at(i)))
                    solutions->push_back(sols[i]);
            }
        }

        return solutions;
    }


    /**
      * Method which check the solution dominance
      * @param scores : scores of the older solution
      * @param n = the new solution
      * @return True if new solution dominate the older
      */
    bool checkSolution(vector<double>& scores, C* n){

        int counter = 0;

        size_t s =  this->funcs.size();

        for (int i = 0; i < s; ++i) {

            if(this->problem_type){
                if(funcs[i]((long)n) >= scores[i]) counter++;
            }
            else{
                if(funcs[i]((long)n) <= scores[i]) counter++;
            }
        }

        return counter == this->funcs.size();
    }

    /**
     * Method which check the solution dominance
     * @param o : the older solution
     * @param n = the newest solution
     * @return
     */
    bool checkSolution(C* o, C* n) {

        int counter = 0;

        for (int i = 0; i < this->funcs.size(); ++i) {

            if(this->problem_type){
                if(funcs[i]((long)n) >= funcs[i]((long)o)) counter ++;
            }
            else{
                if(funcs[i]((long)n) <= funcs[i]((long)o)) counter ++;
            }
        }

        return (counter == this->funcs.size());
    }

    /**
     *  HillClimberBestImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @param nbEvaluation : Number of iteration expected for the HC best improvement
     * @param s : C solution to begin algorithm with
     * @return Solution object : the best solution found
     */
    C* hillClimberBestImprovement(int nbEvaluation, C* s = NULL) {
        int nbEval = 0;

        C *sol;

        // Getting existing solution pass as parameter
        if(s == NULL)
            sol = new C(this->size);
        else
            sol = s;

        do{
            vector<double> scores;

            // Store scores to avoid redundant compute statements
            for (unsigned int j = 0; j < this->funcs.size(); ++j) {
                Fitness fnc = (Fitness) this->funcs[j];
                double r = fnc((long)sol);
                scores.push_back(r);
            }

            // Getting neighbor solutions of sol
            vector<C*>* neighbors = (vector<C*>*)sol->getNeighbors();

            for (int i = 0; i < neighbors->size(); ++i) {

                if(this->checkSolution(scores, neighbors->at(i))){
                    sol->copyArr(neighbors->at(i)->getArr(), this->size);
                }

                nbEval++;

                if(nbEvaluation <= nbEval){
                    delete neighbors;
                    goto end;
                }
            }

            delete neighbors;

        }while (nbEvaluation > nbEval);

        end:
        return sol;
    }

    /**
     *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @param nbEvaluation : Number of iteration expected for the HC first improvement
     * @param s : C solution to begin algorithm with
     * @return Solution object : the best solution found
     */
    C* hillClimberFirstImprovement(int nbEvaluation, C *s = NULL) {
        int nbEval = 0;

        C *sol;

        if(s == NULL)
            sol = new C(this->size);
        else
            sol = s;

        do{
            vector<double> scores;

            // Store scores to avoid redundant compute statements
            for (unsigned int j = 0; j < this->funcs.size(); ++j) {
                Fitness fnc = (Fitness) this->funcs[j];
                double r = fnc((long)sol);
                scores.push_back(r);
            }

            // TODO check if it's possible to avoid double loop for BinaryCombinatorySolution
            for (int i = 0; i < sol->getSize(); ++i) {

                for (int j = 0; j < sol->getSize(); ++j) {

                    C *newest = (C*)sol->getNeighbor(sol, i, j);

                    // Break if new solution is better
                    if(this->checkSolution(scores, newest)) {
                        sol->copyArr(newest->getArr(), this->size);
                        break;
                    }

                    nbEval++;

                    if(nbEvaluation <= nbEval)
                        goto end;
                }
            }

        }while (nbEvaluation > nbEval);

        end:
        return sol;
    }


    /**
     * Iterated local search implementation
     *
     * @param nbEvaluation : number of iteration for ILS
     * @param nbHcIteration : number of iteration for each HC first improvement
     * @param nbPerturbation : number of element permute to create new solution
     * @return the best solution found
     */
    C* iteratedLocalSearch(int nbEvaluation, int nbHcIteration, int nbPerturbation) {
        int nbEval = 0;

        C *s;
        C *best = new C(this->size);

        do{
            s = C::copy(best);
            s->swapIndex(nbPerturbation);

            C *n = this->hillClimberFirstImprovement(nbHcIteration, s);

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
     * Tabu search implementation
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

        vector<C*>* tabuList = new vector<C*>();
        tabuList->push_back(C::copy(best));

        int nbEval = 0;

        while(nbEval < nbEvaluation) {

            // 1. Do N non taboo movement to obtain new solution to start iteration with
            for (int i = 0; i < nbMovement; ++i) {
                begin:

                C* currentMov = C::copy(s);
                currentMov->swapIndex(nbPerturbation);

                if(!Utilities<C>::checkExists(tabuList, currentMov)){
                    best = C::copy(currentMov);
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

                if (checkSolution(t, neighborHood->at(i))) {
                    t = C::copy(neighborHood->at(i));
                }

                nbEval++;
            }

            // 3. Update best solution if it is
            if (checkSolution(best, t)) {
                delete best;
                best = C::copy(t);
            }

            // 4. Mark as taboo this movement
            tabuList->push_back(C::copy(t));
            delete neighborHood;

            // 5. Set new context for next iteration
            s = C::copy(t);
            delete t;
        }

        return best;
    }

};


#endif //METAHEURISTICS_HEURISTICS_H
