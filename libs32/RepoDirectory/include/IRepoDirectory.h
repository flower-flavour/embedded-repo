#ifndef _IREPODIRECTORY_H_
#define _IREPODIRECTORY_H_

#include <cstddef>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "RepoDirectory_Export.h"

typedef struct tag_ParseTree ParseTree;
typedef struct tag_Array_str Array_str;
typedef struct tag_logger_closure logger_closure;
typedef struct tag_data_sizes data_sizes;

class Logger;
class DataSet;
class DataSet_v2;
class IKey;
class ISurrogateKey;
class IPlanTransactions;

class RepoDirectory_EXPORT IRepoDirectory
{
public:

    static IRepoDirectory * createRepoDirectory (Logger * pLogger = nullptr);

    virtual ~IRepoDirectory () {};


    virtual int getIndexesByFilters (IKey const * const & pKey,
                                     ParseTree const * const & ptr_parse_tree,
                                     size_t & dimension,
                                     data_sizes & sizes,
                                     size_t * & pTrackIndexes,
                                     Array_str ** & ppArray_with_newMetaData,
                                     logger_closure * ptr_lc) const = 0;

    virtual int notifyOnTransactionPlan (size_t curRepoSize,
                                         IKey const * const & pKey,
                                         size_t dimension,
                                         data_sizes const & sizes,
                                         size_t const * const & pTrackIndexes,
                                         IPlanTransactions * const & pPlanTransactions) = 0;

    virtual int commitTransaction (IKey const *& pKey,
                                   IPlanTransactions const * const & pPlanTransactions,
                                   DataSet_v2 const * const & ptrDS = nullptr) = 0;

    virtual int rollBackTransaction (IKey const *& pKey,
                                     IPlanTransactions const * const & pPlanTransactions,
                                     DataSet_v2 const * const & ptrDS = nullptr) = 0;

    virtual int getKeyCopyByPK(size_t PK, IKey const *& pKeyCopy) const = 0;

    virtual int getIndexesDScached(size_t & sizeIndexes, size_t *& pIndexes) const = 0;

protected:

    IRepoDirectory(){};

private:

    IRepoDirectory(IRepoDirectory const & other) = delete;
    void operator=(IRepoDirectory const &) = delete;

};

#endif // _IREPODIRECTORY_H_
