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

        fillRandomSolution();
    }

    /**
    * Method used for define a suit of int randomly distributed
    * @param this->size : number of element into array solution
    *
    */
    void fillRandomSolution() {

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

    /**
     * Method used for check if solution already exists into a set of solution
     * @param sols : set of all solutions
     * @param s : solution to check
     * @return boolean : True if solution exists, otherwise False
     */
    Solution<T>* getNeighbor(Solution<T>* sol, int i, int j) {

        Solution<T> *newest = (Solution<T>*)CombinatorySolution<T>::copy((CombinatorySolution<T>*)sol);
        newest->getArr()[i] = !(bool)newest->getArr()[i];

        return newest;
    }

    /**
     * Check if to solutions are equivalents
     *
     * @param Solution<T> a : Solution A
     * @param Solution<T> b	: Solution B
     *
     * @return bool
     */
    Solution<T>* crossover(Solution<T> *sol) {

        // Getting information
        int splitIndex = (rand() % this->size);

        Solution<T>* child = new BinaryCombinatorySolution<T>(this->size);

        // Setting new binary solution
        for(int i(0); i < this->size; i++){
            if(i > splitIndex){
                child->setArr(i, this->getArr(i));
            }else{
                child->setArr(i, sol->getArr(i));
            }
        }

        return child;
    }
};


#endif //METAHEURISTICS_BINARYCOMBINATORYSOLUTION_H
