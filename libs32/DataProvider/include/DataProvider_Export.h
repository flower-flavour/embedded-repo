#ifndef DataProvider_EXPORT_H
#define DataProvider_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define DataProvider_DLL_IMPORT __declspec(dllimport)
  #define DataProvider_DLL_EXPORT __declspec(dllexport)
  #define DataProvider_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define DataProvider_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define DataProvider_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define DataProvider_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define DataProvider_DLL_IMPORT
    #define DataProvider_DLL_EXPORT
    #define DataProvider_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef DataProvider_BUILT_AS_STATIC
  #define DataProvider_EXPORT
  #define DATAPROVIDER_NO_EXPORT
#else /* NOT DataProvider_BUILT_AS_STATIC */
  #ifndef DataProvider_EXPORT
    #ifdef DataProvider_EXPORTS
/* We are building this library */
      #define DataProvider_EXPORT DataProvider_DLL_EXPORT
    #else
/* We are using this library */
      #define DataProvider_EXPORT DataProvider_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define DataProvider_LOCAL DataProvider_DLL_LOCAL_VISIBILITY

  #ifndef DATAPROVIDER_NO_EXPORT
    #define DATAPROVIDER_NO_EXPORT
  #endif
#endif /* DataProvider_BUILT_AS_STATIC */

#ifndef DATAPROVIDER_DEPRECATED
  #define DATAPROVIDER_DEPRECATED __declspec(deprecated)
#endif

#ifndef DATAPROVIDER_DEPRECATED_EXPORT
  #define DATAPROVIDER_DEPRECATED_EXPORT DataProvider_EXPORT DATAPROVIDER_DEPRECATED
#endif

#ifndef DATAPROVIDER_DEPRECATED_NO_EXPORT
  #define DATAPROVIDER_DEPRECATED_NO_EXPORT DATAPROVIDER_NO_EXPORT DATAPROVIDER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef DATAPROVIDER_NO_DEPRECATED
    #define DATAPROVIDER_NO_DEPRECATED
  #endif
#endif

#endif
