//
// Created by Jérôme BUISINE on 11/07/2017.
//

#include <iostream>
#include "Solution.h"


/**
 * Constructor used for creating new solution
 */
template<size_t N> Solution<N>::Solution() {
    srand((unsigned int) time(0));
}

/**
 * Getter of arr attribute
 * @return arr : Solution array
 */
template<size_t N> array<int, N> Solution<N>::getArr() {
    return this->arr;
}

/**
 * Destructor
 */
template<size_t N> Solution<N>::~Solution() {}

/**
 * Method used for swap and permute index values
 * @param nb : number of swap expected
 */
template<std::size_t N> void Solution<N>::swapIndex(int nb) {};

/**
* Method used for getting all neighbors solution of current solution
* @tparam T : Template object Type, subclass of Solution
* @param s
* @return
*/
template<size_t N> vector<Solution<N>> Solution<N>::getNeighbors() {}
