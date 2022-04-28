#include <iostream>
#include <random>

#include "../../../libs32/Logger/include/errors.h"
#include "../../../libs32/Logger/include/Logger.h"

#include "../../../libs32/DataSet/include/data_sizes.h"
#include "../../../libs32/DataSet/include/DataSet.h"

#include "../../../libs32/Key/include/IKey.h"

#include "grammar_stuff.h"

#include "test_patterns/pattern_headers.h"

#include "parseCLIargs.h"
#include "DataproviderImpl.h"

#include "allocateRepository.h"

int main(int argc, char *argv[])
{
    bool existsCfg = false;
    size_t max_number_saveDS_transactions = MAX_SAVE_DS_TRANSACTIONS;
    size_t max_track_size                 = MAX_TRACK_SIZE;

    /** 1. Parse CLI args */
    if (parseCLIargs (argc, argv, existsCfg, max_number_saveDS_transactions, max_track_size) == 0) {
        return 1;
    }

    /** 2. Init params for test pattern */
    size_t minNumberSaveTA = 1;
    size_t maxNumberSaveTA = 10;

    size_t minNumberLoadTA  = 1;
    size_t maxNumberLoadTA  = 10;

    size_t minNumberDSTracks = DIMENSION;
    size_t maxNumberDSTracks = DIMENSION;
    size_t minSizeDSTrack    = 1;
    size_t maxSizeDSTrack    = max_track_size;

    char const * pRepoCfgFilename = argv[2];

    /** 3. Create Logger instance */
    Logger * pLogger = Logger::createLogger();

    RepoManager * pRepository = nullptr;

    /** 4. Create Repository instance embedded into this process */
    int rc = allocateRepository (pRepoCfgFilename, pRepository, pLogger);
    assert(_RC_SUCCESS_ == rc);

    size_t sizeRequestArr = 0;

    /** This demo keeps implementation of URANDOM test pattern ONLY!
       Almost all parameters of save/load-transactions are generated
       as r.v. ~ U[measure_support]
    */
    enum TEST_PATTERN_IMPLS pattern = URANDOM_PATTERN;

    switch(pattern)
    {
    case URANDOM_PATTERN:
    {
        ParamsUrandomPattern paramsTestPattern;
        paramsTestPattern.cardinality_of_params_set = 9;
        paramsTestPattern.probability_save_ta = 0.5;
        paramsTestPattern.min_number_save_ta = minNumberSaveTA;
        paramsTestPattern.max_number_save_ta = maxNumberSaveTA;
        paramsTestPattern.min_number_load_ta = minNumberLoadTA;
        paramsTestPattern.max_number_load_ta = maxNumberLoadTA;
        paramsTestPattern.min_number_ds_tracks = minNumberDSTracks;
        paramsTestPattern.max_number_ds_tracks = maxNumberDSTracks;
        paramsTestPattern.min_size_ds_tracks = minSizeDSTrack;
        paramsTestPattern.max_size_ds_tracks = maxSizeDSTrack;

        sizeRequestArr = (size_t)(max_number_saveDS_transactions/paramsTestPattern.probability_save_ta);
        /** Client code must have IDataProvider implemetation to 
          work with embedded repository instance!

          5. Create IDataProvider implemetation which keeps URANDOM test pattern as well.
        */
        DataproviderImpl DPI(pRepository, nullptr);

        /** 6. Run URANDOM test pattern */
        rc = DPI.run(sizeRequestArr, &paramsTestPattern);

        break;
    }
    ///TODO!!! Feel free to implement test patterns on your own...
    default:
        assert(pattern < TOTAL_TEST_PATTERN_IMPLS);
    }///end switch

    std::cout << "accomplished at size Repository = " << pRepository->sizeRepository() << std::endl;

    /** 7. Delete Repository instance embedded into this process */
    delete pRepository;
    pRepository = nullptr;
    delete pLogger;
    pLogger = nullptr;
    std::cout << "DONE!" << std::endl;
    return 0;
}
