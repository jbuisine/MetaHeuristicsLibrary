//
// Created by Jérôme BUISINE on 18/07/2017.
//

#include "Utilities.h"

/**
* Method used for check if solution already exists into a set of solution
* @param sols : set of all solutions
* @param s : solution to check
* @return boolean : True if solution exists, otherwise False
*/
template<std::size_t N> bool Utilities<N>::checkExists(vector<Solution<N>> sols, Solution<N> s) {
    bool check = false;

    for (int i = 0; i < sols.size(); ++i) {
        if(sols[i].getArr() == s.getArr()){
            check = true;
            break;
        }
    }

    return check;
}