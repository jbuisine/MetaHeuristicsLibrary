//
// Created by Jérôme BUISINE on 06/10/2017.
//

#ifndef METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H
#define METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H


#include "Heuristics.hpp"

template<typename C>
class EvolutionaryAlgorithmSearch : public Heuristics<C> {


// Type Operator used for generate new solution
typedef C* (Operator)(C* fstSol, C* sndSol);

// Type Local search function type
typedef C* (Local)(int nbEvaluation, Heuristics<C> *heuristics, C* s);

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    EvolutionaryAlgorithmSearch(bool problem_type, vector<Fitness>& funcs, int size) : Heuristics<C>(problem_type, funcs, size){}

    C* runSimple(int mu, int lambda, int iteration, Local localSearch, int nbIterationLocal, Operator anOperator){

    }
};


#endif //METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H
