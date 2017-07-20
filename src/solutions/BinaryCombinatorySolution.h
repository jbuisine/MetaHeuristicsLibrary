//
// Created by Jérôme BUISINE on 17/07/2017.
//

#ifndef METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H
#define METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H

#include <vector>
#include "Solution.h"

template<size_t N> class BinaryCombinatorySolution : public Solution<N>{

public:
    /**
     * Constructor used for setting arr
     * @param arr : array solution
     */
    BinaryCombinatorySolution(array<int, N> arr);

    /**
     * Constructor used for define a suit of int randomly distributed
     */
    BinaryCombinatorySolution();

    /**
     * Method used for swap element of array randomly
     * @param nb : number of expected swap
     */
    void swapIndex(int nb);

    /**
     * Method used for getting all neighbors solutions of the solution
     * Permutation of each bit value
     *
     * @return vector : all neighbor solutions
     */
    vector<Solution<N>> getNeighbors();
};


#endif //METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H
