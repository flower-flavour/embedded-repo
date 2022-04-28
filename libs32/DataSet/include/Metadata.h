#ifndef _METADATA_DS_H_
#define _METADATA_DS_H_

#include <stdlib.h>
#include <ostream>

#include "../../repo_grammar/include/Grammar.h" /* enum INDEX_FILTER_TOKEN */

#include "DataSet_Export.h"

typedef struct tag_Array_str Array_str;
typedef struct tagDataSetNamesAsStruct DataSetNamesAsStruct;

class DataSet_EXPORT DS_metadata_immutable {

public:

    static DS_metadata_immutable * createDS_metadata_immutable(size_t size_dataSetName, char const * const & p_dataSetName,
                                           size_t size_dataCreatorName, char const * const & p_dataCreatorName,
                                           size_t size_dataModelName, char const * const & p_dataModelName,
                                           size_t dimension,
                                           char const * const * const & ppDataSetTrackNames);

    virtual ~DS_metadata_immutable() {};

    virtual bool isValidInstance() const = 0;

    virtual size_t getDimension() const = 0;

    virtual char const * const getDS_CreatorName() const = 0;

    virtual char const * const getDS_ModelName() const = 0;

    virtual char const * const getDS_Name() const = 0;

    virtual char const * const getDS_TrackName(size_t index) const = 0;

    virtual int getCopiesDS_TrackNames(size_t & numberTrackNames, char ** & ppTrackNames) const = 0;

    virtual DS_metadata_immutable * clone() const = 0;

    virtual size_t sizeAllocated() const = 0;


    virtual int serialize(std::ostream& out) const = 0;
    static DS_metadata_immutable * deserialize(std::istream& in);

    virtual uint8_t* serialize(size_t& _size) const = 0;

    virtual uint8_t* serialize(size_t sizeIndexes,
                               size_t * const& pIndexesMetadataToBeSerialized,
                               size_t& _size) const = 0;

    static DS_metadata_immutable * deserialize(size_t _size, uint8_t *& pMetadataSerialized);
    static DS_metadata_immutable * cast_to_DS_metadata_immutable(size_t _size, uint8_t *& pMetadataSerialized, bool needValidation, bool removePrefix);

    static DS_metadata_immutable const * createDS_metadata_immutable (size_t dimension, Array_str const ** ppArray_str_newMetaData);

    static int compareDS_MetadataItems(DS_metadata_immutable const * const & pConstDS_metadata_immutable, std::string const & subfilter, enum INDEX_FILTER_TOKEN indexSubfilter);

protected:

    DS_metadata_immutable() = default;

private:

    DS_metadata_immutable(const DS_metadata_immutable &) = delete;
    DS_metadata_immutable & operator=(const DS_metadata_immutable &) = delete;

};///end class DS_metadata_immutable

class DataSet_EXPORT DS_metadata_mutable : public DS_metadata_immutable {

public:

    static DS_metadata_mutable * createDS_metadata_mutable(size_t size_dataSetName, char const * const & p_dataSetName,
                                           size_t size_dataCreatorName, char const * const & p_dataCreatorName,
                                           size_t size_dataModelName, char const * const & p_dataModelName,
                                           size_t dimension,
                                           char const * const * const & ppDataSetTrackNames);

    virtual ~DS_metadata_mutable() {};

    bool isValidInstance() const final {
        bool Kapets = false;
        /// "NOT IMPLEMENTED YET!"
        return Kapets;
    }

    virtual DS_metadata_mutable * clone() const = 0;

    static DS_metadata_mutable * deserialize(std::istream& in);

    static DS_metadata_mutable * deserialize(size_t _size, uint8_t *& in);

protected:

    DS_metadata_mutable() = default;

private:

    DS_metadata_mutable(const DS_metadata_mutable &) = delete;
    DS_metadata_mutable & operator=(const DS_metadata_mutable &) = delete;

};///end class DS_metadata_mutable

#endif // _METADATA_DS_H_
