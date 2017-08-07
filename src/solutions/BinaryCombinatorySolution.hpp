//
// Created by Jérôme BUISINE on 17/07/2017.
//

#ifndef METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H
#define METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H

#include "Solution.hpp"

template<typename T>
class BinaryCombinatorySolution : public Solution<T>{

public:

    /**
     * Constructor used for setting arr
     * @param arr : array solution
     */
    BinaryCombinatorySolution(int s) : Solution<T>(s){

        for (int i = 0; i < this->size; ++i) {
            this->arr[i] = 0;
        }

        this->swapIndex(1000);
    }

    /**
     * Method used for swap element of array randomly
     * @param nb : number of expected swap
     */
    void swapIndex(int nb) {

        for (int i = 0; i < nb; ++i) {
            int index = (rand() % this->size);

            this->arr[index] = !(bool)this->arr[index];
        }
    }

    /**
     * Method used for getting all neighbors solutions of the solution
     * @return vector : all neighbor solutions
     */
    vector<Solution<T>*>* getNeighbors() {

        vector<Solution<T>*>* sols = new vector<Solution<T>*>();

        sols->push_back(this);

        for (int i = 0; i < this->size; ++i) {

            // TODO check memory possible issues
            T newest = this->arr;

            newest[i] = !(bool)newest[i];

            Solution<T> *n = new BinaryCombinatorySolution<T>(newest);
            sols->push_back(n);
        }

        sols->erase(sols->begin());

        return sols;
    }
};


#endif //METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H
