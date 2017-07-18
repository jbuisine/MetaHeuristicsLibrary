//
// Created by Jérôme BUISINE on 11/07/2017.
//

#include <iostream>
#include "Solution.h"

/**
 * Constructor used for creating new solution
 */
Solution::Solution() {
    srand((unsigned int) time(0));
}

// TODO need to change to Array of int to increase performance

/**
 * Getter of arr attribute
 * @return arr : Solution array
 */
vector<int> Solution::getArr() {
    return this->arr;
}

/**
 * Destructor
 */
Solution::~Solution() {}

/**
 * Method used for swap and permute index values
 * @param nb : number of swap expected
 */
void Solution::swapIndex(int nb) {};

/**
* Method used for getting all neighbors solution of current solution
* @tparam T : Template object Type, subclass of Solution
* @param s
* @return
*/
vector<Solution> Solution::getNeighbors() {}

/**
 * Method used for display solution
 */
void Solution::displaySolution() {
    cout << "[";

    for (int j = 0; j < this->arr.size(); ++j) {
        if(j != this->arr.size()-1)
            cout << this->arr[j] << ",";
        else
            cout << this->arr[j];
    }
    cout << "]" << endl;
}