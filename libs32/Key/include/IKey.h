#ifndef _IKEY_H_
#define _IKEY_H_

#include <cstddef>
#include <string>

#include "Key_Export.h"

class Logger;

typedef struct tag_logger_closure logger_closure;

typedef int (*ptr_Key_parser) (char const * pKeyAsStr, size_t * pPK, size_t * pSizeArrayParentDS, size_t ** ppArrayParentPKs, logger_closure * ptr_lc);

class IKey
{
public:

    static IKey * createKey(size_t DS_index, size_t dimArrayParentDS, size_t const * const& pArrayParentDS_indexes, Logger * pLogger);

    static IKey * deserialize (char const * pKeyAsStr, ptr_Key_parser pKeyParser, logger_closure * ptr_lc);

    static bool verify(size_t PK, size_t sizeParentPKs, size_t const * const& ptrParentPKs, Logger * pLogger);

    virtual ~IKey(){};

    virtual IKey * clone() const = 0;

    virtual size_t getPK() const = 0;

    virtual size_t hash() const = 0;

    virtual size_t getSizeParentPKs() const = 0;


    virtual size_t const * getPtrConstParentPKs(size_t & sizeParentPKs) const = 0;

    virtual int getParentPKs(size_t & sizeParentPKs, size_t *& ptrParentPKs) const = 0;

    virtual size_t sizeAllocated() const = 0;

    virtual bool compare(IKey const * other) const = 0;

    virtual std::string toString() const = 0;

    virtual std::string PKtoString() const = 0;

    virtual int serialize(size_t& _size, uint8_t *& pKeySerialized) const = 0;

protected:

    IKey(size_t PK){};

private:

    IKey(IKey const & other) = delete;
    void operator=(IKey const &) = delete;

};

#endif // _IKEY_H_
