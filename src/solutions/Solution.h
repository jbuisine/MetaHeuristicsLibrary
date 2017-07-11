//
// Created by Jérôme BUISINE on 11/07/2017.
//

#ifndef METAHEURISTICS_SOLUTION_H
#define METAHEURISTICS_SOLUTION_H

#include <vector>

using namespace std;

class Solution {

public:

    vector<int> getArr();

protected:

    vector<int> arr;

    Solution();

    void swapIndex(int nb);

};


#endif //METAHEURISTICS_SOLUTION_H
