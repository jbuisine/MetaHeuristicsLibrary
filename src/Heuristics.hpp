//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include "solutions/CombinatorySolution.hpp"
#include "solutions/BinaryCombinatorySolution.hpp"
#include "Utilities.hpp"

template<typename C>
class Heuristics {

private:
    /**
     * 'false' specify minimizing problem and 'true' maximizing
     */
    bool problem_type;

    vector<VoidFunctionLong> funcs;

    int s_size;

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    Heuristics(bool problem_type, vector<VoidFunctionLong>& funcs, int size) {
        this->funcs = funcs;
        this->s_size = size;
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
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : Number of iteration expected for the HC best improvement
     * @return Solution object : the best solution found
     */
    C* HillClimberBestImprovement(int nb_iteration, bool useRandomValue) {
        int nb_eval = 0;
        C *sol = new C(this->s_size);

        do{
            vector<double> scores;

            // Store scores to avoid redundant compute statements
            for (unsigned int j = 0; j < this->funcs.size(); ++j) {
                VoidFunctionLong fnc = (VoidFunctionLong) this->funcs[j];
                double r = fnc((long)sol);
                scores.push_back(r);
            }

            // Getting neighbor solutions of s
            vector<C*>* neighbors = (vector<C*>*)sol->getNeighbors();
            int neighborsSize = (int)neighbors->size();

            for (int i = 0; i < neighbors->size(); ++i) {

                if(this->checkSolution(scores, neighbors->at(i))){
                    sol->copyArr(neighbors->at(i)->getArr(), this->s_size);
                }

                nb_eval++;

                if(nb_iteration <= nb_eval)
                    break;
            }

            delete neighbors;

        }while (nb_iteration > nb_eval);

        return sol;
    }

    /**
     *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : Number of iteration expected for the HC first improvement
     * @return Solution object : the best solution found
     */
    C* HillClimberFirstImprovement(int nb_iteration, C *s) {
        int nb_eval = 0;

        C *sol;

        if(s)
            sol = s;
        else
            sol = new C(this->s_size);

        do{
            vector<double> scores;

            // Store scores to avoid redundant compute statements
            for (int j = 0; j < this->funcs.size(); ++j)
                scores.push_back(this->funcs[j](*sol));

            // Getting neighbor solutions of s
            vector<C*>* neighbors = sol->getNeighbors();

            for (int i = 0; i < neighbors->size(); ++i) {

                // Break if new solution is better
                if(this->checkSolution(scores, neighbors->at(i))) {
                    delete sol;
                    sol->copyArr(neighbors->at(i)->getArr(), this->s_size);
                    break;
                }

                nb_eval++;

                if(nb_iteration <= nb_eval)
                    break;
            }

        }while (nb_iteration > nb_eval);

        return sol;
    }


    /**
     * Iterated local search implementation
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : number of iteration for ILS
     * @param nb_hc_iteration : number of iteration for each HC first improvement
     * @param perturbation : number of element permute to create new solution
     * @return the best solution found
     */
    C* IteratedLocalSearch(int nb_iteration, int nb_hc_iteration, int perturbation) {
        int nb_eval = 0;

        C *s = new C(this->s_size);
        C *best = new C(s->getArr());

        do{

            s->swapIndex(perturbation);

            C *n = this->HillClimberFirstImprovement(nb_hc_iteration, new C(s->getArr()));

            if(this->checkSolution(*best, *n)){
                delete s, best;
                best = new C(n->getArr());
                s = new C(n->getArr());
                delete n;
            }

            nb_eval++;

        }while (nb_iteration > nb_eval);

        return best;
    }

};


#endif //METAHEURISTICS_HEURISTICS_H
