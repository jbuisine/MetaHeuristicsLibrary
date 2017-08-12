//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include "../solutions/CombinatorySolution.hpp"
#include "../solutions/BinaryCombinatorySolution.hpp"
#include "Utilities.hpp"

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
    vector<C> getNonDominatedSols(vector<C>& sols) {

        vector<C> solutions;

        for (int i = 0; i < sols.size(); ++i) {

            vector<double> scores;

            // Store scores of i solution to avoid redundant compute statements
            for (int j = 0; j < this->funcs.size(); ++j)
                scores.push_back(this->funcs[j](sols[i]));

            for (int j = 0; j < sols.size(); ++j) {

                if(this->checkSolution(scores, sols[j]) && !Utilities<C>::checkExists(solutions, sols[i]))
                    solutions.push_back(sols[i]);
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
     * @param nb_iteration : Number of iteration expected for the HC best improvement
     * @param s : C solution to begin algorithm with
     * @return Solution object : the best solution found
     */
    C* HillClimberBestImprovement(int nb_iteration, C* s = NULL) {
        int nb_eval = 0;

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

                nb_eval++;

                if(nb_iteration <= nb_eval){
                    delete neighbors;
                    goto end;
                }
            }

            delete neighbors;

        }while (nb_iteration > nb_eval);

        end:
        return sol;
    }

    /**
     *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @param nb_iteration : Number of iteration expected for the HC first improvement
     * @param s : C solution to begin algorithm with
     * @return Solution object : the best solution found
     */
    C* HillClimberFirstImprovement(int nb_iteration, C *s = NULL) {
        int nb_eval = 0;

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

                    nb_eval++;

                    if(nb_iteration <= nb_eval)
                        goto end;
                }
            }

        }while (nb_iteration > nb_eval);

        end:
        return sol;
    }


    /**
     * Iterated local search implementation
     *
     * @param nb_iteration : number of iteration for ILS
     * @param nb_hc_iteration : number of iteration for each HC first improvement
     * @param perturbation : number of element permute to create new solution
     * @return the best solution found
     */
    C* IteratedLocalSearch(int nb_iteration, int nb_hc_iteration, int perturbation) {
        int nb_eval = 0;

        C *s;
        C *best = new C(this->size);

        do{
            s = C::copy(best);
            s->swapIndex(perturbation);

            C *n = this->HillClimberFirstImprovement(nb_hc_iteration, s);

            if(this->checkSolution(best, n)){
                best = C::copy(n);
                delete n;
            }

            cout << "ILS " << ((double)nb_eval*100.0)/nb_iteration << "%" << endl;

            nb_eval++;

        }while (nb_iteration > nb_eval);

        cout << "100.000%" << endl;

        return best;
    }

    /**
     * Tabu search implementation
     * @param nb_iteration
     * @return
     */
    C* TabuSearch(int nb_iteration){
        /*
        sBest ← s0
        tabuList ← []
        tabuList.push(s0)
        while (not stoppingCondition())
         	sNeighborhood ← getNeighbors(bestCandidate)
            bestCandidate ← sNeighborHood.firstElement
            for (sCandidate in sNeighborhood)
                if ( (not tabuList.contains(sCandidate)) and (fitness(sCandidate) > fitness(bestCandidate)) )
                    bestCandidate ← sCandidate
                end
            end
            if (fitness(bestCandidate) > fitness(sBest))
                sBest ← bestCandidate
            end
            tabuList.push(bestCandidate)
            if (tabuList.size > maxTabuSize)
                tabuList.removeFirst()
            end
        end
        return sBest
        */
    }

};


#endif //METAHEURISTICS_HEURISTICS_H
