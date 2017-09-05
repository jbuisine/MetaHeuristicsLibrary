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

    /**
     * Method used for accept or not a new solution after comparison
     * @param o : current best solution
     * @param n : new solution to compare
     * @param temperature : current temperature
     * @return the acceptance probability
     */
    double acceptanceProbability(C *o, C *n, double temperature){

        if(this->checkSolution(o, n)){
            return 1.0;
        }

        double ap = 0.0;

        // Getting sum of acceptance probability for each criterion
        for(int i = 0; i < this->funcs.size(); i++){
            if(this->problem_type)
                ap += exp((this->funcs[i]((long)n) - this->funcs[i]((long)o))/temperature);
            else
                ap += exp(-(this->funcs[i]((long)n) - this->funcs[i]((long)o))/temperature);
        }

        return ap / this->funcs.size();
    }

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
     * @param nbEvaluation : number of iteration before changing temperature
     * @param temperature : starting temperature to decrease
     * @param minTemperature : stopping criterion
     * @param alpha : constant defined to decrease temperature (typical choices are between 0.8 & 0.99) 
     * @return
     */
    C* SimulatedAnnealingSimple(int nbEvaluation, double temperature, double minTemperature, double alpha){

        // Best solution to return
        auto *best = new C(this->size);

        while(temperature > minTemperature){
            int i = 0;

            while(i <= nbEvaluation){

                C *neighbor = C::copy(best);
                neighbor->swapIndex(1);

                double ap = acceptanceProbability(best, neighbor, temperature);

                // TODO move this util function into another util class (template is not necessary)
                double r = Utilities<C>::randInterval(0, 1);

                if(ap > r){
                    delete best;
                    best = C::copy(neighbor);
                }

                delete neighbor;

                i+=1;
            }
            temperature = temperature * alpha;
        }

        return best;
    }
};