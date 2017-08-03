//
// Created by Jérôme BUISINE on 11/07/2017.
//

#include <iostream>
#include "Solution.h"


/**
 * Constructor used for creating new solution
 */
template<typename T, size_t N> Solution<T,N>::Solution() {
    srand((unsigned int) time(0));
    size = sizeof(arr) / sizeof(T);
}

/**
 * Getter of arr attribute
 * @return arr : Solution array
 */
template<typename T, size_t N> T* Solution<T, N>::getArr() {
    return arr;
}

/**
 * Destructor
 */
template<typename T, size_t N> Solution<T, N>::~Solution() {}

/**
 * Method used for swap and permute index values
 * @param nb : number of swap expected
 */
template<typename T, size_t N> void Solution<T, N>::swapIndex(int nb) {};

/**
* Method used for getting all neighbors solution of current solution
* @tparam T : Template object Type, subclass of Solution
* @param s
* @return
*/
template<typename T, size_t N> vector<Solution<T, N>> Solution<T, N>::getNeighbors() {}
