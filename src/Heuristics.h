//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include <functional>
#include <vector>
#include "solutions/CombinatorySolution.h"
#include "solutions/Solution.h"
#include "solutions/BinaryCombinatorySolution.h"

template<typename T, std::size_t N> class Heuristics {

private:
    /**
     * 'false' specify minimizing problem and 'true' maximizing
     */
    bool problem_type;

    vector<function<double(T*)>> funcs;

    int s_size;

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    Heuristics(bool problem_type, vector<function<double(T*)>> funcs, int size);

    /**
     * Method used for getting all non dominated solutions from set of solutions
     *
     * @param sols : the set of solutions
     * @return solutions : new set of non dominated solutions
     */
    vector<T> getNonDominatedSols(vector<T> sols);

    /**
     * Method which check the solution dominance
     * @param o : the older solution
     * @param n = the new solution
     * @return True if new solution dominate the older
     */
    bool checkSolution(T o, T n);

    /**
     * Method which check the solution dominance
     * @param scores : scores of the older solution
     * @param n = the new solution
     * @return True if new solution dominate the older
     */
    bool checkSolution(vector<double> scores, T n);

    /**
     *  HillClimberBestImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : Number of iteration expected for the HC best improvement
     * @return Solution object : the best solution found
     */
    T* HillClimberBestImprovement(int nb_iteration, T *s = NULL);

    /**
     *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : Number of iteration expected for the HC first improvement
     * @return Solution object : the best solution found
     */
    T* HillClimberFirstImprovement(int nb_iteration, T *s = NULL);

    /**
     * Iterated local search implementation
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : number of iteration for ILS
     * @param nb_hc_iteration : number of iteration for each HC first improvement
     * @param perturbation : number of element permute to create new solution
     * @return the best solution found
     */
    T* IteratedLocalSearch(int nb_iteration, int nb_hc_iteration, int perturbation);
};


#endif //METAHEURISTICS_HEURISTICS_H
