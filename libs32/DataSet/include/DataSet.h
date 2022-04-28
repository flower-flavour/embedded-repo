#ifndef _DATASET__H_
#define _DATASET__H_

//OLD #include <boost/utility/string_ref.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "Metadata.h"

#include "DataSet_Export.h"

class Logger;
class DataProviderDelegate;

class DataSet_EXPORT DataSet
{
public:
    typedef boost::shared_ptr<DataSet> sptr_DS_t;
    typedef boost::shared_ptr<const DataSet> sptr_constDS_t;

    typedef boost::shared_ptr<const std::string[]> sptr_arrConstStrings_type;
    typedef boost::shared_ptr<size_t[]> sptr_size_t;
    typedef boost::shared_ptr<double[]> sptr_data;

    typedef boost::shared_ptr<std::string[]> sptr_arrStrings_type;
    typedef boost::shared_ptr<const size_t[]> sptr_const_size_t;
    typedef boost::shared_ptr<const double[]> sptr_const_data_t;

    typedef boost::shared_ptr<const double * []> sptr_arrPtrsToConstData_type;

    static DataSet * createDataSet(DS_metadata_immutable const * const & pDS_metadata_immutable,
                                   DataProviderDelegate const * const & pDPD,
                                   size_t sizeIndexes,
                                   size_t const * const indexes);

    static sptr_DS_t createShrPtrDS (DS_metadata_immutable const * const & pDS_metadata_immutable,
                                     DataProviderDelegate const * const & pDPD,
                                     size_t sizeIndexes,
                                     size_t const * const indexes);


    explicit DataSet() = default;

    virtual ~DataSet() = default;

