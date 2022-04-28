#pragma once

#include "DataSet.h"

class DataSet_EXPORT DataSetHelper
{
public:

    static int isNANInDStrack(DataSet::sptr_constDS_t const & dataSet,
                                size_t indexOfTrack);

    explicit DataSetHelper() = default;
    ~DataSetHelper() = default;
    DataSetHelper(const DataSetHelper &) = delete;
    DataSetHelper & operator=(const DataSetHelper &) = delete;

};
