#include <stddef.h>
#include <iostream>
#include <random>

#include "../../../libs32/Logger/include/errors.h"
#include "../../../libs32/Logger/include/Logger.h"

#include "../../../libs32/DataSet/include/data_sizes.h"
#include "../../../libs32/DataSet/include/Metadata.h"
#include "../../../libs32/DataSet/include/DataSet.h"
#include "../../../libs32/Key/include/IKey.h"

#include "../../../libs32/repo/include/IRepoManager.h"

#include "grammar_stuff.h"
#include "./test_patterns/Urandom_generators.h"

#include "DataproviderImpl.h"

using shr_ptrUniqueDS_Indexes_t = IRepository::shr_ptrUniqueDS_Indexes_t;
using sptr_DS_t                 = IRepository::sptr_DS_t;
using shr_ptrArray_Shr_ptrDS_t  = IRepository::shr_ptrArray_Shr_ptrDS_t;

static std::random_device rd;
static std::mt19937 mt(rd());

static size_t Urandom_indexDS_gen(size_t minIndexDSToLoad, size_t maxIndexDSToLoad)
{
    std::uniform_int_distribution<size_t> rnd_index(minIndexDSToLoad, maxIndexDSToLoad);
    return rnd_index(mt);
}

static int makeFilterPrefix (size_t indexDS, DataproviderImpl const * const & pDPI, std::string & filterPrefix, Logger * pLogger)
{
  size_t _dimensionIndexesSrcDS = 0;
  size_t const * _IndexesSrcDS = nullptr;
  int rc = pDPI->getIndexesSrcDS(_dimensionIndexesSrcDS, _IndexesSrcDS);
  assert(_RC_SUCCESS_ == rc);
  IKey * pKey = IKey::createKey(indexDS, _dimensionIndexesSrcDS, _IndexesSrcDS, pLogger);
  delete [] _IndexesSrcDS;
  _IndexesSrcDS = nullptr;
  filterPrefix = pKey->toString();
  delete pKey;
  pKey = nullptr;

  filterPrefix += RepoGrammar::DELIMITER_KEY_FILTER;

  DS_metadata_immutable * pDS_metadata_immutable = nullptr;
  rc = pDPI->getCopyDSmetadata(0, pDS_metadata_immutable);

  filterPrefix += pDS_metadata_immutable->getDS_CreatorName();
  filterPrefix += RepoGrammar::DELIMITER_FILTER_TOKENS;
  filterPrefix += pDS_metadata_immutable->getDS_ModelName();
  filterPrefix += RepoGrammar::DELIMITER_FILTER_TOKENS;
  filterPrefix += pDS_metadata_immutable->getDS_Name();
  filterPrefix += RepoGrammar::DELIMITER_FILTER_TOKENS;

  delete pDS_metadata_immutable;
  pDS_metadata_immutable = nullptr;

  return _RC_SUCCESS_;
}///end makeFilterPrefix

DataproviderImpl::DataproviderImpl(RepoManager * const & pRepository, Logger * pLogger)
                  : m_pRepository(pRepository)
                  , m_pLogger(pLogger)
{
  m_idCustomerRepo = 0;
  m_IndexesSrcDS = boost::make_shared<size_t[]>(m_dimensionIndexesSrcDS);
  assert(nullptr != m_IndexesSrcDS);
  for(size_t i = 0; i < m_dimensionIndexesSrcDS; ++i){
    m_IndexesSrcDS[i] = 0;
  }
  /**  to start RANDOM PATTERN
    we MUST populate repository with two DSs at least 
  */
  data_sizes sizes { DIMENSION, NULL, 0, 0, NULL, 0};
  int rc = Urandom_DS_generator(sizes, m_minSizeDSTrack, m_maxSizeDSTrack);
  assert(_RC_SUCCESS_ == rc);

  rc = m_pRepository->saveData(m_idCustomerRepo,
                               this,
                               0);
  assert(_RC_SUCCESS_ == rc);
  rc = m_pRepository->saveData(m_idCustomerRepo,
                               this,
                               0);
  assert(_RC_SUCCESS_ == rc);
}

DataproviderImpl::~DataproviderImpl()
{
    reset();
}


