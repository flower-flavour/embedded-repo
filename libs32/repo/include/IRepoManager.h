#ifndef _REPO_MANAGER_H_
#define _REPO_MANAGER_H_

#include <string>

#include <vector>

#include "../../DataProvider/include/DataProviderDelegate.hpp" /* DataProviderDelegate */

#include "../../repository/include/IRepository.h" /* IRepository */

#include "Repo_Export.h"

class Logger;
class DatSet;
class DataModel;
class IKey;
class IParamsModelComposition;
class IDataProvider;
typedef struct tag_logger_closure logger_closure;
typedef struct tag_register_variables_closure register_variables_closure;
typedef struct tag_ParseTree ParseTree;
typedef struct tag_repo_saving_closure saving_closure;
typedef struct tag_repo_loading_closure loading_closure;

class Repo_EXPORT RepoManager : public IRepository
{
public:

    enum IndexesRepoGrammar {
        DATA_MODEL_CFG_FILENAME,
        DATA_MODEL_TYPE,
        DIMENSION_INDEX_GRAMMAR
    };

    constexpr static char const * const grammar[DIMENSION_INDEX_GRAMMAR] = {
        "DATA_MODEL_CFG_FILENAME",
        "DATA_MODEL_TYPE"
    };

    enum DATA_MODEL_TYPES {
        NON_CACHING = 0,
        CACHING1 = 1,
        CACHING2 = 2,
        TOTAL_DATA_MODEL_TYPES
    };


    static RepoManager * createRepoManager(Logger * pLogger, char const * pCfgFilename = nullptr, bool needCachingRepoManager = false);

    virtual ~RepoManager() = default;

   int saveData(IdRepoConsumerType const & idCustomerRepo,
                           IDataProvider const * ptrConstDP,
                           size_t stepN,
                           IParamsModelComposition const * ptrVars = nullptr) override = 0;
    int getData(IdRepoConsumerType const & idCustomerRepo,
                IDataProvider * ptrDP,
                std::string const & list_DS_defs_as_str,
                size_t & dimUniqueDS_defs,
                shr_ptrUniqueDS_Indexes_t & shr_ptrUniqueDS_Indexes,
                shr_ptrArray_Shr_ptrDS_t & shr_ptrArray_Shr_ptrDS,
                size_t stepN,
                IParamsModelComposition const * ptrVars = nullptr) override = 0;

    virtual size_t sizeRepository() const = 0;

    virtual int setCallbacks(saving_closure * ptr_sv_cl, loading_closure * ptr_ld_cl) = 0;

    static int parseDSdef_CreateKey(char const * pKeyAsStr, IKey const *& ptrKey, ParseTree *& ptr_parse_tree, logger_closure * ptr_lc, const register_variables_closure * ptr_register_variables_closure);

    static int parseKey(char const * pKeyAsStr, bool checkRegisteredVariables, size_t * pDS_index, size_t * pDimArrayParentDS, size_t ** ppArrayParentDS_indexes, logger_closure * ptr_lc);

    virtual Serializer * getPtrSerializer() const override = 0;

    virtual int  setOutputStream(std::string & path) = 0;

    virtual int  closeOutputStreamAndSetDefaultStream() = 0;

protected:

    RepoManager() = default;

private:

    RepoManager(RepoManager const & other) = delete;
    void operator=(RepoManager const &) = delete;
};

#endif // _REPO_MANAGER_H_
