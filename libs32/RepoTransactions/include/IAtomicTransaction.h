#ifndef _IATOMICTRANSACTION_H_
#define _IATOMICTRANSACTION_H_

#include <cstddef>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "AtomicTransaction_Export.h"

class Logger;
class DataSet;
class DataSet_v2;
class IKey;

using SurrogateKey = IKey;
using PK_t         = size_t;

class AtomicTransaction_EXPORT IAtomicTransaction
{
public:

    constexpr static const float kExecutionDurationUnavailable = -1;

    enum ATOMIC_TRANSACTION_TYPES{
        SAVE_RESOURCE_IN_CACHE           = 0,
        SAVE_RESOURCE_ON_DISK            = 1,
        MOVE_RESOURCE_FROM_DISK_TO_CACHE = 2,
        MOVE_RESOURCE_FROM_CACHE_TO_DISK = 3,
        RETRIEVE_RESOURCE_FROM_DISK      = 4,
        COPY_RESOURCE_FROM_CACHE_TO_DISK = 5,
        TOTAL_ATOMIC_TRANSACTION_TYPES
    };

    enum ATOMIC_TRANSACTION_STATES{
        JUST_CREATED                             = 0,
        VALIDATED                                = 1,
        RESOURCE_CONSUMED_FROM_PROVIDER          = 2,
        RESOURCE_PROVIDED_TO_CONSUMER            = 3,
        TRANSACTION_COMMITED_AND_RESOURCE_FREED  = 4,
        TOTAL_ATOMIC_TRANSACTION_STATES
    };

    struct NullDeleter {template<typename T> void operator()(T*) {} };

    using shr_ptrUniqueIndexes_DS_tracks_t = boost::shared_ptr<size_t[]>;
    using sptr_DS_t = boost::shared_ptr<DataSet_v2>;
    using sptr_constDS_t = boost::shared_ptr<const DataSet_v2>;
    using shr_ptrArray_Shr_ptr_constDS_t = boost::shared_ptr< boost::shared_ptr<const DataSet_v2> [] >;

    static IAtomicTransaction * createAtomicTransaction (enum ATOMIC_TRANSACTION_TYPES att, PK_t const & PK, Logger * pLogger = nullptr);

    static IAtomicTransaction * createAtomicTransaction (enum ATOMIC_TRANSACTION_TYPES att, SurrogateKey const *& pSK, Logger * pLogger = nullptr);

    virtual ~IAtomicTransaction () {};

    virtual enum ATOMIC_TRANSACTION_TYPES getAtomicTransactionType () const = 0;

    virtual int copySK (SurrogateKey *& pSK) const = 0;

    virtual size_t keyPK() const = 0;

    virtual enum ATOMIC_TRANSACTION_STATES getAtomicTransactionState () const = 0;

    virtual int validateState (enum ATOMIC_TRANSACTION_STATES ats) = 0;

    virtual int reset () = 0;

    virtual int setDS (sptr_constDS_t & sptr_DS) = 0;

    virtual int getDS (sptr_constDS_t & sptr_DS) const = 0;

    virtual float getExecutionDuration() const = 0;

protected:

    IAtomicTransaction(){};

private:

    IAtomicTransaction(IAtomicTransaction const & other) = delete;
    void operator=(IAtomicTransaction const &) = delete;

};

#endif // _IATOMICTRANSACTION_H_