int DataproviderImpl::run(size_t & sizeRequestArr,
                          ParamsTestPattern const * const& pParams)
{
    assert( pParams && sizeRequestArr && m_pRepository);
    ParamsUrandomPattern const * const pParamsPattern = static_cast<ParamsUrandomPattern const * const>(pParams);
    assert(CARDINALITY_OF_URANDOM_PARAMS_SET == pParamsPattern->cardinality_of_params_set);

    ParamsUrandomRequestGenerator paramsRequestGenerator;
    paramsRequestGenerator.cardinality_of_params_set = CARDINALITY_OF_URANDOM_PARAMS_SET;

    paramsRequestGenerator.probability_save_ta = pParamsPattern->probability_save_ta;
    assert((paramsRequestGenerator.probability_save_ta > 0.0f) && (paramsRequestGenerator.probability_save_ta < 1.0f));

    paramsRequestGenerator.min_number_save_ta = pParamsPattern->min_number_save_ta;
    assert(paramsRequestGenerator.min_number_save_ta > 0);
    paramsRequestGenerator.max_number_save_ta = pParamsPattern->max_number_save_ta;
    assert(paramsRequestGenerator.min_number_save_ta <= paramsRequestGenerator.max_number_save_ta);

    paramsRequestGenerator.min_number_load_ta  = pParamsPattern->min_number_load_ta;
    assert(paramsRequestGenerator.min_number_load_ta > 0);
    paramsRequestGenerator.max_number_load_ta = pParamsPattern->max_number_load_ta;
    assert(paramsRequestGenerator.min_number_load_ta <= paramsRequestGenerator.max_number_load_ta);

    request_t * pRequestArr = new (std::nothrow) request_t[sizeRequestArr];
    assert(pRequestArr);
    int rc = Urandom_request_generator (&paramsRequestGenerator, sizeRequestArr, pRequestArr);
    assert(_RC_SUCCESS_ == rc);
    m_maxNumSrcDSs        = DEFAULT_MAX_NUM_SRC_DATASETS;
    m_minNumberDSTracks   = pParamsPattern->min_number_ds_tracks;
    m_maxNumberDSTracks   = pParamsPattern->max_number_ds_tracks;
    m_minSizeDSTrack      = pParamsPattern->min_size_ds_tracks;
    m_maxSizeDSTrack      = pParamsPattern->max_size_ds_tracks;
    size_t sizeRepository = m_pRepository->sizeRepository();
    size_t cntTA = 0;
    while(cntTA < sizeRequestArr)
    {
        sizeRepository = m_pRepository->sizeRepository();
        if(SAVE_TA == pRequestArr[cntTA])
        {
            // std::cout << "Urandom_save_pattern" << std::endl;
            cntTA += Urandom_save_pattern(cntTA,
                                          sizeRequestArr,
                                          pRequestArr);
            }
            else
            {
                m_minIndexDSToLoad = 1;
                m_maxIndexDSToLoad = sizeRepository - 1;
                // std::cout << "Urandom_load_pattern" << std::endl;
                cntTA += Urandom_load_pattern(cntTA,
                                              sizeRequestArr,
                                              pRequestArr);

                assert(_RC_SUCCESS_ == rc);
            }
    }
    delete pRequestArr;
    return _RC_SUCCESS_;
}

void DataproviderImpl::reset()
{
    delete m_pDataProviderDelegate;
    m_pDataProviderDelegate = nullptr;
    delete [] m_ppToDataTracks;
    m_ppToDataTracks = nullptr;
    delete [] m_pDataTracks;
    m_pDataTracks = nullptr;
    delete [] m_pDataSetTrackSizes;
    m_pDataSetTrackSizes = nullptr;
    delete m_pDS_metadata;
    m_pDS_metadata = nullptr;
}

IDataProvider const * DataproviderImpl::getPtrDPtoSaveResults(){
    return this;
}

int DataproviderImpl::getDimensionDSarray(size_t & dimension) const{
  dimension = m_dimSrcDSarray;
  return _RC_SUCCESS_;
}

int DataproviderImpl::getDimensionDatasetByDSindex(size_t indexDS, size_t & dimension) const{
    if(indexDS + 1 > m_dimSrcDSarray){
        return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
    }
    dimension = m_dim;
    return _RC_SUCCESS_;
}

