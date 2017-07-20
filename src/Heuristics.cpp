//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include <iostream>
#include "Heuristics.h"
#include "Utilities.h"

/**
 * Initialization of context
 * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
 * @param f : objective function(s)
 * @param s_size : size of problem solution
 */
template<typename T, size_t N> Heuristics<T, N>::Heuristics(bool problem_type, vector<function<double(T*)>> f, int s_size) {
    this->funcs = f;
    this->s_size = s_size;
    this->problem_type = problem_type;
}

/**
 * Method used for getting all non dominated solutions from set of solutions
 *
 * @param sols : the set of solutions
 * @return solutions : new set of non dominated solutions
 */
template<typename T, size_t N> vector<T> Heuristics<T, N>::getNonDominatedSols(vector<T> sols) {

    vector<T> solutions;

    for (int i = 0; i < sols.size(); ++i) {

        vector<double> scores;

        // Store scores of i solution to avoid redundant compute statements
        for (int j = 0; j < this->funcs.size(); ++j)
            scores.push_back(this->funcs[j](&sols[i]));

        for (int j = 0; j < sols.size(); ++j) {

            if(this->checkSolution(scores, sols[j]) && !Utilities<N>::checkExists(solutions, sols[i]))
                solutions.push_back(sols[i]);
        }
    }

    return solutions;
}

/**
 * Method which check the solution dominance
 * @param o : the older solution
 * @param n = the newest solution
 * @return
 */
template<typename T, size_t N> bool Heuristics<T, N>::checkSolution(T o, T n) {

    int counter = 0;

    for (int i = 0; i < this->funcs.size(); ++i) {

        if(this->problem_type){
            if(funcs[i](&n) >= funcs[i](&o)) counter ++;
        }
        else{
            if(funcs[i](&n) <= funcs[i](&o)) counter ++;
        }
    }

    return counter == funcs.size();
}

/**
  * Method which check the solution dominance
  * @param scores : scores of the older solution
  * @param n = the new solution
  * @return True if new solution dominate the older
  */
template<typename T, size_t N> bool Heuristics<T, N>::checkSolution(vector<double> scores, T n){

    int counter = 0;

    for (int i = 0; i < this->funcs.size(); ++i) {

        if(this->problem_type){
            if(funcs[i](&n) >= scores[i]) counter ++;
        }
        else{
            if(funcs[i](&n) <= scores[i]) counter ++;
        }
    }

    return counter == funcs.size();
}

/**
 *  HillClimberBestImprovement implementation with possibility to use multiple objective or single objective scalarizing method
 *
 * @tparam T : Template object Type, subclass of Solution
 * @param nb_iteration : Number of iteration expected for the HC best improvement
 * @return Solution object : the best solution found
 */
template<typename T, size_t N> T* Heuristics<T, N>::HillClimberBestImprovement(int nb_iteration, T *s) {
    int nb_eval = 0;

    T *sol;

    if(s)
        sol = s;
    else
        sol = new T(this->s_size);

    do{
        vector<double> scores;

        // Store scores to avoid redundant compute statements
        for (int j = 0; j < this->funcs.size(); ++j)
            scores.push_back(this->funcs[j](sol));

        // Getting neighbor solutions of s
        vector<T> neighbors = sol->getNeighbors();

        for (int i = 0; i < neighbors.size(); ++i) {

            if(this->checkSolution(scores, neighbors[i])){
                delete sol;
                sol = new T(neighbors[i].getArr());
            }

            nb_eval++;

            if(nb_iteration <= nb_eval)
                break;
        }

    }while (nb_iteration > nb_eval);

    return sol;
}

//template<size_t N> T* Heuristics<CombinatorySolution, N>::HillClimberBestImprovement(int nb_iteration, T *s);

//template<size_t N> T* Heuristics<BinaryCombinatorySolution, N>::HillClimberBestImprovement(int nb_iteration, T *s);


/**
 *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
 *
 * @tparam T : Template object Type, subclass of Solution
 * @param nb_iteration : Number of iteration expected for the HC first improvement
 * @return Solution object : the best solution found
 */
template<typename T, size_t N> T* Heuristics<T, N>::HillClimberFirstImprovement(int nb_iteration, T *s) {
    int nb_eval = 0;

    T *sol;

    if(s)
        sol = s;
    else
        sol = new T(this->s_size);

    do{
        vector<double> scores;

        // Store scores to avoid redundant compute statements
        for (int j = 0; j < this->funcs.size(); ++j)
            scores.push_back(this->funcs[j](sol));

        // Getting neighbor solutions of s
        vector<T> neighbors = sol->getNeighbors();

        for (int i = 0; i < neighbors.size(); ++i) {

            // Break if new solution is better
            if(this->checkSolution(scores, neighbors[i])){
                delete sol;
                sol = new T(neighbors[i].getArr());
                break;
            }

            nb_eval++;

            if(nb_iteration <= nb_eval)
                break;
        }

    }while (nb_iteration > nb_eval);

    return sol;
}

//template<size_t N> T* Heuristics<CombinatorySolution, N>::HillClimberFirstImprovement(int nb_iteration, T *s);

//template<size_t N> T* Heuristics<BinaryCombinatorySolution, N>::HillClimberFirstImprovement(int nb_iteration, T *s);

/**
 * Iterated local search implementation
 *
 * @tparam T : Template object Type, subclass of Solution
 * @param nb_iteration : number of iteration for ILS
 * @param nb_hc_iteration : number of iteration for each HC first improvement
 * @param perturbation : number of element permute to create new solution
 * @return the best solution found
 */
template<typename T, size_t N> T* Heuristics<T, N>::IteratedLocalSearch(int nb_iteration, int nb_hc_iteration, int perturbation) {
    int nb_eval = 0;

    T *s = new T(this->s_size);
    T *best = new T(s->getArr());

    do{

        s->swapIndex(perturbation);

        T *n = this->HillClimberFirstImprovement(nb_hc_iteration, new T(s->getArr()));

        if(this->checkSolution(*best, *n)){
            delete s, best;
            best = new T(n->getArr());
            s = new T(n->getArr());
            delete n;
        }

        nb_eval++;

    }while (nb_iteration > nb_eval);

    return best;
}

//template<size_t N> T* Heuristics<CombinatorySolution, N>::IteratedLocalSearch(int nb_iteration, int nb_hc_iteration, int perturbation);

//template<size_t N> T* Heuristics<BinaryCombinatorySolution, N>::IteratedLocalSearch(int nb_iteration, int nb_hc_iteration, int perturbation);