//
// Created by Jérôme BUISINE on 18/07/2017.
//

#ifndef METAHEURISTICS_UTILITIES_H
#define METAHEURISTICS_UTILITIES_H


#include "solutions/Solution.h"

class Utilities {

public:

    /**
    * Method used for check if solution already exists into a set of solution
    * @param sols : set of all solutions
    * @param s : solution to check
    * @return boolean : True if solution exists, otherwise False
    */
    static bool checkExists(vector<Solution> sols, Solution s);
};


#endif //METAHEURISTICS_UTILITIES_H