int DataproviderImpl::getCopyDSmetadata(size_t indexDS, DS_metadata_immutable *& pDS_metadata_immutable) const
{
  if(indexDS + 1 > m_dimSrcDSarray){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }
  if(!m_pDS_metadata){
    return _ERROR_WRONG_WORKFLOW_;
  }
  pDS_metadata_immutable = m_pDS_metadata->clone();
  return _RC_SUCCESS_;
}

int DataproviderImpl::getSizeDatasetTrackByDSindexAndTrackIndex(size_t indexDS, size_t indexTrack, size_t & trackSize) const
{
  if(indexDS + 1 > m_dimSrcDSarray){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }

  if(indexTrack + 1 > m_dim){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }

  if(!m_pDataSetTrackSizes){
    return _ERROR_WRONG_WORKFLOW_;
  }
  trackSize = m_pDataSetTrackSizes[indexTrack];
  return _RC_SUCCESS_;
}

int DataproviderImpl::getIndexesSrcDS(size_t & dim, size_t const *& pIndexes) const
{
    if(! m_dimensionIndexesSrcDS){
        return _ERROR_WRONG_WORKFLOW_;
    }
    dim = m_dimensionIndexesSrcDS;

    if(pIndexes){
        delete [] pIndexes;
        pIndexes = nullptr;
    }
    pIndexes = new (std::nothrow) size_t[dim];
    assert(pIndexes);
    size_t const * const pSrc = m_IndexesSrcDS.get();
    memcpy((void*)pIndexes, pSrc, dim * sizeof(size_t));
    return _RC_SUCCESS_;
}

int DataproviderImpl::getCopiesPtrsToTracks(size_t indexDS,
                                            size_t & dim,
                                            double const * const * & ppTracks) const
{
  if(indexDS + 1 > m_dimSrcDSarray){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }
  if(!m_ppToDataTracks){
    return _ERROR_WRONG_WORKFLOW_;
  }

  ppTracks = new (std::nothrow) double const *[m_dim];
  assert(ppTracks);
  ::memcpy((void*)ppTracks, (void*)m_ppToDataTracks, m_dim * sizeof(double const *));
  return _RC_SUCCESS_;
}

int DataproviderImpl::getAllTrackItemsByIndexes(size_t indexDS, size_t indexTrack, size_t sizeTrackCopy, double * trackCopy) const
{
  if(indexDS + 1 > m_dimSrcDSarray){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }

  if(indexTrack + 1 > m_dim){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }
  if(sizeTrackCopy != m_pDataSetTrackSizes[indexTrack]){
    return _ERROR_NO_ROOM_;
  }
  ::memcpy((void*)trackCopy, (void*)m_ppToDataTracks[indexTrack], sizeTrackCopy * sizeof(double));
  return _RC_SUCCESS_;
}

int DataproviderImpl::getItemByIndexes(size_t indexDS, size_t indexTrack, size_t index, double & item) const
{
  if(indexDS + 1 > m_dimSrcDSarray){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }
  if(indexTrack + 1 > m_dim){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }
  if(index + 1 > m_pDataSetTrackSizes[indexTrack]){
    return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
  }
  item = m_ppToDataTracks[indexTrack][index];
  return _RC_SUCCESS_;
}

DataProviderDelegate const * const & DataproviderImpl::getDataProviderDelegate(size_t indexDS) const
{
  assert(1 ==   m_dimSrcDSarray);
  return m_pDataProviderDelegate;
}

