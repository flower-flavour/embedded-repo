#ifndef _DATA_SIZES_H_
#define _DATA_SIZES_H_

typedef struct tag_data_sizes{
    size_t dimension;
    size_t const * pDataSetTrackSizes;
    size_t sizeAllTracks;
    size_t sizeAllocated;
    double const * const * ppDataTracks;
    size_t sizeRequiredTracks;
} data_sizes;

#endif // _DATA_SIZES_H_
