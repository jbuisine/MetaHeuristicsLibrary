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
    CombinatorySolution(int s) : Solution<T>(s){

        for (int i = 0; i < this->size; ++i) {
            this->arr[i] = i;
        }

        this->swapIndex(1000);
    }

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
                T val = newest->getArr(j);
                newest->setArr(i, newest->getArr(j));
                newest->setArr(j, old_val);

                if (!this->checkExists(sols, newest))
                    sols->push_back(newest);

                T solsSize = sols->size();
            }
        }

        sols->erase(sols->begin());

        return sols;
    }

    /**
     * Neighbor of specific index position
     *
     * @param sol
     * @param i
     * @param j
     * @return
     */
    Solution<T>* getNeighbor(Solution<T>* sol, int i, int j) {

        Solution<T> *newest = (Solution<T>*)CombinatorySolution<T>::copy((CombinatorySolution<T>*)sol);
        T old_val = newest->getArr(i);
        T val = newest->getArr(j);
        newest->setArr(i, newest->getArr(j));
        newest->setArr(j, old_val);

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
    Solution<T>* crossover(Solution<T>* sol) {

        // Method which generates two solutions and selected one randomly

        // Random probability
        double p = ((double) rand() / (RAND_MAX)) + 1;

        /***************************************************************/
        /*  Partially Matched Crossover. Buckland (2002, pp. 130-132)  */
        /***************************************************************/

        // Setting child solutions
        CombinatorySolution<T>* fstChild = CombinatorySolution<T>::copy(this);
        CombinatorySolution<T>* sndChild = CombinatorySolution<T>::copy((CombinatorySolution<T> *) sol);

        // Finding crossing region (avoiding array out of bounds)
        int fstRegion = (rand() % (this->size-1)+1);
        int sndRegion = (rand() % (this->size-1)+1);

        // Getting region values
        std::pair<int, int> fstRegionVal (this->getArr(fstRegion-1), this->getArr(fstRegion));
        std::pair<int, int> sndRegionVal (sol->getArr(sndRegion-1), sol->getArr(sndRegion));

        // Grouping regions value
        auto regionsValue = vector<pair<int, int>>();
        regionsValue.push_back(fstRegionVal);
        regionsValue.push_back(sndRegionVal);

        // Grouping child solution
        auto children = vector<CombinatorySolution<T>*>();
        children.push_back(fstChild);
        children.push_back(sndChild);

        // Iterations : example -> fstRegionVal(1) value swap with fstRegionVal(2) value index for each child :
        for(auto region : regionsValue){

            for(auto child : children){

                // Retrieve index of region value
                int fstIndex = std::distance(child, std::find(child, child + this->size, region.first));
                int sndIndex = std::distance(child, std::find(child, child + this->size, region.second));

                // Swap values
                int tempVal = child->getArr(fstIndex);
                child->setArr(fstIndex, child->getArr(sndIndex));
                child->setArr(sndIndex, tempVal);
            }
        }

        // Return child solution generated randomly
        if(p > 0.5){

            delete sndChild;

            return fstChild;
        } else{

            delete fstChild;

            return sndChild;
        }
    }
};


#endif //METAHEURISTICS_COMBINATORYSOLUTION_H
