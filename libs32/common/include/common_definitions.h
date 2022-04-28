#ifndef __LIBRARIES_COMMON_DEFINITIONS_H_
#define __LIBRARIES_COMMON_DEFINITIONS_H_

#ifndef __cplusplus

  /** number of decimal digits in int including sign */
  #define INT_DIGITS  10
#else
  /** number of decimal digits in int */
  #include <limits>
  /** number of decimal digits in int
      compile time constant!
  */
  constexpr static size_t INT_DIGITS = 1 + std::numeric_limits<int>::digits10;

#endif // __cplusplus

#define DEFINED_INT_DIGITS

#define NPOS ((size_t)-1)

#ifndef __cplusplus

  static char const * const DEFAULT_DELIMITERS = " \t\r\n";

  static size_t const DEFAULT_SIZE_OF_GRAMMAR_ITEM = 1;

  static char const DELIMITER_LIST_ITEMS = ',';

#else

  constexpr char const * const DEFAULT_DELIMITERS = " \t\r\n";

  constexpr size_t const DEFAULT_SIZE_OF_GRAMMAR_ITEM = 1;

  constexpr char const DELIMITER_LIST_ITEMS = ',';

#endif // NO __cplusplus


typedef unsigned char byte;

/*** Bool type definition ***/
#ifndef __cplusplus

    typedef unsigned char bool;
    enum BOOLVALUES{
        FALSE = 0,
        TRUE  = 1
    };

#else /* For C++ */

  /* Redefine bool's for backward compatibility  */
  #undef TRUE
  #define TRUE  true

  #undef FALSE
  #define FALSE false

#endif


#endif // __LIBRARIES_COMMON_DEFINITIONS_H_
