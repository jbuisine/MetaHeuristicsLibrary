//
// Created by Jérôme BUISINE on 11/07/2017.
//

#ifndef METAHEURISTICS_SOLUTION_H
#define METAHEURISTICS_SOLUTION_H

#include <vector>

using namespace std;

/**
 * Solution class : template of solution
 */
class Solution {

public:

    /**
     * TODO check if it's perhaps necessary to pass this attribute type to generic type
     *
     * Getter of arr attribute
     * @return arr : Solution array
     */
    vector<int> getArr();

    /**
     * Destructor
     */
    ~Solution();

    /**
     * Method used for swap and permute index values
     * @param nb : number of swap expected
     */
    virtual void swapIndex(int nb);

    /**
     * Method used for getting all neighbors solution of current solution
     * @tparam T : Template object Type, subclass of Solution
     * @param s
     * @return
     */
    virtual vector<Solution> getNeighbors();

    /**
     * Method used for display solution
     */
    void displaySolution();

protected:

    vector<int> arr;

    /**
     * Constructor
     */
    Solution();
};


#endif //METAHEURISTICS_SOLUTION_H
