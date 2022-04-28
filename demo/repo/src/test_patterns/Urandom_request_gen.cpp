#include <assert.h>
#include <random>
#include <iostream>
#include <cstring>

#include "../../../../libs32/Logger/include/errors.h"

#include "../grammar_stuff.h"
#include "Urandom_generators.h"

#include "pattern_headers.h"

int Urandom_request_generator (ParamsRequestGenerator const * const& pParams, size_t sizeRequestArr, request_t *const& pRequestArr)
{
    assert( pParams && sizeRequestArr && pRequestArr);
    ParamsUrandomRequestGenerator const * const pParamsGenerator = static_cast<ParamsUrandomRequestGenerator const * const>(pParams);
    assert(CARDINALITY_OF_URANDOM_PARAMS_SET == pParamsGenerator->cardinality_of_params_set);
    double probabilitySaveTA =  pParamsGenerator->probability_save_ta;
    assert((probabilitySaveTA > 0.0f) && (probabilitySaveTA < 1.0f));

    size_t minNumberSaveTA = pParamsGenerator->min_number_save_ta;
    assert(minNumberSaveTA > 0);
    size_t maxNumberSaveTA = pParamsGenerator->max_number_save_ta;
    assert(minNumberSaveTA <= maxNumberSaveTA);
    std::uniform_int_distribution<size_t> rnd_num_saves(minNumberSaveTA, maxNumberSaveTA);

    size_t minNumberLoadTA = pParamsGenerator->min_number_load_ta;
    assert(minNumberLoadTA > 0);
    size_t maxNumberLoadTA = pParamsGenerator->max_number_load_ta;
    assert(minNumberLoadTA <= maxNumberLoadTA);
    std::uniform_int_distribution<size_t> rnd_num_loads(minNumberLoadTA, maxNumberLoadTA);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> saveTA_or_loadTA(0, 1);
    size_t cntTA = 0u;
    bool save;
    size_t numRequests;
    while(cntTA < sizeRequestArr){
        save = (probabilitySaveTA < saveTA_or_loadTA(mt));
        if(save){
            numRequests = rnd_num_saves(mt);
            numRequests = numRequests <= (sizeRequestArr - cntTA)
                          ? numRequests
                          : (sizeRequestArr - cntTA);
            for(size_t indexTA = 0; indexTA < numRequests; ++indexTA, ++cntTA){
                pRequestArr[cntTA] = SAVE_TA;
            }
        }
        else {
            numRequests = rnd_num_loads(mt);
            numRequests = numRequests <= (sizeRequestArr - cntTA)
                          ? numRequests
                          : (sizeRequestArr - cntTA);
            for(size_t indexTA = 0; indexTA < numRequests; ++indexTA, ++cntTA){
                pRequestArr[cntTA] = LOAD_TA;
            }
        }
    }

  return _RC_SUCCESS_;
}///end request_generator
