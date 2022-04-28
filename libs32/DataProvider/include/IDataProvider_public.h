#ifndef __IDATAPROVIDER__H__633569422542968750
#define __IDATAPROVIDER__H__633569422542968750

#include "DataProvider_Export.h"

class Logger;
class DS_metadata_immutable;
class IDataProvider_Impl;
class DataProviderDelegate;

class DataProvider_EXPORT IDataProvider
{
public:

    virtual ~IDataProvider() = default;

    virtual void reset() = 0;

    virtual IDataProvider const * getPtrDPtoSaveResults() = 0;

    virtual int getDimensionDSarray(size_t & dimension) const = 0;

    virtual int getCopyDSmetadata(size_t indexDS, DS_metadata_immutable *& pDS_metadata_immutable) const = 0;

    virtual int getDimensionDatasetByDSindex(size_t indexDS, size_t & dimension) const = 0;

    virtual int
    getSizeDatasetTrackByDSindexAndTrackIndex(size_t indexDS, size_t indexTrack, size_t & trackSize) const = 0;

    virtual int getIndexesSrcDS(size_t & dim, size_t const *& pIndexes) const = 0;

    virtual int getCopiesPtrsToTracks(size_t indexDS,
                                      size_t & dim,
                                      double const * const * & ppTracks) const = 0;

    virtual int getAllTrackItemsByIndexes(size_t indexDS, size_t indexTrack, size_t sizeTrackCopy, double * trackCopy) const = 0;

    virtual int getItemByIndexes(size_t indexDS, size_t indexTrack, size_t index, double & item) const = 0;

    virtual DataProviderDelegate const * const & getDataProviderDelegate(size_t indexDS) const = 0;

protected:

    IDataProvider() = default;

private:

    IDataProvider(const IDataProvider &) = delete;
    void operator=(const IDataProvider &) = delete;

};

#endif
