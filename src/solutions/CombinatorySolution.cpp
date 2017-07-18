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
CombinatorySolution::CombinatorySolution(vector<int> arr) : Solution(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of int randomly distributed
 * @param size : number of element into array solution
 */
CombinatorySolution::CombinatorySolution(int size) : Solution(){

    vector<int> v;

    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }

    this->arr = v;

    this->swapIndex(1000);
}

/**
 * Method used for swap element of array randomly
 * @param nb : number of expected swap
 */
void CombinatorySolution::swapIndex(int nb) {

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
vector<Solution> CombinatorySolution::getNeighbors() {
    vector<Solution> sols;

    sols.push_back(*this);

    for (int i = 0; i < this->getArr().size(); ++i) {
        for (int j = 0; j < this->getArr().size(); ++j) {

            vector<int> newest = this->getArr();

            int old_val = newest[i];
            newest[i] = newest[j];
            newest[j] = old_val;

            Solution *n = new CombinatorySolution(newest);
            if(!Utilities::checkExists(sols, *n)) sols.push_back(*n);
        }
    }

    sols.erase(sols.begin());

    return sols;
}

