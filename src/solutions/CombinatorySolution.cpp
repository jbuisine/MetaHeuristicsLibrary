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
template<size_t N> CombinatorySolution<N>::CombinatorySolution(array<int, N> arr) : Solution<N>(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of int randomly distributed
 * @param size : number of element into array solution
 */
template<size_t N> CombinatorySolution<N>::CombinatorySolution() : Solution<N>(){

    array<int, N> v;

    for (int i = 0; i < N; ++i) {
        v[i] = i;
    }

    this->arr = v;

    this->swapIndex(1000);
}

/**
 * Method used for swap element of array randomly
 * @param nb : number of expected swap
 */
template<size_t N> void CombinatorySolution<N>::swapIndex(int nb) {

    for (int i = 0; i < nb; ++i) {
        int first_index = (int) (rand() % (this->arr.size()));
        int second_index = (int) (rand() % (this->arr.size()));

        int old_val = this->arr[first_index];
        this->arr[first_index] = this->arr[second_index];
        this->arr[second_index] = old_val;
    }
}

/**
 * Method used for getting all neighbors solutions of the solution
 * @return vector : all neighbor solutions
 */
template<size_t N> vector<Solution<N>> CombinatorySolution<N>::getNeighbors() {
    vector<Solution<N>> sols;

    sols.push_back(*this);

    for (int i = 0; i < this->getArr().size(); ++i) {
        for (int j = 0; j < this->getArr().size(); ++j) {

            array<int, N> newest = this->getArr();

            int old_val = newest[i];
            newest[i] = newest[j];
            newest[j] = old_val;

            Solution<N> *n = new CombinatorySolution<N>(newest);
            if(!Utilities<N>::checkExists(sols, *n)) sols.push_back(*n);
        }
    }

    sols.erase(sols.begin());

    return sols;
}


/**
 * Method used for display solution
 */
template<size_t N> void Solution<N>::displaySolution() {
    cout << "[";

    for (int j = 0; j < this->arr.size(); ++j) {
        if(j != this->arr.size()-1)
            cout << this->arr[j] << ",";
        else
            cout << this->arr[j];
    }
    cout << "]" << endl;
}
