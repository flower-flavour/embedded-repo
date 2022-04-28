#ifndef _ISTORAGEIMPL_H_
#define _ISTORAGEIMPL_H_

#include <cstddef>

#include "RepoPersistentStorage_Export.h"

class RepoPersistentStorage_EXPORT IStorageImpl
{
public:

    static IStorageImpl * createStorageImpl (char const * p_file_name,  size_t curSize, Logger * pLogger = nullptr);

    virtual ~IStorageImpl () {};

    virtual int save(size_t indexDS, size_t _size, uint8_t const * pDS) = 0;

    virtual int load(size_t indexDS, size_t & _size, uint8_t *& pDS, size_t offset = 0) = 0;

    virtual int discard(size_t indexDS, size_t _size, uint8_t *& pDS, size_t offset = 0) = 0;

protected:

    IStorageImpl(){};

private:

    IStorageImpl(IStorageImpl const & other) = delete;
    void operator=(IStorageImpl const &) = delete;

};

#endif // _ISTORAGEIMPL_H_
