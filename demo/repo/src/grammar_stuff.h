#ifndef TEST_DATASET_V2_STUFF_H
#define TEST_DATASET_V2_STUFF_H

  /** Merely forward declarations */
  class DS_metadata_immutable;
  class DataSet_v2;
  class DataSet_v2_sc;

  constexpr static size_t size_dataSetName =  12; // strlen(p_dataSetName);
  constexpr static char const p_dataSetName[size_dataSetName] = {"dataSetName"};

  constexpr static size_t size_dataCreatorName = 16; // strlen(p_dataCreatorName);
  constexpr static char const p_dataCreatorName[size_dataCreatorName] = {"dataCreatorName"};

  constexpr static size_t size_dataModelName = 14; // strlen(p_dataModelName);
  constexpr static char const p_dataModelName[] = {"dataModelName"};

  constexpr static size_t DIMENSION = 3;
  constexpr static char const * const ppDataSetTrackNames[DIMENSION] = {
    "Track1",
    "Track2",
    "Track3"
    };

//  static size_t pIndexesMetadataToBeSerialized[DIMENSION] = {0,0,0};

#endif /// TEST_DATASET_V2_STUFF_H
