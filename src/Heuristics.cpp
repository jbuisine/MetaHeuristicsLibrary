//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include "Heuristics.h"

Heuristics::Heuristics(vector<function<double(Solution)>> f, int s_size) {
    this->funcs = f;
    this->s_size = s_size
}

vector<Solution> Heuristics::HillClimberBestImprovment(int nb_iteration) {
    int nb_eval = 0;

    Solution s = Solution(this->s_size);

    do{


        nb_eval++;
    }while (nb_iteration >= nb_eval);
}