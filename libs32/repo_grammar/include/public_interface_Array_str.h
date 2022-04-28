#ifndef _REPO_GRAMMAR_PUBLIC_ARRAY_STR_H_
#define _REPO_GRAMMAR_PUBLIC_ARRAY_STR_H_

#ifdef __cplusplus
extern "C"{
#endif

    Array_str * create_Array_str(size_t size_Arr_str, char const ** ppStr);

    Array_str * clone_Array_str(Array_str * pSrcArray_str);

    void destroy_Array_str(Array_str ** ppArray_str);

    size_t getSize_Array_str(Array_str const * pArray_str);

    char const * getPtr_str(size_t index, Array_str const * pArray_str);

    int set_Str(Array_str * pArray_str, size_t indexStr, char const * pSrcStr);

    int Array_str_toString(Array_str const * pArray_str, size_t sizeBuf, char * pBuf);

    Array_str * list_as_str_to_arr_unique_strs(char const * pList, char const * pDelimiterListItems, size_t sizeDelimiter, logger_closure * ptr_lc);

    int compare_Array_strs(Array_str const * pOperand1, Array_str const * pOperand2);

#ifdef __cplusplus
}
#endif

#endif //_REPO_GRAMMAR_PUBLIC_ARRAY_STR_H_
