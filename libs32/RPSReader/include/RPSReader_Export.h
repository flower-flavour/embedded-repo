#ifndef RPSReader_EXPORT_H
#define RPSReader_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define RPSReader_DLL_IMPORT __declspec(dllimport)
  #define RPSReader_DLL_EXPORT __declspec(dllexport)
  #define RPSReader_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define RPSReader_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define RPSReader_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define RPSReader_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define RPSReader_DLL_IMPORT
    #define RPSReader_DLL_EXPORT
    #define RPSReader_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef RPSReader_BUILT_AS_STATIC
  #define RPSReader_EXPORT
  #define RPSReader_NO_EXPORT
#else /* NOT RPSReader_BUILT_AS_STATIC */
  #ifndef RPSReader_EXPORT
    #ifdef RPSReader_EXPORTS
/* We are building this library */
      #define RPSReader_EXPORT RPSReader_DLL_EXPORT
    #else
/* We are using this library */
      #define RPSReader_EXPORT RPSReader_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define RPSReader_LOCAL RPSReader_DLL_LOCAL_VISIBILITY

  #ifndef RPSReader_NO_EXPORT
    #define RPSReader_NO_EXPORT
  #endif
#endif /* RPSReader_BUILT_AS_STATIC */

#ifndef RPSReader_DEPRECATED
  #define RPSReader_DEPRECATED __declspec(deprecated)
#endif

#ifndef RPSReader_DEPRECATED_EXPORT
  #define RPSReader_DEPRECATED_EXPORT RPSReader_EXPORT RPSReader_DEPRECATED
#endif

#ifndef RPSReader_DEPRECATED_NO_EXPORT
  #define RPSReader_DEPRECATED_NO_EXPORT RPSReader_NO_EXPORT RPSReader_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef RPSReader_NO_DEPRECATED
    #define RPSReader_NO_DEPRECATED
  #endif
#endif

#endif //RPSReader_EXPORT_H
