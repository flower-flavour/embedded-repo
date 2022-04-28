#ifndef RepoDirectory_EXPORT_H
#define RepoDirectory_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define RepoDirectory_DLL_IMPORT __declspec(dllimport)
  #define RepoDirectory_DLL_EXPORT __declspec(dllexport)
  #define RepoDirectory_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define RepoDirectory_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define RepoDirectory_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define RepoDirectory_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define RepoDirectory_DLL_IMPORT
    #define RepoDirectory_DLL_EXPORT
    #define RepoDirectory_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef RepoDirectory_BUILT_AS_STATIC
  #define RepoDirectory_EXPORT
  #define RepoDirectory_NO_EXPORT
#else /* NOT RepoDirectory_BUILT_AS_STATIC */
  #ifndef RepoDirectory_EXPORT
    #ifdef RepoDirectory_EXPORTS
/* We are building this library */
      #define RepoDirectory_EXPORT RepoDirectory_DLL_EXPORT
    #else
/* We are using this library */
      #define RepoDirectory_EXPORT RepoDirectory_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define RepoDirectory_LOCAL RepoDirectory_DLL_LOCAL_VISIBILITY

  #ifndef RepoDirectory_NO_EXPORT
    #define RepoDirectory_NO_EXPORT
  #endif
#endif /* RepoDirectory_BUILT_AS_STATIC */

#ifndef RepoDirectory_DEPRECATED
  #define RepoDirectory_DEPRECATED __declspec(deprecated)
#endif

#ifndef RepoDirectory_DEPRECATED_EXPORT
  #define RepoDirectory_DEPRECATED_EXPORT RepoDirectory_EXPORT RepoDirectory_DEPRECATED
#endif

#ifndef RepoDirectory_DEPRECATED_NO_EXPORT
  #define RepoDirectory_DEPRECATED_NO_EXPORT RepoDirectory_NO_EXPORT RepoDirectory_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef RepoDirectory_NO_DEPRECATED
    #define RepoDirectory_NO_DEPRECATED
  #endif
#endif

#endif //RepoDirectory_EXPORT_H
