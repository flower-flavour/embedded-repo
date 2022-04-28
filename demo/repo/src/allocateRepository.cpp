#include <iostream>

#include "../../../libs32/Logger/include/errors.h"
#include "../../../libs32/Logger/include/Logger.h"

#include "allocateRepository.h"

/**
 Creates '1'- OR '2'-type repository (see DATA_MODEL_TYPE into repository.cfg)
 PARAM [IN]  pRepoCfgFilename -- cfg-filename. MANDATORY!
 PARAM [OUT]  pRepository     -- ptr to repository instance
 PARAM [OUT]  pLogger         -- ptr to Logger instance. OPTIONAL.
*/
int allocateRepository (char const * pRepoCfgFilename, RepoManager *& pRepository, Logger * pLogger)
{
  assert(pRepoCfgFilename && "Caching Repository needs cfg-file!");
  pRepository = RepoManager::createRepoManager(pLogger, pRepoCfgFilename, true);
  if (!pRepository)
  {
      std::cout << "Can not create repository!\n";
      return _ERROR_WRONG_ARGUMENT_;
  }
  std::cout << "Repository created!\n";

  return _RC_SUCCESS_;
}///end allocateRepository
