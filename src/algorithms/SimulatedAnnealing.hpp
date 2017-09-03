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
     * @param alpha : constant defined to decrease temperature (typical choices are between 0.8 & 0.99) 
     * @return
     */
    C* SimulatedAnnealingSimple(int nbEvaluation, int temperature, int alpha){

        // Best solution to return
        C *best = new C(this->size);

        // TODO Implement simulated annealing algorithm

        // Initialize T, T_min and alpha a constant used to decrease temperature

        // 1. Generate random solution
        // 2. Calculate cost solution defined
        // 3. Getting randomly a neighboring solution
        // 4. Calculate new solution's cost
        // 5. Compare the two solutions
        // 6. Repeat step 3 to 5 above until verified stop criterion

        return best;
    }
};