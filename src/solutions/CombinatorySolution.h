//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_COMBINATORYSOLUTION_H
#define METAHEURISTICS_COMBINATORYSOLUTION_H

#include <vector>
#include "Solution.h"

using namespace std;

template<typename T, size_t N> class CombinatorySolution : public Solution<T, N> {

public:

    /**
     * Constructor used for setting arr
     * @param arr : array solution
     */
    CombinatorySolution(T* arr[]);

    /**
     * Constructor used for define a suit of int randomly distributed
     */
    CombinatorySolution();

    /**
     * Method used for swap element of array randomly
     * @param nb : number of expected swap
     */
    void swapIndex(int nb);

    /**
     * Method used for getting all neighbors solutions of the solution
     * @return vector : all neighbor solutions
     */
    vector<Solution<T, N>> getNeighbors();
};


#endif //METAHEURISTICS_COMBINATORYSOLUTION_H
