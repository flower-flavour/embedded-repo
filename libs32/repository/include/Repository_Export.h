#ifndef Repository_EXPORT_H
#define Repository_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define Repository_DLL_IMPORT __declspec(dllimport)
  #define Repository_DLL_EXPORT __declspec(dllexport)
  #define Repository_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define Repository_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define Repository_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define Repository_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define Repository_DLL_IMPORT
    #define Repository_DLL_EXPORT
    #define Repository_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef Repository_BUILT_AS_STATIC
  #define Repository_EXPORT
  #define REPOSITORY_NO_EXPORT
#else /* NOT Repository_BUILT_AS_STATIC */
  #ifndef Repository_EXPORT
    #ifdef Repository_EXPORTS
/* We are building this library */
      #define Repository_EXPORT Repository_DLL_EXPORT
    #else
/* We are using this library */
      #define Repository_EXPORT Repository_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define Repository_LOCAL Repository_DLL_LOCAL_VISIBILITY

  #ifndef REPOSITORY_NO_EXPORT
    #define REPOSITORY_NO_EXPORT
  #endif
#endif /* Repository_BUILT_AS_STATIC */

#ifndef REPOSITORY_DEPRECATED
  #define REPOSITORY_DEPRECATED __declspec(deprecated)
#endif

#ifndef REPOSITORY_DEPRECATED_EXPORT
  #define REPOSITORY_DEPRECATED_EXPORT Repository_EXPORT REPOSITORY_DEPRECATED
#endif

#ifndef REPOSITORY_DEPRECATED_NO_EXPORT
  #define REPOSITORY_DEPRECATED_NO_EXPORT REPOSITORY_NO_EXPORT REPOSITORY_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef REPOSITORY_NO_DEPRECATED
    #define REPOSITORY_NO_DEPRECATED
  #endif
#endif

#endif //Repository_EXPORT_H
