//
// Created by Jérôme BUISINE on 06/10/2017.
//

#ifndef METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H
#define METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H


#include "Heuristics.hpp"
#include "operators/EAOperators.hpp"

template<typename C>
class EvolutionaryAlgorithmSearch : public Heuristics<C> {


// Type Operator used for generate new solution
typedef C* (Operator)(C* fstSol, C* sndSol);


// Type Selector used for getting children list
typedef std::vector<int>* (Selector)(std::vector<double>* muScores, int lambda);

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
     * @return
     */
    C* runSimple(int mu, int lambda, int iteration, Selector selector, Operator crossover, Operator mutation, Local localSearch, int nbIterationLocal){


        /***********************************************/
        /*********** Context verifications  ************/
        /***********************************************/

        // Verifying mu and lambda parameters
        if(mu < lambda){
            std::cout << "Error : You can't use mu parameter smaller than lambda." << std::endl;
            return nullptr;
        }

        // Verifying  if context used one or multiple objective functions
        if(this->funcs.size() > 1){
            std::cout << "Error : You can't use this EA method with multiple objective context." << std::endl;
            return nullptr;
        }

        /***********************************************/
        /***********  Setting context objects  *********/
        /***********************************************/

        // Getting objective function
        Fitness func = this->funcs.at(0);

        // Vector of mu parent solutions and scores
        auto parents = new std::vector<C*>(mu);
        auto parentsScores = new std::vector<double>(mu);

        /**************************************************************/
        /****** 1. mu population initialization and evaluation ********/
        /**************************************************************/

        // Initialize each parent
        for(int i = 0; i < parents->size(); i++){

            // Parent 'i' random initialization
            parents->at(i) = new C(this->size);
            parents->at(i)->fillRandomSolution();

            // Getting solution score
            parentsScores->at(i) = func((long)parents->at(i));
        }

        for (int i(0); i < iteration; ++i) {

            /******************************************************************/
            /****** 1. lambda initialization using parental selection  ********/
            /******************************************************************/

            // Vector of children solutions
            auto children = new std::vector<C*>(lambda);
            auto childrenScores = new std::vector<double>(lambda);

            // By default getting lambda best parents solutions indexes
            auto muIndexes = selector(parentsScores, lambda);

            // Initialisation of child solutions
            for(int j(0); j < lambda; j++){

                children->at(j) = C::copy(parents->at(muIndexes->at(j)));
                childrenScores->at(j) = parentsScores->at(muIndexes->at(j));
            }

            /******************************************************************************************/
            /****** 2. Improvement part of children using crossover, mutation and LocalSearch  ********/
            /******************************************************************************************/

            // Perform improvement for each child (currently best parents)
            for(int j(0); j < children->size(); j++){

                // Getting index sol used for crossover
                int indexSol = (rand() % children->size());

                // Crossover between current child solution and another chosen randomly
                children->at(j) = crossover(children->at(j), children->at(indexSol));

                // Simple mutation of solution
                children->at(j) = mutation(children->at(j), nullptr);

                // Local search to improve solution
                children->at(j) = localSearch(nbIterationLocal, this, children->at(j));

                // Replace score of new child generated
                childrenScores->at(j) = func((long)children->at(j));
            }

            /**********************************************************************/
            /****** 3. Environmental selection to create new mu population ********/
            /**********************************************************************/

            // Vector of parents+children solutions for environmental selection
            auto population = new std::vector<C*>();
            auto populationScores = new std::vector<double>();

            // Merge parents and children into population
            population->insert(population->end(), parents->begin(), parents->end());
            population->insert(population->end(), children->begin(), children->end());

            // Merge parents and children scores into population scores
            populationScores->insert(populationScores->end(), parentsScores->begin(), parentsScores->end());
            populationScores->insert(populationScores->end(), childrenScores->begin(), childrenScores->end());

            // By default getting best mu solution indexes   of population
            auto populationIndexes = new std::vector<int>(populationScores->size());

            for( int j = 0; j < populationIndexes->size(); ++j ){
                populationIndexes->at(j) = j;
            }

            partial_sort(populationIndexes->begin(), populationIndexes->begin()+mu, populationIndexes->end(), Utils::Comp(populationScores));

            // Setting best population (mu+lambda) solutions to generate new parents (mu) population
            for(int j(0); j < mu; j++){

                parents->at(j) = population->at(populationIndexes->at(j));
                parentsScores->at(j) = populationScores->at(populationIndexes->at(j));
            }

            ///////////////////////////////
            // Clear iteration variables //
            ///////////////////////////////
            delete children, population;
            delete childrenScores, populationScores;

            // delete indexes..
            delete populationIndexes, muIndexes;

            std::cout << "EA Simple " << ((double)i*100.0)/iteration << "%" << std::endl;
        }

        std::cout << "EA Simple 100%" << std::endl;

        // Finally return best solution of parents population
        int bestIndex = (int) std::distance(parentsScores->begin(), std::max_element(parentsScores->begin(), parentsScores->end()));

        return parents->at(bestIndex);
    }
};


#endif //METAHEURISTICS_EVOLUTIONARYALGORITHMSEARCH_H
