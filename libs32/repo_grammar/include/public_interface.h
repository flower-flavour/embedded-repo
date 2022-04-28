#ifndef _REPO_GRAMMAR_PUBLIC_INTERFACE_H_
#define _REPO_GRAMMAR_PUBLIC_INTERFACE_H_

#include "Grammar.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tag_Array_str Array_str;
typedef struct tag_ParseTree ParseTree;
typedef struct tag_Filters Filters;

#include "logger_closure.h"

    int normalize(char * keyAsString);

    int makeStrCopy(char const * src, char ** _copy);

    Array_str * parse_list_DS_defs(char * pAll_DS_defs, logger_closure * ptr_lc);

    ParseTree * parse(char * strDSdef, logger_closure * ptr_lc);

    void destroyParseTree(ParseTree * pParseTree);

    size_t getSizeRegistered_variables(ParseTree * pParseTree);

    int getRegisteredVariableMetaData(ParseTree * pParseTree, size_t indexRegisteredVariable, size_t sizeBufForVariableToken, char * pAllocatedBufForVariableToken);

    int updateVariableValue(ParseTree * pParseTree, size_t indexRegisteredVariable, int newValue);

    int validateSemantics(ParseTree * pParseTree, bool needCheckRegisteredVariables, bool needValidFiltersAsSingleStr, logger_closure * ptr_lc);

    size_t getSizeParentIndexes(ParseTree * pParseTree);

    int getFirstKey(ParseTree * pParseTree, size_t * pDS_index, size_t sizeParentIndexes, size_t * pParentIndexes, logger_closure * ptr_lc);

    int getNextKey(ParseTree * pParseTree, size_t * pDS_index, size_t sizeParentIndexes, size_t * pParentIndexes, logger_closure * ptr_lc);

    size_t getSize_ArrayFilters_in_ParseTree(ParseTree const * pParseTree);

    Filters const * getPtrConstFilters(ParseTree const * pParseTree, size_t indexFilter);

    char const * getPtrConstFiltersStr(ParseTree const * pParseTree, logger_closure * ptr_lc);

    int getCopyFilterToken(Filters const * pConstFilters, enum INDEX_FILTER_TOKEN indexToken, size_t sizeBuf, char * pBufForFilterToken);

    int getFilterToken(ParseTree * pParseTree, size_t indexFilter, enum INDEX_FILTER_TOKEN indexToken, size_t sizeBuf, char * pBufForFilterToken, logger_closure * ptr_lc);

    Array_str * cloneFilterTokens(Filters const * pFilters);

    int  make_reinterpret_replace_filters(Filters const * pConstFilters,
                                      Array_str * pDS_metadata_current,
                                      Array_str * pDS_metadata_history,
                                      Array_str * pCopyDS_metadata,
                                      size_t sizeIndexesReinterpretations,
                                      size_t * pIndexesReinterpretations,
                                      logger_closure * ptr_lc);

#ifdef __cplusplus
}
#endif

#endif // _REPO_GRAMMAR_PUBLIC_INTERFACE_H_
