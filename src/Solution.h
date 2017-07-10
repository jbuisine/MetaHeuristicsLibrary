//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_SOLUTION_H
#define METAHEURISTICS_SOLUTION_H

#include <vector>

using namespace std;

class Solution {

private:
    vector<int> arr;

public:
    Solution(vector<int> arr);
    Solution(int size);

    void switchIndex(int nb);
    vector<int> getArr();
};


#endif //METAHEURISTICS_SOLUTION_H
