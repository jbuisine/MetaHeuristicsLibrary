//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include <cmath>
#include <iostream>
#include "CombinatorySolution.h"

/**
 * Constructor used for setting arr
 * @param arr
 */
CombinatorySolution::CombinatorySolution(vector<int> arr) : Solution(){
    this->arr = arr;
}

/**
 * Constructor used for define a suit of int
 * @param size
 */
CombinatorySolution::CombinatorySolution(int size) : Solution(){

    vector<int> v;
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }

    this->arr = v;
}

/**
 * Method used for swap element of array randomly
 * @param nb
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

