#ifndef DATAPROVIDERIMPL_H
#define DATAPROVIDERIMPL_H

#include <assert.h>

#include "../../../libs32/DataProvider/include/IDataProvider_public.h"

#include "../../../libs32/repository/include/IRepository.h"

#include "./test_patterns/pattern_headers.h"

class RepoManager;
class Logger;

class DataproviderImpl : public IDataProvider
{
    public:

        DataproviderImpl(RepoManager * const & pRepository, Logger * pLogger);

        virtual ~DataproviderImpl();

        int run(size_t & sizeRequestArr, ParamsTestPattern const * const& pParams);

        virtual void reset();

        virtual IDataProvider const * getPtrDPtoSaveResults(); // final;

        virtual int getDimensionDSarray(size_t & dimension) const final;
        virtual int getDimensionDatasetByDSindex(size_t indexDS, size_t & dimension) const final;

        virtual int getCopyDSmetadata(size_t indexDS, DS_metadata_immutable *& pDS_metadata_immutable) const;

        virtual int
        getSizeDatasetTrackByDSindexAndTrackIndex(size_t indexDS, size_t indexTrack, size_t & trackSize) const final;

        virtual int getIndexesSrcDS(size_t & dim, size_t const *& pIndexes) const final;

        virtual int getCopiesPtrsToTracks(size_t indexDS,
                                          size_t & dim,
                                          double const * const * & ppTracks) const;

        virtual int getAllTrackItemsByIndexes(size_t indexDS, size_t indexTrack, size_t sizeTrackCopy, double * trackCopy) const final;

        virtual int getItemByIndexes(size_t indexDS, size_t indexTrack, size_t index, double & item) const final;

        virtual DataProviderDelegate const * const & getDataProviderDelegate(size_t indexDS) const final;

        virtual int getIndexesSrcDS(size_t & dim, boost::shared_ptr<const size_t[]> & shr_ptrIndexes) const final;


    protected:

    private:

        DataproviderImpl(const DataproviderImpl &) = delete;
        void operator=(const DataproviderImpl &) = delete;

        RepoManager * const & m_pRepository;
        Logger * m_pLogger {nullptr};

        int Urandom_save_pattern(size_t cntTA,
                                 size_t sizeRequestArr,
                                 request_t const *const& pRequestArr);

        int Urandom_load_pattern(size_t cntTA,
                                 size_t sizeRequestArr,
                                 request_t *const& pRequestArr);

        void loadByFilters(size_t indexDS);

        int Urandom_DS_generator(data_sizes & sizes, size_t minSizeDSTrack, size_t maxSizeDSTrack);
        int DS_test(size_t indexDS, char const * msg_prefix);

        size_t m_maxNumSrcDSs      {0};
        size_t m_minNumberDSTracks {0};
        size_t m_maxNumberDSTracks {0};
        size_t m_minSizeDSTrack    {0};
        size_t m_maxSizeDSTrack    {0};
        size_t m_minIndexDSToLoad  {0};
        size_t m_maxIndexDSToLoad  {0};

        /** IdRepoConsumerType */ size_t m_idCustomerRepo {0};
        size_t const m_dimSrcDSarray {1};
        size_t m_dim {0};
        DS_metadata_immutable * m_pDS_metadata {nullptr};
        size_t * m_pDataSetTrackSizes {nullptr};
        double * m_pDataTracks {nullptr};
        const double ** m_ppToDataTracks {nullptr};
        DataProviderDelegate const * m_pDataProviderDelegate {nullptr};

        size_t m_dimensionIndexesSrcDS{ 1 };
        boost::shared_ptr<size_t[]> m_IndexesSrcDS{ nullptr };
};

#endif // DATAPROVIDERIMPL_H
