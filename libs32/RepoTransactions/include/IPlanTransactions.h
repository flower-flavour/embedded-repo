#ifndef _IPLANTRANSACTIONS_H_
#define _IPLANTRANSACTIONS_H_

#include <cstddef>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "PlanTransactions_Export.h"

#include "IAtomicTransaction.h"

class Logger;
class DataSet;
class IKey;

using SurrogateKey = IKey;

class PlanTransactions_EXPORT IPlanTransactions
{
public:

    static IPlanTransactions * createPlanTransactions (size_t numberAtomicTransactions, enum IAtomicTransaction::ATOMIC_TRANSACTION_TYPES const * const & p_att, PK_t const * const & pPK, Logger * pLogger = nullptr);

    static IPlanTransactions * createPlanTransactions (size_t numberAtomicTransactions, enum IAtomicTransaction::ATOMIC_TRANSACTION_TYPES const * const & p_att, SurrogateKey const ** const & pSK, Logger * pLogger = nullptr);

    virtual ~IPlanTransactions () {};

    virtual size_t size() const = 0;

    virtual enum IAtomicTransaction::ATOMIC_TRANSACTION_TYPES getAtomicTransactionType (size_t index) const = 0;

    virtual int copySK (size_t index, SurrogateKey *& pSK) const = 0;

    virtual size_t keyPK(size_t index) const = 0;

    virtual enum IAtomicTransaction::ATOMIC_TRANSACTION_STATES getAtomicTransactionState (size_t index) const = 0;

    virtual int validateState (size_t index, enum IAtomicTransaction::ATOMIC_TRANSACTION_STATES ats) const = 0;

    virtual int reset (size_t index) = 0;

    virtual int setDS (size_t index, IAtomicTransaction::sptr_constDS_t & sptr_DS) = 0;

    virtual int getDS (size_t index, IAtomicTransaction::sptr_constDS_t & sptr_DS) const = 0;

    virtual int getExecutionDuration(size_t index, float& executionDurationMicroseconds) const = 0;

protected:

    IPlanTransactions(){};

private:

    IPlanTransactions(IPlanTransactions const & other) = delete;
    void operator=(IPlanTransactions const &) = delete;

};

#endif // _IPLANTRANSACTIONS_H_