    virtual sptr_DS_t cloneShrPtrDS(size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual DataSet * clone (size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual DS_metadata_immutable const * getDS_metadata_immutable() const = 0;

    virtual size_t getDimension() const = 0;

    virtual size_t getTotalSizeAllTracks() const = 0;

    virtual char const * const getDS_CreatorName() const = 0;

    virtual char const * const getDS_ModelName() const = 0;

    virtual char const * const getDS_Name() const = 0;

    virtual char const * const getDS_TrackName(size_t index_item) const = 0;


    virtual int getTrackSize(size_t indexTrack, size_t & size_track) const = 0;
    virtual int getTrackItemValueByIndex(size_t indexTrack, size_t indexItem, double & value) const = 0;

    static int serializeDataSet(std::ostream & ostream, DataSet const * const & ptrConstDS, char const * delimiterValues);

private:

    DataSet(const DataSet &) = delete;
    DataSet & operator=(const DataSet &) = delete;

};///end class DataSet

class DataSet_EXPORT DataSet_v1 : public DataSet
{
public:

    static DataSet_v1 * createDataSet(DS_metadata_immutable const * const & pDS_metadata_immutable,
                                       DataProviderDelegate const * const & pDPD,
                                       size_t sizeIndexes,
                                       size_t const * const indexes,
                                       DataSet_v1 * parent = nullptr);

    static boost::shared_ptr<DataSet_v1> createShrPtrDS(DS_metadata_immutable const * const & pDS_metadata_immutable,
                                                        DataProviderDelegate const * const & pDPD,
                                                        size_t sizeIndexes,
                                                        size_t const * const indexes,
                                                        DataSet_v1 * parent = nullptr);

    explicit DataSet_v1() = default;
    virtual ~DataSet_v1() = default;

    virtual boost::shared_ptr<DataSet> cloneShrPtrDS(size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;
    virtual DataSet_v1 * clone (size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual DS_metadata_immutable const * getDS_metadata_immutable() const override = 0;
    virtual size_t getRefCount() const = 0;

    virtual void incRefCount() = 0;

    virtual bool isUsed() const = 0;

    virtual void addChild(const DataSet_v1 * child) = 0;

    virtual size_t getSizeInBytes() const = 0;

    virtual int serialize(std::ostream& in) const = 0;
    static boost::shared_ptr<DataSet_v1> deserialize(std::istream& out);

    virtual int serialize(size_t& _sizeMetadataSerialized, uint8_t *& pMetadataSerialized, size_t& _sizeDataSerialized, uint8_t *& pDataSerialized) const = 0;
    static boost::shared_ptr<DataSet_v1> deserialize(size_t _sizeMetadataSerialized, uint8_t * pMetadataSerialized, size_t _sizeDataSerialized, uint8_t * pDataSerialized);

private:

    DataSet_v1(const DataSet_v1 &) = delete;
    DataSet_v1 & operator=(const DataSet_v1 &) = delete;

};///end class DataSet_v1

class DataSet_v2_sc;
class DataSet_EXPORT DataSet_v2 : public DataSet
{
public:

    static DataSet_v2 * createDataSet (DS_metadata_immutable const * const & pDS_metadata_immutable,
                                       DataProviderDelegate const * const & pDPD,
                                       size_t sizeIndexes,
                                       size_t const * const indexes,
                                       Logger * pLogger);

    static boost::shared_ptr<DataSet_v2> createShrPtrDS (DS_metadata_immutable const * const & pDS_metadata_immutable,
                                                         DataProviderDelegate const * const & pDPD,
                                                         size_t sizeIndexes,
                                                         size_t const * const indexes,
                                                         Logger * pLogger);

    explicit DataSet_v2() = default;
    virtual ~DataSet_v2() = default;

    virtual boost::shared_ptr<DataSet> cloneShrPtrDS(size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual DataSet_v2 * clone (size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual DataSet_v2_sc * clone_shallow_copy(size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual boost::shared_ptr<DataSet_v2_sc> cloneShrPtrDS_shallow_copy(size_t sizeIndexes = 0, size_t const * indexes = nullptr, DS_metadata_immutable const * pDS_metadata_reinterpreted = nullptr) const = 0;

    virtual uint8_t * resetControlBlock(size_t _sizeMemAllocated4ControlBlock, uint8_t * const & _pMemAllocated4ControlBlock) const = 0;

    virtual size_t sizeAllocated() const = 0;

    virtual size_t getRefCount() const = 0;

    virtual bool isUsed() const = 0;

    virtual size_t getSizeInBytes() const = 0;

    virtual int serialize(std::ostream& in) const = 0;
    static boost::shared_ptr<DataSet_v2> deserialize(std::istream& out);

    virtual int serialize(size_t& _sizeMetadataSerialized, uint8_t *& pMetadataSerialized, size_t& _sizeDataSerialized, uint8_t *& pDataSerialized) const = 0;

    virtual size_t getOffsetTracksInBytes() const = 0;

    static DataSet_v2 * deserialize(size_t & _sizeDataSerialized, uint8_t *& pDataSerialized);

    /** FOR DEBUG PURPOSES! */
    static size_t sizeControlBlockAllocated();

    virtual bool assertCBO() const = 0;

    static bool isValidInstance (size_t const & _sizeDataSerialized, uint8_t const * const & pDataSerialized);

    static DataSet_v2 * cast_to_DataSet_v2 (size_t & _sizeDataSerialized, uint8_t *& pDataSerialized, bool needValidation);

    static DataSet_v2 * move_instance (size_t & _sizeDstMem, uint8_t *& pDstMem, DataSet_v2 *& pDSv2ToBeMoved);

private:

    DataSet_v2(const DataSet_v2 &) = delete;
    DataSet_v2 & operator=(const DataSet_v2 &) = delete;

};///end class DataSet_v2


class DataSet_EXPORT DataSet_v2_sc : public DataSet
{
public:

    virtual ~DataSet_v2_sc() = default;

    virtual size_t sizeAllocated() const = 0;

    virtual size_t getRefCount() const = 0;

    virtual bool isUsed() const = 0;

    virtual size_t getSizeInBytes() const = 0;

protected:

    explicit DataSet_v2_sc() = default;

private:

    DataSet_v2_sc(const DataSet_v2_sc &) = delete;
    DataSet_v2_sc & operator=(const DataSet_v2_sc &) = delete;

};///end class DataSet_v2_sc

class ControlBlock
{
public:

    virtual ~ControlBlock(){};

    virtual DataSet_v2 const * get() const = 0;

    virtual bool isLockedByOwner() const = 0;

    virtual bool isLockedByShallowCopy()  const = 0;

    virtual int lockByShallowCopy()   = 0;

    virtual int unlockByShallowCopy()  = 0;

protected:
    ControlBlock (){};
};///end ControlBlockunlockByShallowCopy

class  ControlBlockForOwner : public ControlBlock
{
public:

    virtual ~ControlBlockForOwner(){};

    virtual int reset(DataSet_v2 const * _pDSv2) = 0;

    virtual int lockByOwner()   = 0;

    virtual int unlockByOwner()  = 0;

    virtual size_t refCount() const = 0;

protected:
    ControlBlockForOwner (){};
};///end ControlBlockForOwner

#endif ///_DATASET__H_
