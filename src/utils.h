//
// Created by jbuisine on 09/08/17.
//

#ifndef METAHEURISTICS_CONFIGURATION_H
#define METAHEURISTICS_CONFIGURATION_H

// Number of element
const int N = 100;

// Number of iteration
const int I = 1000;

// Function of Fitness type
double compute (long ptrToParam) {

    CombinatorySolution<int>* s = (CombinatorySolution<int>*)ptrToParam;

    double c = 0.0;

    int t = s->getSize();
    for (int i = 0; i < t; ++i) {
        c += sqrt(s->getArr()[i])*sqrt(i);
    }

    return c;
}

#endif //METAHEURISTICS_CONFIGURATION_H
