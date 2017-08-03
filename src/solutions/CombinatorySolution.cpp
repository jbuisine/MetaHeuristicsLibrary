//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include <cmath>
#include <iostream>
#include "CombinatorySolution.h"
#include "../Utilities.h"

/**
 * Constructor used for setting arr
 * @param arr : array solution
 */
template<typename T, size_t N> CombinatorySolution<T, N>::CombinatorySolution(T* arr) : Solution<T, N>(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of int randomly distributed
 * @param this->size : number of element into array solution
 */
template<typename T, size_t N> CombinatorySolution<T, N>::CombinatorySolution() : Solution<T, N>(){

    for (int i = 0; i < this->size; ++i) {
        this->arr[i] = i;
    }

    this->swapIndex(1000);
}

/**
 * Method used for swap element of array randomly
 * @param nb : number of expected swap
 */
template<typename T, size_t N> void CombinatorySolution<T, N>::swapIndex(int nb) {

    for (int i = 0; i < nb; ++i) {
        int first_index = (rand() % (this->size));
        int second_index = (rand() % (this->size));

        int old_val = this->arr[first_index];
        this->arr[first_index] = this->arr[second_index];
        this->arr[second_index] = old_val;
    }
}

/**
 * Method used for getting all neighbors solutions of the solution
 * @return vector : all neighbor solutions
 */
template<typename T, size_t N> vector<Solution<T, N>> CombinatorySolution<T, N>::getNeighbors() {
    vector<Solution<T, N>> sols;

    sols.push_back(*this);

    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {

            T newest = this->arr;

            int old_val = newest[i];
            newest[i] = newest[j];
            newest[j] = old_val;

            Solution<T, N> *n = new CombinatorySolution<T, N>(newest);
            if(!Utilities<T>::checkExists(sols, *n)) sols.push_back(*n);
        }
    }

    sols.erase(sols.begin());

    return sols;
}


/**
 * Method used for display solution
 */
template<typename T, size_t N> void Solution<T, N>::displaySolution() {
    cout << "[";

    for (int j = 0; j < this->size; ++j) {
        if(j != this->size-1)
            cout << this->arr[j] << ",";
        else
            cout << this->arr[j];
    }
    cout << "]" << endl;
}
