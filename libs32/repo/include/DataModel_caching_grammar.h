#ifndef _DATAMODEL_CACHING_GRAMMAR_H_
#define _DATAMODEL_CACHING_GRAMMAR_H_

namespace DataModel_caching_grammar{

    enum IndexesDataModelGrammar {
        initRepositorySize    = 0,
        CacheType             = 1,
        CacheSizeInBytes      = 2,
        CacheNumSegments      = 3,
        CacheSegmentSizes     = 4,
        DiskStorageType       = 5,
        StorageFileName       = 6,
        Max_NumberDS_in_Cache = 7,
        DIMENSION_INDEX_GRAMMAR
    };

    constexpr static char const * const grammar[DIMENSION_INDEX_GRAMMAR] =
    {
      "initRepositorySize",
      "CacheType",
      "CacheSizeInBytes",
      "CacheNumSegments",
      "CacheSegmentSizes",
      "DiskStorageType",
      "StorageFileName",
      "Max_NumberDS_in_Cache"
    };

    enum IndexesCacheLogicType{
      LRU  = 0,
      SLRU = 1, ///the only one multi-segmented so far
      MarkovChain = 2,
      MRU         = 3,
      Bubble      = 4,
      RANDOM      = 5,
      LFU         = 6,
      GDSF        = 7,
      TOTAL_CACHE_LOGIC_TYPES
    };

    static char const * const cacheLogicType[TOTAL_CACHE_LOGIC_TYPES] = {
      "LRU",
      "SLRU",
      "MarkovChain",
      "MRU",
      "Bubble",
      "RANDOM",
      "LFU",
      "GDSF"
    };

    enum IndexesDiskStorageType{
      PLAIN  = 0,
      SQLITE = 1,
      MMAP   = 2,
      TOTAL_DISK_STORAGE_TYPES
    };

    typedef struct tagDefaultsForDataModelParams
    {
        IndexesDataModelGrammar indexValue;
        double value;
    } defaultsForDataModelParams;

    static constexpr defaultsForDataModelParams const defaultParams[DIMENSION_INDEX_GRAMMAR] = {
            {initRepositorySize, 100},
            {CacheType, LRU},
             // In-memory cache parameters
             // 1. LRU cache
            {CacheSizeInBytes, 1000000},
            {CacheNumSegments, 1},
            {CacheSegmentSizes, 1000000},
            {DiskStorageType, MMAP},
            {StorageFileName, 0},
            {Max_NumberDS_in_Cache, 1000}
             // 2. SLRU cache
            // {SLRU_CacheSize, 32000},
            // {SLRU_CacheNumSegments, 2}
    };

    static constexpr char const * const dbName = "repo.db";
    static constexpr char const * const default_path = "./repo_db";
    static constexpr char const * const default_storage_file_name = "storage.bin";
}
#endif // _DATAMODEL_CACHING_GRAMMAR_H_
