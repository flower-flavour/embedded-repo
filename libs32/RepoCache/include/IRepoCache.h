#ifndef _IREPOCACHE_H_
#define _IREPOCACHE_H_

#include <cstddef>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "RepoCache_Export.h"


class Logger;
class DataSet;
class DataSet_v2;
class DataSet_v2_sc;
class IPlanTransactions;

typedef struct tag_data_sizes data_sizes;

class RepoCache_EXPORT IRepoCache
{
public:

    using storage_value_t = boost::shared_ptr<DataSet_v2>;
    using storage_shallow_copy_t = boost::shared_ptr<DataSet_v2_sc>;
    using storage_const_value_t = boost::shared_ptr<DataSet_v2 const>;
    using storage_const_shallow_copy_t = boost::shared_ptr<DataSet_v2_sc const>;

    static IRepoCache * createRepoCache (size_t cacheCapacityBytes, size_t CacheSize, Logger * pLogger = nullptr);

    virtual ~IRepoCache () {};

    virtual int runTransaction (IPlanTransactions * const & pPlanTransactions) = 0;

    virtual int commitTransaction (IPlanTransactions * const & pPlanTransactions,
                                   IKey const * const & pKey = nullptr,
                                   DataSet_v2 const * const & ptrDS = nullptr) = 0;

    virtual int rollBackTransaction (IPlanTransactions * const & pPlanTransactions,
                                     IKey const * const & pKey = nullptr,
                                     DataSet_v2 const * const & ptrDS = nullptr) = 0;

    virtual int retrieveDS_sc (IKey const * const & pKey,
                               IRepoCache::storage_shallow_copy_t & shr_ptrDS_sc) = 0;

    virtual int retrieveDS_sc (IKey const * const & pKey,
                               size_t dimension,
                               size_t const * const & pTrackIndexes,
                               IRepoCache::storage_shallow_copy_t & shr_ptrDS) = 0;

protected:

    IRepoCache(){};

private:

    IRepoCache(IRepoCache const & other) = delete;
    void operator=(IRepoCache const &) = delete;

};

#endif // _IREPOCACHE_H_
