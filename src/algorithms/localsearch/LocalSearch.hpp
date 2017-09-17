//
// Created by jbuisine on 17/09/17.
//

#ifndef METAHEURISTICS_LOCALSEARCH_HPP
#define METAHEURISTICS_LOCALSEARCH_HPP

#include "../../solutions/CombinatorySolution.hpp"
#include "../../solutions/BinaryCombinatorySolution.hpp"
#include "../Heuristics.hpp"
#include <algorithm>

template <typename C>
class LocalSearch{


public:
    /**
     *  HillClimberBestImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @param nbEvaluation : Number of iteration expected for the HC best improvement
     * @param heuristics : problem's context
     * @param s : C solution to begin algorithm with
     * @return Solution object : the best solution found
     */
    static C* hillClimberBestImprovement(int nbEvaluation, Heuristics<C> *heuristics, C* s = NULL) {
        int nbEval = 0;
        int size = heuristics->getProblemSize();
        vector<Fitness> funcs = heuristics->getFunctions();

        C *sol;

        // Getting existing solution pass as parameter
        if(s == NULL)
            sol = new C(size);
        else
            sol = s;

        do{
            vector<double> scores;

            // Store scores to avoid redundant compute statements
            for (unsigned int j = 0; j < funcs.size(); ++j) {
                Fitness fnc = (Fitness) funcs[j];
                double r = fnc((long)sol);
                scores.push_back(r);
            }

            // Getting neighbor solutions of sol
            vector<C*>* neighbors = (vector<C*>*)sol->getNeighbors();

            for (int i = 0; i < neighbors->size(); ++i) {

                if(heuristics->checkSolution(scores, neighbors->at(i))){
                    sol->copyArr(neighbors->at(i)->getArr(), size);
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
     * @param heuristics : problem's context
     * @param s : C solution to begin algorithm with
     * @return Solution object : the best solution found
     */
    static C* hillClimberFirstImprovement(int nbEvaluation, Heuristics<C> *heuristics, C *s = NULL) {
        int nbEval = 0;
        int size = heuristics->getProblemSize();
        vector<Fitness> funcs = heuristics->getFunctions();

        C *sol;

        if(s == NULL)
            sol = new C(size);
        else
            sol = s;

        do{
            vector<double> scores;

            // Store scores to avoid redundant compute statements
            for (unsigned int j = 0; j < funcs.size(); ++j) {
                Fitness fnc = (Fitness) funcs[j];
                double r = fnc((long)sol);
                scores.push_back(r);
            }

            // TODO check if it's possible to avoid double loop for BinaryCombinatorySolution type
            for (int i = 0; i < sol->getSize(); ++i) {

                for (int j = 0; j < sol->getSize(); ++j) {

                    C *newest = (C*)sol->getNeighbor(sol, i, j);

                    // Break if new solution is better
                    if(heuristics->checkSolution(scores, newest)) {
                        sol->copyArr(newest->getArr(), size);
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
};
#endif //METAHEURISTICS_LOCALSEARCH_HPP
