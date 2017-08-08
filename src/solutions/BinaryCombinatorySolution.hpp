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
      * Copy solution content (array)
      * @param combinatorySolution : solution
      */
    static BinaryCombinatorySolution<T>* copy(BinaryCombinatorySolution<T>* binaryCombinatorySolution){
        BinaryCombinatorySolution<T>* result = new BinaryCombinatorySolution<T>(binaryCombinatorySolution->getSize());

        for (int i = 0; i < binaryCombinatorySolution->size; ++i) {
            result->arr[i] = binaryCombinatorySolution->arr[i];
        }

        return result;
    }

    /**
     * Method used for getting all neighbors solutions of the solution
     * @return vector : all neighbor solutions
     */
    vector<Solution<T>*>* getNeighbors() {

        vector<Solution<T>*>* sols = new vector<Solution<T>*>();

        sols->push_back(this);

        for (int i = 0; i < this->size; ++i) {

            Solution<T> *newest =  (Solution<T>*)BinaryCombinatorySolution<T>::copy(this);

            newest->getArr()[i] = !(bool)newest->getArr()[i];

            sols->push_back(newest);
        }

        sols->erase(sols->begin());

        return sols;
    }

    Solution<T>* getNeighbor(Solution<T>* sol, int i, int j) {

        Solution<T> *newest = (Solution<T>*)CombinatorySolution<T>::copy((CombinatorySolution<T>*)sol);
        newest->getArr()[i] = !(bool)newest->getArr()[i];

        return newest;
    }
};


#endif //METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H
