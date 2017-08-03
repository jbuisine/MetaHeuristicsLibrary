//
// Created by Jérôme BUISINE on 17/07/2017.
//

#include <cmath>
#include <iostream>
#include "BinaryCombinatorySolution.h"

/**
 * Constructor used for setting arr
 * @param arr
 */
template<typename T, size_t N>  BinaryCombinatorySolution<T, N>::BinaryCombinatorySolution(T* arr) : Solution<T, N>(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of random 0 and 1
 */
template<typename T, size_t N>  BinaryCombinatorySolution<T, N>::BinaryCombinatorySolution() : Solution<T, N>(){

    for (int i = 0; i < this->size; ++i) {
        this->arr[i] = 0;
    }

    this->swapIndex(1000);
}

/**
 * Method used for swap element of array randomly
 * @param nb : number of expected swap
 */
template<typename T, size_t N>  void BinaryCombinatorySolution<T, N>::swapIndex(int nb) {

    for (int i = 0; i < nb; ++i) {
        int index = (rand() % this->size);

        this->arr[index] = !(bool)this->arr[index];
    }
}

/**
 * Method used for getting all neighbors solutions of the solution
 * @return vector : all neighbor solutions
 */
template<typename T, size_t N>  vector<Solution<T, N>> BinaryCombinatorySolution<T, N>::getNeighbors() {
    vector<Solution<T, N>> sols;

    sols.push_back(*this);

    for (int i = 0; i < this->size; ++i) {

        // TODO check memory possible issues
        T newest = this->arr;

        newest[i] = !(bool)newest[i];

        Solution<T, N> *n = new BinaryCombinatorySolution<T, N>(newest);
        sols.push_back(*n);
    }

    sols.erase(sols.begin());

    return sols;
}