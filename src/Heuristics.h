//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include <functional>
#include <vector>
#include "solutions/CombinatorySolution.h"
#include "solutions/Solution.h"

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

    template <typename T> vector<Solution> getNeighbors(Solution s);

    vector<Solution> getNonDominatedSols(vector<Solution> sols, vector<function<double(Solution*)>> funcs);

    bool checkSolution(vector<function<double(Solution*)>> funcs, Solution o, Solution n);

    bool checkNeighborsExists(vector<Solution> sols, Solution s);

    template <typename T> Solution* HillClimberBestImprovement(int nb_iteration);

    Heuristics(bool problem_type, vector<function<double(Solution*)>> funcs, int size);
};


#endif //METAHEURISTICS_HEURISTICS_H
