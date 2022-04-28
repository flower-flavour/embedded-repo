#!/bin/bash
# For debug ONLY!/bin/bash -x
mkdir -p ./bin/Debug
cp ../../libs32/Logger/bin/Debug/Loggerd.so                               ./bin/Debug/Loggerd.so
cp ../../libs32/config_parser/bin/Debug/config_parserd.so                 ./bin/Debug/config_parserd.so
cp ../../libs32/DataSet/bin/Debug/DataSetd.so                             ./bin/Debug/DataSetd.so
cp ../../libs32/RepoCache/bin/Debug/RepoCached.so                         ./bin/Debug/RepoCached.so
cp ../../libs32/RepoCacheLogic/bin/Debug/RepoCacheLogicd.so               ./bin/Debug/RepoCacheLogicd.so
cp ../../libs32/RepoDirectory/bin/Debug/RepoDirectoryd.so                 ./bin/Debug/RepoDirectoryd.so
cp ../../libs32/RepoPersistentStorage/bin/Debug/RepoPersistentStoraged.so ./bin/Debug/RepoPersistentStoraged.so
cp ../../libs32/RPSReader/bin/Debug/RPSReaderd.so                         ./bin/Debug/RPSReaderd.so
cp ../../libs32/RepoTransactions/bin/Debug/RepoTransactionsd.so           ./bin/Debug/RepoTransactionsd.so
cp ../../libs32/repo_grammar/bin/Debug/repo_grammard.so                   ./bin/Debug/repo_grammard.so
cp ../../libs32/repo/bin/Debug/repod.so                                   ./bin/Debug/repod.so
cp ../../libs32/Key/bin/Debug/Keyd.so                                     ./bin/Debug/Keyd.so
cp ./data_model.cfg                                                      ./bin/Debug/data_model.cfg
