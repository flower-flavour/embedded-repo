#include <cstring>
#include <stdio.h>

#include "parseCLIargs.h"

/** NB One may use REPO_CFG_FILENAME, hard-coded repository cfg-filename!
       Otherwise REPO_CFG_FILENAME CLI arg is MANDATORY!

*/
#define REPO_CFG_FILENAME "repository.cfg"

/**
 * Initialize test stuff
 */
int parseCLIargs (int argc, char **argv, bool & existsCfg, size_t & max_number_saveDS_transactions, size_t & max_track_size)
{
  int rc = 0;
  existsCfg = false;
  max_number_saveDS_transactions = (size_t)-1;
  max_track_size             = (size_t)-1;

  if (( argc >= 3) && (0 == strcmp (argv[1], REPO_CFG_FILENAME_TOKEN))){
        FILE * cfg = ::fopen(argv[2], "rt");
        if(!cfg){
          return 0;
        }
        ::fclose(cfg); cfg = NULL;
        printf("command-line arg provided: %s='%s'\n", REPO_CFG_FILENAME_TOKEN, argv[2]);
        rc = 1;
        existsCfg = true;
  }

  if (( argc >= 5) && (0 == strcmp (argv[3], MAX_SAVE_DS_TRANSACTIONS_TOKEN))){
        if(0 == sscanf(argv[4], "%u", &max_number_saveDS_transactions)){
          return 0;
        }
        printf("command-line arg provided: %s=%u\n", MAX_SAVE_DS_TRANSACTIONS_TOKEN, max_number_saveDS_transactions);
        rc = 1;
  }

  if (( argc >= 7) && (0 == strcmp (argv[5], MAX_TRACK_SIZE_TOKEN))){
        if(0 == sscanf(argv[6], "%u", &max_track_size)){
            return rc;
        }
        printf("command-line arg provided: %s=%u\n", MAX_TRACK_SIZE_TOKEN, max_track_size);
        rc = 2;
   }

  if(0 == rc){
      printf("USAGE: %s %s value %s value %s value \n", argv[0], REPO_CFG_FILENAME_TOKEN, MAX_SAVE_DS_TRANSACTIONS_TOKEN, MAX_TRACK_SIZE_TOKEN);
      printf("e.g.: %s %s %s %s 1000000 %s 1000 \n", argv[0], REPO_CFG_FILENAME_TOKEN, REPO_CFG_FILENAME, MAX_SAVE_DS_TRANSACTIONS_TOKEN, MAX_TRACK_SIZE_TOKEN);
      return rc;
  }
  return rc;
} ///end parseCLIargs
