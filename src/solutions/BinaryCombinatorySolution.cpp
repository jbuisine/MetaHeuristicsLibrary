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
template<size_t N> BinaryCombinatorySolution<N>::BinaryCombinatorySolution(array<int, N> arr) : Solution<N>(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of random 0 and 1
 */
template<size_t N> BinaryCombinatorySolution<N>::BinaryCombinatorySolution() : Solution<N>(){

    array<int, N> v;

    for (int i = 0; i < N; ++i) {
        v[i] = 0;
    }

    this->arr = v;

    this->swapIndex(1000);
}

/**
 * Method used for swap element of array randomly
 * @param nb : number of expected swap
 */
template<size_t N> void BinaryCombinatorySolution<N>::swapIndex(int nb) {

    for (int i = 0; i < nb; ++i) {
        int index = (int) (rand() % (this->arr.size()));

        this->arr[index] = !(bool)this->arr[index];
    }
}

/**
 * Method used for getting all neighbors solutions of the solution
 * @return vector : all neighbor solutions
 */
template<size_t N> vector<Solution<N>> BinaryCombinatorySolution<N>::getNeighbors() {
    vector<Solution<N>> sols;

    sols.push_back(*this);

    for (int i = 0; i < this->getArr().size(); ++i) {

        array<int, N> newest = this->getArr();

        newest[i] = !(bool)newest[i];

        Solution<N> *n = new BinaryCombinatorySolution<N>(newest);
        sols.push_back(*n);
    }

    sols.erase(sols.begin());

    return sols;
}