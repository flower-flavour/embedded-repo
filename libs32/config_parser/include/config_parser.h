#ifndef __CONFIG_PARSER_H_633569422542968750
#define __CONFIG_PARSER_H_633569422542968750

#include <fstream>

#include <map>
#include <boost/property_tree/ptree.hpp>

#include "config_parser_Export.h"

typedef std::map<std::string, std::string> ParamsMap;
typedef std::map<std::string, std::string>::iterator iteratorParamsMap;
typedef boost::property_tree::ptree ptree;

class ConfigParser_EXPORT ConfigParser final
{
public:
    explicit ConfigParser(std::string const & cfgName);
    ~ConfigParser();

    bool configFileExists() const;
    int parse(ParamsMap & pm);
    int parseToPTree(ptree & pt);

    static std::string setTrackNumToFileName(std::string const & fName, int trackId, int trackNum);

private:
    std::ifstream config;
};

#endif // __CONFIG_PARSER_H_633569422542968750
