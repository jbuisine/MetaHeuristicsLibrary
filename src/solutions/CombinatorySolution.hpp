//
// Created by Jérôme BUISINE on 10/07/2017.
//

#ifndef METAHEURISTICS_COMBINATORYSOLUTION_H
#define METAHEURISTICS_COMBINATORYSOLUTION_H

#include "Solution.hpp"

template<typename T>
class CombinatorySolution : public Solution<T> {

public:

    /**
     * Constructor used for setting arr
     * @param arr : array solution
     */
    CombinatorySolution(int s) : Solution<T>(s){}

    /**
	* Compy constructor used for setting arr
	* @param arr : array solution
	*/
    static CombinatorySolution<T>* copy(CombinatorySolution<T>* combinatorySolution){
        CombinatorySolution<T>* result = new CombinatorySolution<T>(combinatorySolution->getSize());

        for (int i = 0; i < combinatorySolution->size; ++i) {
            result->arr[i] = combinatorySolution->arr[i];
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
            for (int j = 0; j < this->size; ++j) {

                Solution<T> *newest = (Solution<T>*)CombinatorySolution<T>::copy(this);
                T old_val = newest->getArr(i);
                newest->setArr(i, newest->getArr(j));
                newest->setArr(j, old_val);

                if (!this->checkExists(sols, newest))
                    sols->push_back(newest);
            }
        }

        sols->erase(sols->begin());

        return sols;
    }


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
        cout << "]" << endl;
    }
};


#endif //METAHEURISTICS_COMBINATORYSOLUTION_H
