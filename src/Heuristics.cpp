//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include <iostream>
#include "Heuristics.h"


Heuristics::Heuristics(bool problem_type, vector<function<double(Solution*)>> f, int s_size) {
    this->funcs = f;
    this->s_size = s_size;
    this->problem_type = problem_type;
}

bool Heuristics::checkNeighborsExists(vector<Solution> sols, Solution s) {
    bool check = false;

    for (int i = 0; i < sols.size(); ++i) {
        if(sols[i].getArr() == s.getArr()){
            check = true;
            break;
        }
    }

    return check;
}

template <typename T> vector<Solution> Heuristics::getNeighbors(Solution s) {
    vector<Solution> sols;

    sols.push_back(s);

    for (int i = 0; i < s.getArr().size(); ++i) {
        for (int j = 0; j < s.getArr().size(); ++j) {

            vector<int> newest = s.getArr();

            int old_val = newest[i];
            newest[i] = newest[j];
            newest[j] = old_val;

            Solution *n = new T(newest);
            if(!this->checkNeighborsExists(sols, *n)) sols.push_back(*n);
        }
    }

    sols.erase(sols.begin());

    return sols;
}

vector<Solution> Heuristics::getNonDominatedSols(vector<Solution> sols, vector<function<double(Solution*)>> funcs) {

    return sols;
}

bool Heuristics::checkSolution(vector<function<double(Solution*)>> funcs, Solution o, Solution n) {

    int counter = 0;

    for (int i = 0; i < funcs.size(); ++i) {

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

        vector<Solution> neighbors = this->getNeighbors<T>(*s);

        for (int i = 0; i < neighbors.size(); ++i) {

            if(this->checkSolution(funcs, *s, neighbors[i])){
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

/**
 * Implementation of HC best improvement for combinatory problem solution
 * @param nb_iteration
 * @return Solution object : the best solution found
 */
template Solution* Heuristics::HillClimberBestImprovement<CombinatorySolution>(int nb_iteration);
