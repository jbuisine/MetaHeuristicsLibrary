//
// Created by Jérôme BUISINE on 28/10/2017.
//

#ifndef METAHEURISTICS_EASELECTOR_HPP
#define METAHEURISTICS_EASELECTOR_HPP

#include <vector>

template <typename C>
class Selectors {

public:

    /**
     * Simple selector used for generate children population from mu population
     *
     * Selector is based on score, only best solution remains (high pressure selection)
     *
     * @param scores : list which is the population
     * @param nb : number of children expected
     * @return indexes selected from mu population
     */
    static std::vector<int> simpleSelector(std::vector<double>* scores, int nb){

        // By default getting lambda best parents solutions indexes
        auto indexes = std::vector<int>(scores->size());

        for( int j = 0; j < indexes.size(); j++){
            indexes.at(j) = j;
        }

        // Default ordering indexes by value
        std::partial_sort(indexes.begin(), indexes.begin()+nb, indexes.end(), Utils::Comp(scores));

        return std::vector<int>(indexes.begin(), indexes.begin()+nb);
    }
};


#endif //METAHEURISTICS_EASELECTOR_HPP
