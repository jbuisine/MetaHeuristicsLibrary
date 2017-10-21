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
        Comp( const vector<int>& v ) : _v(v) {}
        bool operator ()(int a, int b) { return _v[a] > _v[b]; }
        const vector<int>& _v;
    };
};