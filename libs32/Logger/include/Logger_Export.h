#ifndef Logger_EXPORT_H
#define Logger_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define Logger_DLL_IMPORT __declspec(dllimport)
  #define Logger_DLL_EXPORT __declspec(dllexport)
  #define Logger_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define Logger_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define Logger_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define Logger_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define Logger_DLL_IMPORT
    #define Logger_DLL_EXPORT
    #define Logger_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef Logger_BUILT_AS_STATIC
  #define Logger_EXPORT
  #define LOGGER_NO_EXPORT
#else /* NOT Logger_BUILT_AS_STATIC */
  #ifndef Logger_EXPORT
    #ifdef Logger_EXPORTS
/* We are building this library */
      #define Logger_EXPORT Logger_DLL_EXPORT
    #else
/* We are using this library */
      #define Logger_EXPORT Logger_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define Logger_LOCAL Logger_DLL_LOCAL_VISIBILITY

  #ifndef LOGGER_NO_EXPORT
    #define LOGGER_NO_EXPORT
  #endif
#endif /* Logger_BUILT_AS_STATIC */

#ifndef LOGGER_DEPRECATED
  #define LOGGER_DEPRECATED __declspec(deprecated)
#endif

#ifndef LOGGER_DEPRECATED_EXPORT
  #define LOGGER_DEPRECATED_EXPORT Logger_EXPORT LOGGER_DEPRECATED
#endif

#ifndef LOGGER_DEPRECATED_NO_EXPORT
  #define LOGGER_DEPRECATED_NO_EXPORT LOGGER_NO_EXPORT LOGGER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef LOGGER_NO_DEPRECATED
    #define LOGGER_NO_DEPRECATED
  #endif
#endif

#endif
