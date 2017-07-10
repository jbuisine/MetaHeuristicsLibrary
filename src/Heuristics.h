//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_HEURISTICS_H
#define METAHEURISTICS_HEURISTICS_H


#include <functional>
#include <vector>
#include "Solution.h"

using namespace std;

class Heuristics {

private:
    vector<function<double(Solution)>> funcs;
    int s_size;

public:
    vector<Solution> RandomWalk(int nb_iteration);
    vector<Solution> HillClimberFirstImprovment(int nb_iteration);
    vector<Solution> HillClimberBestImprovment(int nb_iteration);

    Heuristics(vector<function<double(Solution)>> f, int s_size);
};


#endif //METAHEURISTICS_HEURISTICS_H
