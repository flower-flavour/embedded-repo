#ifndef RepoCacheLogic_EXPORT_H
#define RepoCacheLogic_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define RepoCacheLogic_DLL_IMPORT __declspec(dllimport)
  #define RepoCacheLogic_DLL_EXPORT __declspec(dllexport)
  #define RepoCacheLogic_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define RepoCacheLogic_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define RepoCacheLogic_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define RepoCacheLogic_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define RepoCacheLogic_DLL_IMPORT
    #define RepoCacheLogic_DLL_EXPORT
    #define RepoCacheLogic_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef RepoCacheLogic_BUILT_AS_STATIC
  #define RepoCacheLogic_EXPORT
  #define RepoCacheLogic_NO_EXPORT
#else /* NOT RepoCacheLogic_BUILT_AS_STATIC */
  #ifndef RepoCacheLogic_EXPORT
    #ifdef RepoCacheLogic_EXPORTS
/* We are building this library */
      #define RepoCacheLogic_EXPORT RepoCacheLogic_DLL_EXPORT
    #else
/* We are using this library */
      #define RepoCacheLogic_EXPORT RepoCacheLogic_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define RepoCacheLogic_LOCAL RepoCacheLogic_DLL_LOCAL_VISIBILITY

  #ifndef RepoCacheLogic_NO_EXPORT
    #define RepoCacheLogic_NO_EXPORT
  #endif
#endif /* RepoCacheLogic_BUILT_AS_STATIC */

#ifndef RepoCacheLogic_DEPRECATED
  #define RepoCacheLogic_DEPRECATED __declspec(deprecated)
#endif

#ifndef RepoCacheLogic_DEPRECATED_EXPORT
  #define RepoCacheLogic_DEPRECATED_EXPORT RepoCacheLogic_EXPORT RepoCacheLogic_DEPRECATED
#endif

#ifndef RepoCacheLogic_DEPRECATED_NO_EXPORT
  #define RepoCacheLogic_DEPRECATED_NO_EXPORT RepoCacheLogic_NO_EXPORT RepoCacheLogic_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef RepoCacheLogic_NO_DEPRECATED
    #define RepoCacheLogic_NO_DEPRECATED
  #endif
#endif

#endif //RepoCacheLogic_EXPORT_H
