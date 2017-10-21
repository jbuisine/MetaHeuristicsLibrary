//
// Created by jbuisine on 14/10/17.
//

#ifndef METAHEURISTICS_EAOPERATORS_HPP
#define METAHEURISTICS_EAOPERATORS_HPP

template <typename C>
class EAOperators {

public:
    /**
     * Operator which specifies swapping two indexes of QAP solution
     *
     * Note that swapIndex function which depends to Solution kind (Binary or Integer array)
     *
     * @param fstSol
     * @return New solution generated
     */
    static C* simpleMutation(C* fstSol, C* sndSol = nullptr){
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

        // Utilisation of crossover defined for each class type
        return fstSol->crossover(sndSol);
    }
};


#endif //METAHEURISTICS_EAOPERATORS_HPP
