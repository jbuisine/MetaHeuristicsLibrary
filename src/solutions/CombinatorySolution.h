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

    /**
     * Constructor used for setting arr
     * @param arr : array solution
     */
    CombinatorySolution(vector<int> arr);

    /**
     * Constructor used for define a suit of int randomly distributed
     * @param size : number of element into array solution
     */
    CombinatorySolution(int size);

    /**
     * Method used for swap element of array randomly
     * @param nb : number of expected swap
     */
    void swapIndex(int nb);

    /**
     * Method used for getting all neighbors solutions of the solution
     * @return vector : all neighbor solutions
     */
    vector<Solution> getNeighbors();

private:

    /**
    * Method used for check if neighbors solution already exists
    * @param sols : set of all solutions
    * @param s : solution to check
    * @return boolean : True if solution exists, otherwise False
    */
    bool checkNeighborsExists(vector<Solution> sols, Solution s);

};


#endif //METAHEURISTICS_COMBINATORYSOLUTION_H
