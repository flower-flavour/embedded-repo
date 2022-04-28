#ifndef RepoCache_EXPORT_H
#define RepoCache_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define RepoCache_DLL_IMPORT __declspec(dllimport)
  #define RepoCache_DLL_EXPORT __declspec(dllexport)
  #define RepoCache_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define RepoCache_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define RepoCache_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define RepoCache_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define RepoCache_DLL_IMPORT
    #define RepoCache_DLL_EXPORT
    #define RepoCache_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef RepoCache_BUILT_AS_STATIC
  #define RepoCache_EXPORT
  #define RepoCache_NO_EXPORT
#else /* NOT RepoCache_BUILT_AS_STATIC */
  #ifndef RepoCache_EXPORT
    #ifdef RepoCache_EXPORTS
/* We are building this library */
      #define RepoCache_EXPORT RepoCache_DLL_EXPORT
    #else
/* We are using this library */
      #define RepoCache_EXPORT RepoCache_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define RepoCache_LOCAL RepoCache_DLL_LOCAL_VISIBILITY

  #ifndef RepoCache_NO_EXPORT
    #define RepoCache_NO_EXPORT
  #endif
#endif /* RepoCache_BUILT_AS_STATIC */

#ifndef RepoCache_DEPRECATED
  #define RepoCache_DEPRECATED __declspec(deprecated)
#endif

#ifndef RepoCache_DEPRECATED_EXPORT
  #define RepoCache_DEPRECATED_EXPORT RepoCache_EXPORT RepoCache_DEPRECATED
#endif

#ifndef RepoCache_DEPRECATED_NO_EXPORT
  #define RepoCache_DEPRECATED_NO_EXPORT RepoCache_NO_EXPORT RepoCache_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef RepoCache_NO_DEPRECATED
    #define RepoCache_NO_DEPRECATED
  #endif
#endif

#endif //RepoCache_EXPORT_H
