//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include "../solutions/CombinatorySolution.hpp"
#include "../solutions/BinaryCombinatorySolution.hpp"
#include "../utils/Utils.hpp"
#include "Utilities.hpp"
#include <algorithm>

template<typename C>
class Heuristics {

protected:
    /**
     * 'false' specify minimizing problem and 'true' maximizing
     */
    bool problem_type;

    vector<Fitness> funcs;

    int size;

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

        return counter == this->funcs.size();
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

            // TODO check if it's possible to avoid double loop for BinaryCombinatorySolution type
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
};


#endif //METAHEURISTICS_HEURISTICS_H
