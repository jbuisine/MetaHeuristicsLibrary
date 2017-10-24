//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include "../utils/Utils.hpp"
#include "Utilities.hpp"
#include <algorithm>

template<typename C>
class Heuristics {

public:

    /**
      * Method which check the solution dominance
      * @param scores : scores of the older solution
      * @param n = the new solution
      * @return True if new solution dominate the older
      */
    bool checkSolution(vector<double>* scores, C* n){

        int counter = 0;

        size_t s =  this->funcs.size();

        for (int i = 0; i < s; ++i) {

            if(this->problem_type){
                if(funcs[i]((long)n) >= scores->at(i)) counter++;
            }
            else{
                if(funcs[i]((long)n) <= scores->at(i)) counter++;
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

    int getProblemSize(){
        return size;
    }

    bool getProblemType(){
        return problem_type;
    }

    vector<Fitness> getFunctions(){
        return funcs;
    }

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

            auto scores = new std::vector<double>();

            // Store scores of i solution to avoid redundant compute statements
            for (int j = 0; j < this->funcs.size(); ++j)
                scores->push_back(this->funcs[j](sols->at(i)));

            for (int j = 0; j < sols->size(); ++j) {

                if(this->checkSolution(scores, sols->at(j)) && !Utilities<C>::checkExists(solutions, sols->at(i)))
                    solutions->push_back(sols[i]);
            }

            delete scores;
        }

        return solutions;
    }
};


#endif //METAHEURISTICS_HEURISTICS_H
