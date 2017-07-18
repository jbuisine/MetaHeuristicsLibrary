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

using namespace std;

class Heuristics {

private:
    /**
     * 'false' specify minimizing problem and 'true' maximizing
     */
    bool problem_type;

    vector<function<double(Solution*)>> funcs;

    int s_size;

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    Heuristics(bool problem_type, vector<function<double(Solution*)>> funcs, int size);

    /**
     * Method used for getting all non dominated solutions from set of solutions
     *
     * @param sols : the set of solutions
     * @return solutions : new set of non dominated solutions
     */
    vector<Solution> getNonDominatedSols(vector<Solution> sols);

    /**
     * Method which check the solution dominance
     * @param o : the older solution
     * @param n = the newest solution
     * @return
     */
    bool checkSolution(Solution o, Solution n);

    /**
     *  HillClimberBestImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : Number of iteration expected for the HC best improvement
     * @return Solution object : the best solution found
     */
    template <typename T> Solution* HillClimberBestImprovement(int nb_iteration);

    /**
     *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
     *
     * @tparam T : Template object Type, subclass of Solution
     * @param nb_iteration : Number of iteration expected for the HC first improvement
     * @return Solution object : the best solution found
     */
    template <typename T> Solution* HillClimberFirstImprovement(int nb_iteration);
};


#endif //METAHEURISTICS_HEURISTICS_H
