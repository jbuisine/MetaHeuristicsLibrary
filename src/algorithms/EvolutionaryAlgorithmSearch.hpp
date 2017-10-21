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

    /**
     * Simple Evolutionary algorithm implementation
     *
     * @param mu : Number of parents solutions
     * @param lambda : Number of children solutions
     * @param iteration : Number of iterations
     * @param localSearch : Local search expected (Local type)
     * @param nbIterationLocal : Iteration for Local search
     * @param anOperator : Operator used like mutation crossover
     * @return
     */
    C* runSimple(int mu, int lambda, int iteration, Local localSearch, int nbIterationLocal, Operator anOperator){


        /***********************************************/
        /*********** Context verifications  ************/
        /***********************************************/

        // Verifying mu and lambda parameters
        if(mu < lambda){
            std::cout << "Error : You can't use mu parameter smaller than lambda." << std::endl;
            return nullptr;
        }

        // Verifying  if context used one or multiple objective functions
        if(funcs.size() > 1){
            std::cout << "Error : You can't use this EA method with multiple objective context." << std::endl;
            return nullptr;
        }

        /***********************************************/
        /***********  Setting context objects  *********/
        /***********************************************/

        // Getting objective function
        Fitness* func = funcs.at(0);

        // Vector of mu parent solutions and scores
        auto parents = new std::vector<C*>(mu);
        auto parentsScores = new std::vector<double>(mu);

        // Vector of children solutions
        auto children = new std::vector<C*>(lambda);
        auto childrenScores = new std::vector<C*>(lambda);

        /**************************************************************/
        /****** 1. mu population initialization and evaluation ********/
        /**************************************************************/

        // Initialize each parent
        for(int i = 0; i < parents->size(); i++){

            // Parent 'i' random initialization
            parents->at(i) = new C(this->size);
            parents->at(i)->fillWithRandomCombatorySolution();

            // Getting solution score
            parentsScores->at(i) = func(parents->at(i));
        }

        /******************************************************************/
        /****** 1. lambda initialization using parental selection  ********/
        /******************************************************************/

        // By default getting best parents solutions indexes
        vector<int> muIndexes;
        muIndexes.resize(parentsScores.size());
        for( int i= 0; i < muIndexes.size(); ++i ){
            muIndexes[i]= i;
        }

        partial_sort( muIndexes.begin(), muIndexes.begin()+lambda, muIndexes.end(), Utils::Comp(v) );

        // Initialisation of child solutions
        for(int i(0); i < lambda; i++){

            children->at(i) = new C::copy(parents->at(muIndexes.at(i)));
            childrenScores->at(i) = parentsScores->at(muIndexes.at(i));
        }


        /******************************************************************************************/
        /****** 2. Improvement part of children using crossover, mutation and LocalSearch  ********/
        /******************************************************************************************/

    }
};


#endif //METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H
