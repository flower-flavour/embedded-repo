#ifndef RepoPersistentStorage_EXPORT_H
#define RepoPersistentStorage_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define RepoPersistentStorage_DLL_IMPORT __declspec(dllimport)
  #define RepoPersistentStorage_DLL_EXPORT __declspec(dllexport)
  #define RepoPersistentStorage_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define RepoPersistentStorage_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define RepoPersistentStorage_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define RepoPersistentStorage_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define RepoPersistentStorage_DLL_IMPORT
    #define RepoPersistentStorage_DLL_EXPORT
    #define RepoPersistentStorage_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef RepoPersistentStorage_BUILT_AS_STATIC
  #define RepoPersistentStorage_EXPORT
  #define RepoPersistentStorage_NO_EXPORT
#else /* NOT RepoPersistentStorage_BUILT_AS_STATIC */
  #ifndef RepoPersistentStorage_EXPORT
    #ifdef RepoPersistentStorage_EXPORTS
/* We are building this library */
      #define RepoPersistentStorage_EXPORT RepoPersistentStorage_DLL_EXPORT
    #else
/* We are using this library */
      #define RepoPersistentStorage_EXPORT RepoPersistentStorage_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define RepoPersistentStorage_LOCAL RepoPersistentStorage_DLL_LOCAL_VISIBILITY

  #ifndef RepoPersistentStorage_NO_EXPORT
    #define RepoPersistentStorage_NO_EXPORT
  #endif
#endif /* RepoPersistentStorage_BUILT_AS_STATIC */

#ifndef RepoPersistentStorage_DEPRECATED
  #define RepoPersistentStorage_DEPRECATED __declspec(deprecated)
#endif

#ifndef RepoPersistentStorage_DEPRECATED_EXPORT
  #define RepoPersistentStorage_DEPRECATED_EXPORT RepoPersistentStorage_EXPORT RepoPersistentStorage_DEPRECATED
#endif

#ifndef RepoPersistentStorage_DEPRECATED_NO_EXPORT
  #define RepoPersistentStorage_DEPRECATED_NO_EXPORT RepoPersistentStorage_NO_EXPORT RepoPersistentStorage_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef RepoPersistentStorage_NO_DEPRECATED
    #define RepoPersistentStorage_NO_DEPRECATED
  #endif
#endif

#endif //RepoPersistentStorage_EXPORT_H
