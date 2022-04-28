#ifndef _IREPOCACHELOGIC_H_
#define _IREPOCACHELOGIC_H_

#include <cstddef>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "../../repo/include/DataModel_caching_grammar.h"

#include "RepoCacheLogic_Export.h"

class Logger;
class DataSet;
class DataSet_v2;
class IKey;
class IPlanTransactions;
class IHints;

typedef struct tag_data_sizes data_sizes;

class RepoCacheLogic_EXPORT IRepoCacheLogic
{
public:

    static IRepoCacheLogic * createRepoCacheLogic (DataModel_caching_grammar::IndexesCacheLogicType cl_t,
                                                   size_t cacheCapacityBytes,
                                                   Logger * pLogger = nullptr);

    static IRepoCacheLogic * createRepoMultiSegmentedCacheLogic (DataModel_caching_grammar::IndexesCacheLogicType clt,
                                                                 size_t numSegments,
                                                                 size_t const * const & segmentCapacitiesInBytes,
                                                                 Logger * pLogger = nullptr);

    virtual ~IRepoCacheLogic () {};

    virtual int makeTransactionPlan (IKey const * const & pKey,
                                     size_t dimension,
                                     data_sizes const & sizes,
                                     size_t const * const & pTrackIndexes,
                                     IPlanTransactions *& pPlanTransactions,
                                     IHints const * pHints = nullptr) = 0;


    virtual int commitTransaction (IKey const * const & pKey,
                                   IPlanTransactions * & pPlanTransactions,
                                   bool ultimateCommitAccordingPlan) = 0;

    virtual int rollBackTransaction (IKey const * const & pKey,
                                     IPlanTransactions * & pPlanTransactions) = 0;


protected:

    IRepoCacheLogic(){};

private:

    IRepoCacheLogic(IRepoCacheLogic const & other) = delete;
    void operator=(IRepoCacheLogic const &) = delete;

};

#endif // _IREPOCACHELOGIC_H_
