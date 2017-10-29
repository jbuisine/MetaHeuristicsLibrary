//
// Created by Jérôme BUISINE on 28/10/2017.
//

#ifndef METAHEURISTICS_EASELECTOR_HPP
#define METAHEURISTICS_EASELECTOR_HPP

#include <vector>

template <typename C>
class EASelectors {

public:

    /**
     * Simple selector used for generate children population from mu population
     *
     * Selector is based on score, only best solution remains (high pressure selection)
     *
     * @param muScore : list which is the population
     * @param lambda : number of children expected
     * @return indexes selected from mu population
     */
    static std::vector<int>* simpleSelector(std::vector<double>* muScores, int lambda){

        // By default getting lambda best parents solutions indexes
        auto muIndexes = new std::vector<int>(muScores->size());

        for( int j = 0; j < muIndexes->size(); j++){
            muIndexes->at(j) = j;
        }

        // Ordering children indexes by value
        std::partial_sort(muIndexes->begin(), muIndexes->begin()+lambda, muIndexes->end(), Utils::Comp(muScores));

        return muIndexes;
    }
};


#endif //METAHEURISTICS_EASELECTOR_HPP
