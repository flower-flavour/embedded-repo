#include <random>
#include "./test_patterns/Urandom_generators.h"

static std::random_device rd;
static std::mt19937 mt(rd());

void getRndSizes(size_t max_sample_value, size_t _sample_size, size_t *const& p_sample) {
    std::uniform_int_distribution<size_t> dis(1, max_sample_value);
    for(size_t i = 0; i < _sample_size; ++i){
        p_sample[i] = dis(mt);
    }
}
