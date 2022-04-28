#ifndef ConfigParser_EXPORT_H
#define ConfigParser_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define ConfigParser_DLL_IMPORT __declspec(dllimport)
  #define ConfigParser_DLL_EXPORT __declspec(dllexport)
  #define ConfigParser_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define ConfigParser_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define ConfigParser_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define ConfigParser_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define ConfigParser_DLL_IMPORT
    #define ConfigParser_DLL_EXPORT
    #define ConfigParser_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef ConfigParser_BUILT_AS_STATIC
  #define ConfigParser_EXPORT
  #define ConfigParser_NO_EXPORT
#else /* NOT ConfigParser_BUILT_AS_STATIC */
  #ifndef ConfigParser_EXPORT
    #ifdef ConfigParser_EXPORTS
/* We are building this library */
      #define ConfigParser_EXPORT ConfigParser_DLL_EXPORT
    #else
/* We are using this library */
      #define ConfigParser_EXPORT ConfigParser_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define ConfigParser_LOCAL ConfigParser_DLL_LOCAL_VISIBILITY

  #ifndef ConfigParser_NO_EXPORT
    #define ConfigParser_NO_EXPORT
  #endif
#endif /* ConfigParser_BUILT_AS_STATIC */

#ifndef ConfigParser_DEPRECATED
  #define ConfigParser_DEPRECATED __declspec(deprecated)
#endif

#ifndef ConfigParser_DEPRECATED_EXPORT
  #define ConfigParser_DEPRECATED_EXPORT ConfigParser_EXPORT ConfigParser_DEPRECATED
#endif

#ifndef ConfigParser_DEPRECATED_NO_EXPORT
  #define ConfigParser_DEPRECATED_NO_EXPORT ConfigParser_NO_EXPORT ConfigParser_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef ConfigParser_NO_DEPRECATED
    #define ConfigParser_NO_DEPRECATED
  #endif
#endif

#endif