int DataproviderImpl::getIndexesSrcDS(size_t & dim, boost::shared_ptr<const size_t[]> & shr_ptrIndexes) const
{
    if(! m_dimensionIndexesSrcDS){
        return _ERROR_WRONG_WORKFLOW_;
    }
    dim = m_dimensionIndexesSrcDS;

    shr_ptrIndexes = m_IndexesSrcDS;

    return _RC_SUCCESS_;
}
///private stuff
int DataproviderImpl::Urandom_save_pattern(size_t cntTA,
                                           size_t sizeRequestArr,
                                           request_t const *const& pRequestArr)
{
    assert(m_pRepository);
    int rc;
    ///Into this implementation the number of DS's tacks is hardcoded as DIMENSION!
    /// and parameters minNumberDSTracks, maxNumberDSTracks are ignored.
    ///So far this way! Because this implementation keeps static array (of size DIMENSION) with track names!
    assert((m_minNumberDSTracks == m_maxNumberDSTracks) && (m_minNumberDSTracks == DIMENSION));
    assert(m_minSizeDSTrack <= m_maxSizeDSTrack);

    ///One may replace DIMENSION with random numberDSTracks, e.g. from U[1,DIMENSION]
    data_sizes sizes { DIMENSION, NULL, 0, 0, NULL, 0};

    size_t sizeRepository = m_pRepository->sizeRepository();
    std::cout << "start test_save at size Repository = " << sizeRepository << std::endl;

    size_t numberSaveTA = 0;

    m_maxNumSrcDSs     = DEFAULT_MAX_NUM_SRC_DATASETS < sizeRepository ? DEFAULT_MAX_NUM_SRC_DATASETS : sizeRepository;

    while((cntTA < sizeRequestArr) && (SAVE_TA == pRequestArr[cntTA]))
    {
        ++cntTA;
        sizeRepository = m_pRepository->sizeRepository();

        rc = Urandom_DS_generator(sizes, m_minSizeDSTrack, m_maxSizeDSTrack);
        assert(_RC_SUCCESS_ == rc);

        /** test setData */
        rc = m_pRepository->saveData(m_idCustomerRepo,
                                     this,
                                     0);
        assert(_RC_SUCCESS_ == rc);

        ///OK in single thread mode only! pRepository->getCurrentSize();
        size_t indexDS = m_pRepository->sizeRepository();
        char const * msg_prefix = "test_save";

        rc = DS_test(indexDS, msg_prefix);
        assert(_RC_SUCCESS_ == rc);
        ++numberSaveTA;
    }
///DEBUG
    std::cout << " Urandom_save_pattern accomplished: " << numberSaveTA << std::endl;
///END DEBUG
    return numberSaveTA;
}///end Urandom_save_pattern

int DataproviderImpl::Urandom_load_pattern(size_t cntTA,
                                           size_t sizeRequestArr,
                                           request_t *const& pRequestArr)
{
    assert(m_minIndexDSToLoad <= m_maxIndexDSToLoad);
    size_t sizeRepository = m_pRepository->sizeRepository();
    std::cout << "start test_load at size Repository = " << sizeRepository << std::endl;

    size_t numberLoadTA = 0;
    while((cntTA < sizeRequestArr) && (LOAD_TA == pRequestArr[cntTA]))
    {
        ++cntTA;
        size_t indexDS_to_load = (m_minIndexDSToLoad = m_maxIndexDSToLoad)
        ? m_minIndexDSToLoad
        : Urandom_indexDS_gen(m_minIndexDSToLoad, m_maxIndexDSToLoad);

        char const * msg_prefix = "test_load";
        int rc = DS_test(indexDS_to_load, msg_prefix);
        assert(_RC_SUCCESS_ == rc);

        ++numberLoadTA;
    }
///DEBUG
    std::cout << " Urandom_load_pattern accomplished: " << numberLoadTA << std::endl;
///END DEBUG
    return numberLoadTA;
}///end Urandom_load_pattern

