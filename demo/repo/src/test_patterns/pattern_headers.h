#ifndef _TEST_PATTERNS_HEADERS_H_
#define _TEST_PATTERNS_HEADERS_H_

  using request_t = uint8_t;
  enum request_types {
      SAVE_TA = 0,
      LOAD_TA = 1,
      LOAD_FIRST_DS_TA = 2,
      LOAD_LAST_DS_TA  = 3,
      TOTAL_REQUEST_TYPES
  };

  enum TEST_PATTERN_IMPLS {
      URANDOM_PATTERN = 0,
      TOTAL_TEST_PATTERN_IMPLS
  };

#define DEFAULT_MAX_NUM_SRC_DATASETS 5

/***************************************************************************
  Request generators
*/
struct ParamsRequestGenerator {};

#define CARDINALITY_OF_URANDOM_PARAMS_SET 9

struct ParamsUrandomRequestGenerator : public ParamsRequestGenerator {
    size_t cardinality_of_params_set;
    double probability_save_ta;
    size_t min_number_save_ta;
    size_t max_number_save_ta;
    size_t min_number_load_ta;
    size_t max_number_load_ta;
    size_t min_number_ds_tracks;
    size_t max_number_ds_tracks;
    size_t min_size_ds_tracks;
    size_t max_size_ds_tracks;
};

int Urandom_request_generator (ParamsRequestGenerator const * const& pParams, size_t sizeRequestArr, request_t *const& pRequestArr);

/***************************************************************************
  implementations of test patterns
*/
struct ParamsTestPattern {};

struct ParamsUrandomPattern : public ParamsTestPattern {
    size_t cardinality_of_params_set;
    double probability_save_ta;
    size_t min_number_save_ta;
    size_t max_number_save_ta;
    size_t min_number_load_ta;
    size_t max_number_load_ta;
    size_t min_number_ds_tracks;
    size_t max_number_ds_tracks;
    size_t min_size_ds_tracks;
    size_t max_size_ds_tracks;
};

#endif /// _TEST_PATTERNS_HEADERS_H_
