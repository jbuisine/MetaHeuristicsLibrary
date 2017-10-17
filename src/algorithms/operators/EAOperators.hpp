//
// Created by jbuisine on 14/10/17.
//

#ifndef METAHEURISTICS_EAOPERATORS_HPP
#define METAHEURISTICS_EAOPERATORS_HPP


#include <map>

template <typename C>
class EAOperators {

    /**
     * Operator which specifies swapping two indexes of QAP solution
     *
     * Note that swapIndex function which depends to Solution kind (Binary or Integer array)
     *
     * @param fstSol
     * @return New solution generated
     */
    static C* simpleMutation(C* fstSol){
        return C::copy(fstSol->swapIndex(1));
    }

    /**
     * Operator which generates new solution based on two parents solutions properties
     *
     * @param fstSol
     * @param sndSol
     * @return new child solution
     */
    static C* simpleCrossover(C* fstSol, C* sndSol){

        unsigned int solSize = fstSol->getSize();

        // Binary solution case
        if(dynamic_cast<BinaryCombinatorySolution*>(fstSol) == nullptr){

            // Getting information
            unsigned int splitIndex = (rand() % solSize);

            C* sol = new C(solSize);

            // Setting new binary solution
            for(int i(0); i < solSize; i++){
                if(i > splitIndex){
                    sol->setArr(i, fstSol->getArr(i));
                }else{
                    sol->setArr(i, sndSol->getArr(i));
                }
            }

            return sol;

        }else if(dynamic_cast<CombinatorySolution*>(fstSol) == nullptr){

            // Method which generates two solutions and selected randomly one

            // Random probability
            double p = ((double) rand() / (RAND_MAX)) + 1;


            /***************************************************************/
            /*  Partially Matched Crossover. Buckland (2002, pp. 130-132)  */
            /***************************************************************/

            // Setting child solutions
            C* fstChild = C::copy(fstSol);
            C* sndChild = C::copy(sndSol);

            // Finding crossing region (avoiding array out of bounds)
            int fstRegion = (rand() % (solSize-1)+1);
            int sndRegion = (rand() % (solSize-1)+1);

            // Getting region values
            std::pair<int, int> fstRegionVal (fstSol->getArr(fstRegion-1), fstSol->getArr(fstRegion));
            std::pair<int, int> sndRegionVal (sndSol->getArr(sndRegion-1), sndSol->getArr(sndRegion));

            // Grouping regions value
            auto regionsValue = vector<pair<int, int>>();
            regionsValue.push_back(fstRegionVal);
            regionsValue.push_back(sndRegionVal);

            // Grouping child solution
            auto children = vector<C*>();
            children.push_back(fstChild);
            children.push_back(sndChild);

            // Iterations : example -> fstRegionVal(1) value swap with fstRegionVal(2) value index for each child :
            for(auto region : regionsValue){

                for(auto child : children){

                    // Retrieve index of region value
                    int fstIndex = std::distance(child, std::find(child, child + solSize, region.first));
                    int sndIndex = std::distance(child, std::find(child, child + solSize, region.second));

                    // Swap values
                    int tempVal = child->getArr(fstIndex);
                    child->getArr(fstIndex) = child->getArr(sndIndex);
                    child->getArr(sndIndex) = tempVal;
                }
            }

            // Return randomly child solution generated
            if(p > 0.5){
                return fstChild;
            } else{
                return sndChild;
            }

        }else{
            return C::copy(fstSol);
        }
    }
};


#endif //METAHEURISTICS_EAOPERATORS_HPP
