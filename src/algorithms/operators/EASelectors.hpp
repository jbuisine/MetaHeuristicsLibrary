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
     * @param mu
     * @return New children population generated
     */
    static std::vector<C*> simpleSelector(std::vector<C*> mu, int lambda){

        auto children = std::vector<C*>(lambda);



        return children;
    }
};


#endif //METAHEURISTICS_EASELECTOR_HPP
