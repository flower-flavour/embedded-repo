#ifndef TEST_REPOSITORY_HEADERS_H_INCLUDED
#define TEST_REPOSITORY_HEADERS_H_INCLUDED

#include "../../../libs32/repo/include/IRepoManager.h"

  int allocateRepository (char const * pRepoCfgFilename, RepoManager *& pRepository, Logger * pLogger);

#endif // TEST_REPOSITORY_HEADERS_H_INCLUDED
