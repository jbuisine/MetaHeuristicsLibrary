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
BinaryCombinatorySolution::BinaryCombinatorySolution(vector<int> arr) : Solution(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of random 0 and 1
 * @param size : number of element into array solution
 */
BinaryCombinatorySolution::BinaryCombinatorySolution(int size) : Solution(){

    vector<int> v;

    for (int i = 0; i < size; ++i) {
        v.push_back(0);
    }

    this->arr = v;

    this->swapIndex(1000);
}

/**
 * Method used for swap element of array randomly
 * @param nb : number of expected swap
 */
void BinaryCombinatorySolution::swapIndex(int nb) {

    for (int i = 0; i < nb; ++i) {
        int index = (int) (rand() % (this->arr.size()));

        this->arr[index] = !(bool)this->arr[index];
    }
}

/**
 * Method used for getting all neighbors solutions of the solution
 * @return vector : all neighbor solutions
 */
vector<Solution> BinaryCombinatorySolution::getNeighbors() {
    vector<Solution> sols;

    sols.push_back(*this);

    for (int i = 0; i < this->getArr().size(); ++i) {

        vector<int> newest = this->getArr();

        newest[i] = !(bool)newest[i];

        Solution *n = new BinaryCombinatorySolution(newest);
        sols.push_back(*n);
    }

    sols.erase(sols.begin());

    return sols;
}