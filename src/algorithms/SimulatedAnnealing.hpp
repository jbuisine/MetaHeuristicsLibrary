//
// Created by Jérôme BUISINE on 10/07/2017.
//

#include "../solutions/CombinatorySolution.hpp"
#include "../solutions/BinaryCombinatorySolution.hpp"
#include "Heuristics.hpp"
#include <algorithm>

template<typename C>
class SimulatedAnnealing : public Heuristics<C> {

private:

public:

    /**
     * Initialization of context
     * @param problem_type : 'false' specify minimizing problem and 'true' maximizing
     * @param f : objective function(s)
     * @param s_size : size of problem solution
     */
    SimulatedAnnealing(bool problem_type, vector<Fitness>& funcs, int size) : Heuristics<C>(problem_type, funcs, size){}

    /**
     * Simulated annealing simple implementation
     * @param nbEvaluation : number of iteration
     * @param temperature : starting temperature to decrease
     * @param stepSize : step defined to decrease temperature
     * @param nbPerturbation : number of elements permuted into a solution at each movement
     * @return
     */
    C* SimulatedAnnealingSimple(int nbEvaluation, int temperature, int stepSize, int nbPerturbation){

        // Best solution to return
        C *best = new C(this->size);

        // TODO Implement simulated annealing algorithm

        return best;
    }
};