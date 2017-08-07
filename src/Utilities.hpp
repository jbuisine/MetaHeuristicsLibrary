//
// Created by Jérôme BUISINE on 18/07/2017.
//


#include <stdio.h>

#include <vector>
#include <iostream>

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

    static bool checkExists(vector<T*> sols, T s) {
        bool check = false;

        for (int i = 0; i < sols.size(); ++i) {
            if(sols[i]->getArr() == s.getArr()){
                check = true;
                break;
            }
        }

        return check;
    }
};