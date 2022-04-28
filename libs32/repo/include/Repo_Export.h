#ifndef Repo_EXPORT_H
#define Repo_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define Repo_DLL_IMPORT __declspec(dllimport)
  #define Repo_DLL_EXPORT __declspec(dllexport)
  #define Repo_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define Repo_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define Repo_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define Repo_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define Repo_DLL_IMPORT
    #define Repo_DLL_EXPORT
    #define Repo_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef Repo_BUILT_AS_STATIC
  #define Repo_EXPORT
  #define REPO_NO_EXPORT
#else /* NOT Repo_BUILT_AS_STATIC */
  #ifndef Repo_EXPORT
    #ifdef Repo_EXPORTS
/* We are building this library */
      #define Repo_EXPORT Repo_DLL_EXPORT
    #else
/* We are using this library */
      #define Repo_EXPORT Repo_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define Repo_LOCAL Repo_DLL_LOCAL_VISIBILITY

  #ifndef REPO_NO_EXPORT
    #define REPO_NO_EXPORT
  #endif
#endif /* Repo_BUILT_AS_STATIC */

#ifndef REPO_DEPRECATED
  #define REPO_DEPRECATED __declspec(deprecated)
#endif

#ifndef REPO_DEPRECATED_EXPORT
  #define REPO_DEPRECATED_EXPORT Repo_EXPORT REPO_DEPRECATED
#endif

#ifndef REPO_DEPRECATED_NO_EXPORT
  #define REPO_DEPRECATED_NO_EXPORT REPO_NO_EXPORT REPO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef REPO_NO_DEPRECATED
    #define REPO_NO_DEPRECATED
  #endif
#endif

#endif
