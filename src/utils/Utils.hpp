//
// Created by Jérôme BUISINE on 18/07/2017.
//


#include <cstdio>
#include <vector>
#include <iostream>
#include "../solutions/Solution.hpp"

using namespace std;

/**
 * Utils method without links' template
 */
class Utils{

public:

    /**
     * Method which returns a random double of an interval
     *
     * @param i0 : first part of interval
     * @param i1 : second part of interval
     * @return
     */
    static double randInterval(double i0, double i1){
        return i0 + (i1 - i0) * rand() / ((double) RAND_MAX);
    }

    struct Comp{
        Comp(vector<double>* v ) : _v(v) {}
        bool operator ()(double a, double b) { return _v->at(a) > _v->at(b); }
        vector<double>* _v;
    };
};