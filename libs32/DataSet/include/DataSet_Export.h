#ifndef DataSet_EXPORT_H
#define DataSet_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define DataSet_DLL_IMPORT __declspec(dllimport)
  #define DataSet_DLL_EXPORT __declspec(dllexport)
  #define DataSet_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define DataSet_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define DataSet_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define DataSet_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define DataSet_DLL_IMPORT
    #define DataSet_DLL_EXPORT
    #define DataSet_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef DataSet_BUILT_AS_STATIC
  #define DataSet_EXPORT
  #define DATASET_NO_EXPORT
#else /* NOT DataSet_BUILT_AS_STATIC */
  #ifndef DataSet_EXPORT
    #ifdef DataSet_EXPORTS
/* We are building this library */
      #define DataSet_EXPORT DataSet_DLL_EXPORT
    #else
/* We are using this library */
      #define DataSet_EXPORT DataSet_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define DataSet_LOCAL DataSet_DLL_LOCAL_VISIBILITY

  #ifndef DATASET_NO_EXPORT
    #define DATASET_NO_EXPORT
  #endif
#endif /* DataSet_BUILT_AS_STATIC */

#ifndef DATASET_DEPRECATED
  #define DATASET_DEPRECATED __declspec(deprecated)
#endif

#ifndef DATASET_DEPRECATED_EXPORT
  #define DATASET_DEPRECATED_EXPORT DataSet_EXPORT DATASET_DEPRECATED
#endif

#ifndef DATASET_DEPRECATED_NO_EXPORT
  #define DATASET_DEPRECATED_NO_EXPORT DATASET_NO_EXPORT DATASET_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef DATASET_NO_DEPRECATED
    #define DATASET_NO_DEPRECATED
  #endif
#endif

#endif
