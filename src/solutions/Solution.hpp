//
// Created by Jérôme BUISINE on 11/07/2017.
//

#ifndef METAHEURISTICS_SOLUTION_H
#define METAHEURISTICS_SOLUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <array>
#include <vector>
#include <iostream>

using namespace std;

//Type called "Fitness" => double function(long: memory address of solution)
typedef double (*Fitness)(long);

/**
 * Solution class : template of solution
 */
template<typename T>
class Solution {

public:

    /**
    * Method used for define a suit of int randomly distributed
    * @param this->size : number of element into array solution
    *
    */
    virtual void fillRandomSolution() = 0;

    /**
	* Compy constructor used for setting arr
	* @param arr : array solution
	*/
    void copyArr(T* arr, int s){

        delete this->arr;

        this->arr = (T*)(malloc(sizeof(T) * s));
        this->size = s;

        for (int i = 0; i < this->size; ++i) {
            this->arr[i] = arr[i];
        }
    }

    /**
     * Destructor
     */
    virtual ~Solution(){ delete arr; }

    /**
     * Getter of arr attribute
     * @return arr : Solution array
     */
    inline T* getArr(){
        return arr;
    };

    /**
     * Getter of arr attribute
     * @return arr : Solution array
     */
    inline T getArr(int i){
        return arr[i];
    };

    inline void setArr(int i, T v){
        arr[i] = v;
    };

    /**
     * Method used for swap and permute index values
     * @param nb : number of swap expected
     */
    virtual void swapIndex(int nb) {
        for (int i = 0; i < nb; ++i) {
            int first_index = (rand() % (this->size));
            int second_index = (rand() % (this->size));

            int old_val = this->arr[first_index];
            this->arr[first_index] = this->arr[second_index];
            this->arr[second_index] = old_val;
        }
    }

    /**
     * Method used for getting all neighbors solution of current solution
     * @tparam T : Template object Type, subclass of Solution
     * @param s
     * @return
     */
    virtual vector<Solution<T>*>* getNeighbors() = 0;

    /**
     * Neighbor of specific index position
     *
     * @param sol
     * @param i
     * @param j
     * @return
     */
    virtual Solution<T>* getNeighbor(Solution<T>* sol, int i, int j) = 0;

    /**
     * Generate new solution using crossove
     *
     * @param sol
     * @return new solution generated
     */
    virtual Solution<T>* crossover(Solution<T>* sol) = 0;

    /**
     * Method used for display solution
     */
    void displaySolution() {
        cout << "[";

        for (int j = 0; j < this->size; ++j) {
            if(j != this->size-1)
                cout << this->arr[j] << ",";
            else
                cout << this->arr[j];
        }
        cout << "]";
    }

    /**
     * Method which returns size of solution
     *
     * @return size of arr
     */
    int getSize(){
        return size;
    };

protected:

    T* arr;

    int size;

    /**
     * Constructor used for creating new solution
     */
    Solution(int s) {
        arr = (T*)(malloc(sizeof(T) * s));
        size = s;
    }

    /**
    * Method used for check if solution already exists into a set of solution
    * @param sols : set of all solutions
    * @param s : solution to check
    * @return boolean : True if solution exists, otherwise False
    */
    bool checkExists(vector<Solution<T>*>* sols, Solution<T>* s) {
        auto t = (int)sols->size();
        for (int i = 0; i < t; ++i) {

            //Unavailable for primitive types
            if (sameSolution(sols->at(i), s)){
                return true;
            }
        }
        return false;
    }

    /**
     * Check if to solutions are equivalents
     *
     * @param Solution<T> a : Solution A
     * @param Solution<T> b	: Solution B
     *
     * @return bool
     */
    static bool sameSolution(Solution<T>* a, Solution<T>* b){
        for (unsigned int i = 0; i < a->size; ++i) {
            if (a->arr[i] != b->arr[i]){
                return false;
            }
        }
        return true;
    }

};


#endif //METAHEURISTICS_SOLUTION_H
