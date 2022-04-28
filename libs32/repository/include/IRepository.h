#ifndef _IREPOSITORY_H_
#define _IREPOSITORY_H_

#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>


#include "Repository_Export.h"

class Logger;
class IDataProvider;
class DataSet;
class IKey;
class IParamsModelComposition;

class Repository_EXPORT IRepository
{
public:

    enum REPOSITORY_INTERFACE_IMPLEMENTATIONS{
        REPO_MANAGER_NON_CACHING = 0,
        REPO_MANAGER_CACHING     = 1,
        REPO_LOGIC = 2,
        TOTAL_REPOSITORY_INTERFACE_IMPLEMENTATIONS
    };
    using shr_ptrUniqueDS_Indexes_t = boost::shared_ptr<size_t[]>;
    using sptr_DS_t = boost::shared_ptr<DataSet>;
    using shr_ptrArray_Shr_ptrDS_t = boost::shared_ptr< boost::shared_ptr<DataSet> [] >;

    using IdRepoConsumerType = size_t;

    static IRepository * createRepository(Logger * pLogger, enum REPOSITORY_INTERFACE_IMPLEMENTATIONS ri, char const * pCfgFilename = nullptr);

    virtual ~IRepository() {};

    virtual int saveData(IdRepoConsumerType const & idCustomerRepo,
                           IDataProvider const * ptrConstDP,
                           size_t stepN,
                           IParamsModelComposition const * ptrVars = nullptr) = 0;

    virtual int getData(IdRepoConsumerType const & idCustomerRepo,
                IDataProvider * ptrDP,
                std::string const & list_DS_defs_as_str,
                size_t & dimUniqueDS_defs,
                shr_ptrUniqueDS_Indexes_t & shr_ptrUniqueDS_Indexes,
                shr_ptrArray_Shr_ptrDS_t & shr_ptrArray_Shr_ptrDS,
                size_t stepN,
                IParamsModelComposition const * ptrVars = nullptr) = 0;

    class Serializer{
        public:
            virtual int serializeRepo(bool serializeAll = true, char const * delimiterValues = " ") const = 0;
            virtual int serializeDataSet(sptr_DS_t const & shr_ptrDS, char const * delimiterValues = " ") const = 0;
            virtual int serializesKey(IKey const *& pKey) const = 0;
            virtual int setOutputStream(std::ostream & out) = 0;
            virtual int closeOutputStreamAndSetDefaultStream() = 0;

        protected:
            Serializer() = default;
            virtual ~Serializer(){};

        private:
            Serializer(Serializer const & other) = delete;
            void operator=(Serializer const &) = delete;
    };

    virtual Serializer * getPtrSerializer() const = 0;

protected:

    IRepository(){};

private:

    IRepository(IRepository const & other) = delete;
    void operator=(IRepository const &) = delete;

};

#endif // _IREPOSITORY_H_
