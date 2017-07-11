//
// Created by Jérôme BUISINE on 11/07/2017.
//

#include <iostream>
#include "Solution.h"

/**
 * Constructor used for implement kind of solution
 * @param problem_type
 */
Solution::Solution() {
    srand((unsigned int) time(0));
}

/**
 * Getter of arr attribute
 * @return
 */
vector<int> Solution::getArr() {
    return this->arr;
}
