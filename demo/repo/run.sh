#!/bin/bash
# For debug ONLY!/bin/bash -x

source ./update_sos.sh
cp ./bin/TEST_repod ./
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./bin/Debug

SECONDS=0

# NB: Hard-coded repository cfg-filename! Mandatory!
# REPO_CFG_FILENAME "repository.cfg"

 ./TEST_repod -REPO_CFG_FILENAME repository.cfg -MAX_SAVE_DS_TRANSACTIONS 1000000 -MAX_TRACK_SIZE 5

duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed."

rm -f ./TEST_repod
rm -f ./bin/Debug/*.so

