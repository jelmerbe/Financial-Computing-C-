#include "Utils/UtilityFunctions.hpp"
#include <random>
#include <functional>
#include <algorithm>
typedef std::mt19937 base_generator_type;//!< generator engine
typedef std::mt19937::result_type result_type;
typedef std::normal_distribution<> normal_distribution;

namespace utils {
    template<class bvector>
    class normal_random_generator {
    public:


        /** Constructor
        * @param seed1 initial seed
        */
        normal_random_generator(result_type seed1 = 123795) :
                Generator(seed1),
                Normal_dist(0, 1),
                Normal_gen(std::bind(Normal_dist, std::ref(Generator))) {}

        /** Standard normal generator
        * @param bvArg bvector passed by reference, standard normals to be written into
        */
        void operator()(bvector &bvArg) {
            std::generate(bvArg.begin(), bvArg.end(), Normal_gen);
        }

        /** Standard normal generator - takes no argument
        * @return a single value
        */
        double operator()() {
            return Normal_gen();
        }

        /** Standard normal generator, standard normals to be written in a range
        * @param LeftIter begining of the range
        * @param RightIter end of range
        */
        void operator()(typename bvector::iterator LeftIter, typename bvector::iterator RightIter) {
            std::generate(LeftIter, RightIter, Normal_gen);
        }

        void reset(result_type seed1 = 123795) {
            Generator = base_generator_type(seed1);
        }

    private:
        base_generator_type Generator; //!< random generator engine
        normal_distribution Normal_dist;//!< determines distribution
        std::function<double()> Normal_gen;
    };

    typedef std::vector<double> dvector;
    static normal_random_generator<dvector> stGen = normal_random_generator<dvector>();

    void ResetGenerator() {
        stGen.reset();
    }

    void NormalDist(std::vector<double> &vArg) {
        stGen(vArg);
    }

    double NormalDist() {
        return stGen();
    }
}