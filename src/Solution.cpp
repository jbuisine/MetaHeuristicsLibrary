//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include <cmath>
#include <iostream>
#include "Solution.h"

Solution::Solution(vector<int> arr) {
    this->arr = arr;
}

Solution::Solution(int size) {
    srand(time(0));

    vector<int> v;
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }

    this->arr = v;
}

void Solution::switchIndex(int nb) {
    for (int i = 0; i < nb; ++i) {
        int first_index = (int) (rand() % (this->arr.size()));
        int second_index = (int) (rand() % (this->arr.size()));

        int old_val = this->arr[first_index];
        this->arr[first_index] = this->arr[second_index];
        this->arr[second_index] = old_val;
    }
}

vector<int> Solution::getArr() {
    return this->arr;
}

