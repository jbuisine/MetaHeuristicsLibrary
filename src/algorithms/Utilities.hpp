//
// Created by Jérôme BUISINE on 18/07/2017.
//


#include <cstdio>

#include <vector>
#include <iostream>
#include "../solutions/Solution.hpp"

using namespace std;

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

    /**
      * Method which compares if solutions are sames
      *
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