int DataproviderImpl::Urandom_DS_generator(data_sizes & sizes, size_t minSizeDSTrack, size_t maxSizeDSTrack)
{
  assert(minSizeDSTrack <= maxSizeDSTrack);

  m_dim = DIMENSION;
  assert(m_dim == sizes.dimension);
  if(m_pDS_metadata){
    delete m_pDS_metadata;
    m_pDS_metadata = nullptr;
  }
  m_pDS_metadata = DS_metadata_immutable::createDS_metadata_immutable(
            size_dataSetName, p_dataSetName,
            size_dataCreatorName, p_dataCreatorName,
            size_dataModelName, p_dataModelName,
            m_dim,
            ppDataSetTrackNames);
  assert(m_pDS_metadata);

  if(m_pDataSetTrackSizes){
    delete [] m_pDataSetTrackSizes;
    m_pDataSetTrackSizes = nullptr;
  }
  m_pDataSetTrackSizes =  new (std::nothrow) size_t[m_dim];
  assert(m_pDataSetTrackSizes);
  memset(m_pDataSetTrackSizes, 0, m_dim * sizeof(size_t));

  size_t totalSizeAllTracks = 0;

  if(m_pDataTracks){
      delete [] m_pDataTracks;
      m_pDataTracks = nullptr;
  }

  size_t var_track_size = maxSizeDSTrack - minSizeDSTrack + 1;
  getRndSizes(var_track_size, m_dim, m_pDataSetTrackSizes);

  for(size_t i = 0; i < m_dim; ++i){
          m_pDataSetTrackSizes[i] += minSizeDSTrack;
          totalSizeAllTracks += m_pDataSetTrackSizes[i];
  }
  m_pDataTracks = new (std::nothrow) double[totalSizeAllTracks];
  assert(m_pDataTracks);

  getRndValues(totalSizeAllTracks, m_pDataTracks);

  if(m_ppToDataTracks){
    delete [] m_ppToDataTracks;
    m_ppToDataTracks = nullptr;
  }
  m_ppToDataTracks = new (std::nothrow) double const *[m_dim];
  assert(m_ppToDataTracks);
  size_t offsetDataTrack = 0;
  for(size_t i = 0; i < m_dim; ++i){
      m_ppToDataTracks[i] = &m_pDataTracks[offsetDataTrack];
      offsetDataTrack += m_pDataSetTrackSizes[i];
  }

  if(m_pDataProviderDelegate){
    delete m_pDataProviderDelegate;
    m_pDataProviderDelegate = nullptr;
  }
  m_pDataProviderDelegate = new (std::nothrow) DataProviderDelegate(m_dim, m_pDataSetTrackSizes, m_ppToDataTracks);
  assert(m_pDataProviderDelegate);

  sizes.sizeAllTracks      = totalSizeAllTracks;
  sizes.sizeRequiredTracks = totalSizeAllTracks;

  return _RC_SUCCESS_;
}///end Urandom_DS_generator

int DataproviderImpl::DS_test(size_t indexDS, char const * msg_prefix)
{
  IKey * pKey = IKey::createKey(indexDS, m_dimensionIndexesSrcDS, m_IndexesSrcDS.get(), m_pLogger);
  std::string list_DS_defs_as_str = pKey->toString();
  delete pKey;
  pKey = nullptr;
  size_t dimUniqueDS_defs = 0;
  shr_ptrUniqueDS_Indexes_t shr_ptrUniqueDS_Indexes;
  shr_ptrArray_Shr_ptrDS_t  shr_ptrArray_Shr_ptrDS;
  size_t stepN = 0;
  IParamsModelComposition const * ptrVars = nullptr;

  /** test getDataByIndex */
  int rc = m_pRepository->getData(m_idCustomerRepo,
                                  this,
                                  list_DS_defs_as_str,
                                  dimUniqueDS_defs,
                                  shr_ptrUniqueDS_Indexes,
                                  shr_ptrArray_Shr_ptrDS,
                                  stepN,
                                  ptrVars);
  assert(_RC_SUCCESS_ == rc);

  /** test getDataByRepoKeyAndFilters */
  loadByFilters(indexDS);

  return _RC_SUCCESS_;
}///end DS_test

void DataproviderImpl::loadByFilters(size_t indexDS)
{
    std::string strDSdef;
    makeFilterPrefix (indexDS, this, strDSdef, m_pLogger);

    for(size_t i = 0; i < m_dim; ++i)
    {
        std::string tmpKeyAndFilter = strDSdef;
        tmpKeyAndFilter += m_pDS_metadata->getDS_TrackName(i);
        size_t dimUniqueDS_defs = 0;
        shr_ptrUniqueDS_Indexes_t shr_ptrUniqueDS_Indexes;
        shr_ptrArray_Shr_ptrDS_t  shr_ptrArray_Shr_ptrDS;
        size_t stepN = 0;
        IParamsModelComposition const * ptrVars = nullptr;
        int rc = m_pRepository->getData(m_idCustomerRepo,
                                        this,
                                        tmpKeyAndFilter,
                                        dimUniqueDS_defs,
                                        shr_ptrUniqueDS_Indexes,
                                        shr_ptrArray_Shr_ptrDS,
                                        stepN,
                                        ptrVars);
        assert(_RC_SUCCESS_ == rc);
    }

  return;
}///end loadByFilters
