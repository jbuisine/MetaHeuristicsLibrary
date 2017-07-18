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
Heuristics::Heuristics(bool problem_type, vector<function<double(Solution*)>> f, int s_size) {
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
vector<Solution> Heuristics::getNonDominatedSols(vector<Solution> sols) {

    vector<Solution> solutions;

    for (int i = 0; i < sols.size(); ++i) {
        for (int j = 0; j < sols.size(); ++j) {

            if(this->checkSolution(sols[i], sols[j]) && !Utilities::checkExists(solutions, sols[i]));
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
bool Heuristics::checkSolution(Solution o, Solution n) {

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
 *  HillClimberBestImprovement implementation with possibility to use multiple objective or single objective scalarizing method
 *
 * @tparam T : Template object Type, subclass of Solution
 * @param nb_iteration : Number of iteration expected for the HC best improvement
 * @return Solution object : the best solution found
 */
template <class T> Solution* Heuristics::HillClimberBestImprovement(int nb_iteration) {
    int nb_eval = 0;

    Solution *s = new T(this->s_size);

    do{

        vector<Solution> neighbors = s->getNeighbors();

        for (int i = 0; i < neighbors.size(); ++i) {

            if(this->checkSolution(*s, neighbors[i])){
                delete s;
                s = new T(neighbors[i].getArr());
            }

            nb_eval++;

            if(nb_iteration <= nb_eval)
                break;
        }

    }while (nb_iteration > nb_eval);

    return s;
}

template Solution* Heuristics::HillClimberBestImprovement<CombinatorySolution>(int nb_iteration);

template Solution* Heuristics::HillClimberBestImprovement<BinaryCombinatorySolution>(int nb_iteration);


/**
 *  HillClimberFirstImprovement implementation with possibility to use multiple objective or single objective scalarizing method
 *
 * @tparam T : Template object Type, subclass of Solution
 * @param nb_iteration : Number of iteration expected for the HC first improvement
 * @return Solution object : the best solution found
 */
template <class T> Solution* Heuristics::HillClimberFirstImprovement(int nb_iteration) {
    int nb_eval = 0;

    Solution *s = new T(this->s_size);

    do{

        vector<Solution> neighbors = s->getNeighbors();

        for (int i = 0; i < neighbors.size(); ++i) {

            // Break if new solution is better 
            if(this->checkSolution(*s, neighbors[i])){
                delete s;
                s = new T(neighbors[i].getArr());
                break;
            }

            nb_eval++;

            if(nb_iteration <= nb_eval)
                break;
        }

    }while (nb_iteration > nb_eval);

    return s;
}

template Solution* Heuristics::HillClimberBestImprovement<CombinatorySolution>(int nb_iteration);

template Solution* Heuristics::HillClimberBestImprovement<BinaryCombinatorySolution>(int nb_iteration);
