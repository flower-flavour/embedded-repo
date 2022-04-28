#ifndef _DATA_PROVIDER_DELEGATE_H_
#define _DATA_PROVIDER_DELEGATE_H_
#include <assert.h>
#include <cstddef>
#include <cstring>

#include "../../Logger/include/errors.h"

#include "DataProvider_Export.h"

class DataProvider_EXPORT DataProviderDelegate
{
  public:
      DataProviderDelegate(size_t dimension, size_t const * const & pDSTrackSizes, double const * const * const & ppDataTracks)
      : m_dimension (dimension)
      {
          if(!m_dimension){
              return;
          }
          assert(pDSTrackSizes && ppDataTracks);
          m_pDSTrackSizes = new (std::nothrow) size_t[m_dimension];
          assert(m_pDSTrackSizes);
          memcpy((void*)m_pDSTrackSizes, pDSTrackSizes, m_dimension * sizeof(size_t) );
          m_ppDataTracks = new (std::nothrow) double const *[m_dimension];
          assert(m_ppDataTracks);
          memcpy((void*)m_ppDataTracks, ppDataTracks, m_dimension * sizeof(double const * const) );
      }
      ~DataProviderDelegate()
      {
          delete [] m_ppDataTracks;
          m_ppDataTracks = nullptr;
          delete [] m_pDSTrackSizes;
          m_pDSTrackSizes = nullptr;
      }

      int getDimension() const
      {
          return m_dimension;
      }

      int getSizeTrack(size_t indexTrack, size_t & sizeTrack) const
      {
          if(indexTrack < m_dimension){
              sizeTrack = m_pDSTrackSizes[indexTrack];
              return _RC_SUCCESS_;
          }
          return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
      }

      int getCopiesTrackSizes(size_t & sizeTrackSizes, size_t * & pTrackSizes) const
      {
          sizeTrackSizes = 0;
          if(pTrackSizes){
              delete [] pTrackSizes;
          }

          if(!m_pDSTrackSizes){
              return _ERROR_WRONG_OUTPUT_DATA_;
          }
          pTrackSizes = new (std::nothrow) size_t[m_dimension];
          assert(pTrackSizes);
          if(!pTrackSizes){
              return _ERROR_NO_ROOM_;
          }
          memcpy((void*)pTrackSizes, m_pDSTrackSizes, m_dimension * sizeof(size_t) );
          return _RC_SUCCESS_;
      }

      size_t getSizeAllTracks() const {
          size_t _size = 0u;
          for(size_t i = 0; i < m_dimension; ++i){
              _size += m_pDSTrackSizes[i];
          }
          return _size;
      }

      int getPtrConstDataTrack(size_t indexTrack, double const * & pConstDataTrack) const
      {
          if(indexTrack < m_dimension){
              pConstDataTrack = m_ppDataTracks[indexTrack];
              return _RC_SUCCESS_;
          }
          return _ERROR_OUT_OF_ARRAY_BOUNDARY_;
      }

      int getCopiesPtrsConstDataTracks(size_t & sizePtrsDataTracks, double const **& pPtrsDataTracks) const
      {
          sizePtrsDataTracks = 0;
          if(pPtrsDataTracks){
              delete [] pPtrsDataTracks;
          }
          if(!m_ppDataTracks){
              return _ERROR_WRONG_OUTPUT_DATA_;
          }
          pPtrsDataTracks = new (std::nothrow) double const *[m_dimension];
          assert(pPtrsDataTracks);
          if(!pPtrsDataTracks){
              return _ERROR_NO_ROOM_;
          }
          memcpy((void*)pPtrsDataTracks, m_ppDataTracks, m_dimension * sizeof(double const *) );
          return _RC_SUCCESS_;
      }

  private:
    /** assign and copy CTORs are disabled */
    DataProviderDelegate(const DataProviderDelegate &) = delete;
    void operator=(const DataProviderDelegate &) = delete;

    size_t const m_dimension;
    size_t const * m_pDSTrackSizes {nullptr};
    double const * const * m_ppDataTracks {nullptr};

///TODO!!! for derived class in repository!     size_t sizeAllocated;
///TODO!!! for derived class in repository!     size_t sizeRequiredTracks;
};


#endif // _DATA_PROVIDER_DELEGATE_H_
