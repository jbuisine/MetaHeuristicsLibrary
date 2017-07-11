//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_COMBINATORYSOLUTION_H
#define METAHEURISTICS_COMBINATORYSOLUTION_H

#include <vector>
#include "Solution.h"

using namespace std;

class CombinatorySolution : public Solution {

public:

    CombinatorySolution(vector<int> arr);

    CombinatorySolution(int size);

    void swapIndex(int nb);
};


#endif //METAHEURISTICS_COMBINATORYSOLUTION_H
