//
// Created by jbuisine on 14/10/17.
//

#ifndef METAHEURISTICS_EAOPERATORS_HPP
#define METAHEURISTICS_EAOPERATORS_HPP


template <typename C>
class EAOperators {

    /**
     * Operator which specifies swapping 1 time combinatory solution
     * @param fstSol
     * @return
     */
    static C* swapIndex(C* fstSol){
        return C::copy(fstSol->swapIndex(1));
    }
};


#endif //METAHEURISTICS_EAOPERATORS_HPP
