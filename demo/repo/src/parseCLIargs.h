#ifndef PARSECLIARGS_H_INCLUDED
#define PARSECLIARGS_H_INCLUDED

  #define REPO_CFG_FILENAME_TOKEN        "-REPO_CFG_FILENAME"
  #define REPO_CACHE_LOGIC_TYPE_TOKEN    "-REPO_CACHE_LOGIC"
  #define MAX_SAVE_DS_TRANSACTIONS_TOKEN "-MAX_SAVE_DS_TRANSACTIONS"
  #define MAX_TRACK_SIZE_TOKEN           "-MAX_TRACK_SIZE"

  int parseCLIargs (int argc, char **argv, bool & existsCfg, size_t & max_number_saveDS_transactions, size_t & max_track_size);

  #define MAX_ITERATIONS              100
  #define MAX_TRACK_SIZE              1000

  #define MAX_SAVE_DS_TRANSACTIONS    1000
  #define MAX_NUMBER_DS_IN_CACHE      1000

#endif // PARSECLIARGS_H_INCLUDED
