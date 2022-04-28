#ifndef _ISTORAGEREADER_H_
#define _ISTORAGEREADER_H_

#include "RPSReader_Export.h"

class Logger;

class RPSReader_EXPORT IStorageReader
{
public:

    virtual ~IStorageReader () {};

    #define DEFAULT_MAX_SIZE_OF_MAP_VIEW_TO_WRITE 262144

    constexpr static size_t size_of_size_t = sizeof(size_t) / sizeof(uint8_t);

#ifdef _POSIX_MAPPED_FILES
    static size_t defaultAllocationGranularity;
#else
    constexpr static size_t defaultAllocationGranularity = 65536;
#endif


#ifdef _POSIX_MAPPED_FILES

    static __off64_t packOffset(uint32_t offsetHigh, uint32_t offsetLow) {
        // XXX: This will fail on 64-bit compiler
        __off64_t realOffset = static_cast<__off64_t>(offsetHigh) << 32 | offsetLow;
        return realOffset;
    }

#else  ///WINDOWOZ

    static inline uint64_t packOffset(uint32_t offsetHigh, uint32_t offsetLow) {
        // XXX: This will not fail on 64-bit compiler
        return static_cast<uint64_t>(offsetHigh) << 32 | offsetLow;
    }
#endif ///_POSIX_MAPPED_FILES

    static inline void unpackOffset(uint64_t offset, uint32_t & offsetHigh, uint32_t & offsetLow) {
        // XXX: This will not fail on 64-bit compiler
        offsetLow  = (uint32_t)(offset & 0xFFFFFFFFL);
        offsetHigh = (uint32_t)((offset >> 32) & 0xFFFFFFFFL);
    }

#ifdef _POSIX_MAPPED_FILES
    static int reMap(uint64_t & _mapView2ReadSize, uint8_t *& _pMapView2Read, uint64_t newSizeMapView2Read, uint32_t offsetLow, uint32_t offsetHi, uint32_t negativeOffset, int _hFile);
#else  ///WINDOWOZ
    static int reMap(uint64_t & _mapView2ReadSize, uint8_t *& _pMapView2Read, uint64_t newSizeMapView2Read, uint32_t offsetLow, uint32_t offsetHi, uint32_t negativeOffset, void * _hMap);
#endif ///_POSIX_MAPPED_FILES

#ifdef _POSIX_MAPPED_FILES
    static int evaluateNewSizeMapView(uint64_t _sizeMap, uint64_t globalOffsetToBeAvailable, uint64_t offset2StartRead, uint64_t & _mapView2ReadOffset, uint64_t & _mapView2ReadSize, uint8_t *& _pMapView2Read, int _hFile);
#else  ///WINDOWOZ
    static int evaluateNewSizeMapView(uint64_t _sizeMap, uint64_t globalOffsetToBeAvailable, uint64_t offset2StartRead, uint64_t & _mapView2ReadOffset, uint64_t & _mapView2ReadSize, uint8_t *& _pMapView2Read, void * _hMap);
#endif ///_POSIX_MAPPED_FILES

#ifdef _POSIX_MAPPED_FILES
    static int findNextDS(uint64_t _sizeMap, uint64_t & _mapView2ReadOffset, uint64_t & _mapView2ReadSize, uint8_t *& _pMapView2Read,  uint64_t & _offsetHeadDS, size_t & _sizeCurDS, int _hFile);
#else  ///WINDOWOZ
    static int findNextDS(uint64_t _sizeMap, uint64_t & _mapView2ReadOffset, uint64_t & _mapView2ReadSize, uint8_t *& _pMapView2Read,  uint64_t & _offsetHeadDS, size_t & _sizeCurDS, void * _hMap);
#endif ///_POSIX_MAPPED_FILES

    enum STORAGE_FILE_PROCESSING_ACTION{
      OPEN = 0,
      CLOSE = 1,
      READ_DS_GIVEN_INDEX = 2,
      READ_NEXT_DS = 3,
      TOTAL_STORAGE_FILE_PROCESSING_ACTION
    };

    static int processStorageFile(enum STORAGE_FILE_PROCESSING_ACTION pa, size_t indexDS, size_t & sizeDS, uint8_t *& pDS, char const * p_file_name = nullptr, Logger * pLogger = nullptr);

protected:

    IStorageReader(){};

private:

    IStorageReader(IStorageReader const & other) = delete;
    void operator=(IStorageReader const &) = delete;

};


#endif // _ISTORAGEREADER_H_
