#include <random>
#include <cstring>
#include "./test_patterns/Urandom_generators.h"

static std::random_device rd;
static std::mt19937 mt(rd());

void getRndValues(size_t _sample_size, double *const& p_sample) {
    std::uniform_real_distribution<> dis(0, 1);
    for(size_t i = 0; i < _sample_size; ++i){
        p_sample[i] = dis(mt);
    }
}
