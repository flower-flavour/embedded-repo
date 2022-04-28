#ifndef _IREPOPERSISTENTSTORAGE_H_
#define _IREPOPERSISTENTSTORAGE_H_

#include <cstddef>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "RepoPersistentStorage_Export.h"

#include "../../RPSReader/include/IStorageReader.h"

class Logger;
class DataSet;
class DataSet_v2;
class IKey;
class IPlanTransactions;

typedef struct tag_data_sizes data_sizes;

class RepoPersistentStorage_EXPORT IRepoPersistentStorage
{
public:

    using storage_value_t = boost::shared_ptr<DataSet_v2>;
    using storage_shallow_copy_t = boost::shared_ptr<DataSet_v2_sc>;

    static IRepoPersistentStorage * createRepoPersistentStorage (char const * p_file_name = nullptr,  size_t curSize = 0, Logger * pLogger = nullptr);

    virtual ~IRepoPersistentStorage () {};

    virtual int runTransaction (IPlanTransactions * const & pPlanTransactions) = 0;

    virtual int commitTransaction (IPlanTransactions * const & pPlanTransactions,
                                   IKey const * const & pKey = nullptr,
                                   DataSet_v2 const * const & ptrDS = nullptr) = 0;

    virtual int rollBackTransaction (IPlanTransactions * const & pPlanTransactions,
                                   IKey const * const & pKey = nullptr,
                                   DataSet_v2 const * const & ptrDS = nullptr) = 0;

    virtual int retrieveDS_sc (IKey const * const & pKey,
                               IRepoPersistentStorage::storage_shallow_copy_t & shr_ptrDS_sc) = 0;

    virtual int retrieveDS_sc (IKey const * const & pKey,
                               size_t dimension,
                               size_t const * const & pTrackIndexes,
                               IRepoPersistentStorage::storage_shallow_copy_t & shr_ptrDS) = 0;

    static int processStorageFile(enum IStorageReader::STORAGE_FILE_PROCESSING_ACTION pa, size_t indexDS, size_t & sizeDS, IRepoPersistentStorage::storage_value_t & shr_ptr_DS, char const * p_file_name = nullptr, Logger * pLogger = nullptr);

protected:

    IRepoPersistentStorage(){};

private:

    IRepoPersistentStorage(IRepoPersistentStorage const & other) = delete;
    void operator=(IRepoPersistentStorage const &) = delete;

};

#endif // _IREPOPERSISTENTSTORAGE_H_
