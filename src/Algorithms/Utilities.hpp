//
// Created by Jérôme BUISINE on 18/07/2017.
//


#include <stdio.h>

#include <vector>
#include <iostream>
#include "../solutions/Solution.hpp"

using namespace std;

/**
* Method used for check if solution already exists into a set of solution
* @param sols : set of all solutions
* @param s : solution to check
* @return boolean : True if solution exists, otherwise False
*/
template<typename T>
class Utilities{

public:

    /**
     * Utility method
     * @param sols
     * @param s
     * @return
     */
    static bool checkExists(vector<T*>* sols, T* s) {

        for (int i = 0; i < sols->size(); ++i) {

            if(sameSolution(sols->at(i), s)){
                return true;
            }
        }

        return false;
    }

private:

    /**
      * @param a : first solution to compare
      * @param b : second solution to compare
      * @return true if same
      */
    static bool sameSolution(T* a, T* b){
        for (int i = 0; i < a->getSize(); ++i) {
            if (a->getArr()[i] != b->getArr()[i]){
                return false;
            }
        }
        return true;
    }
};