#ifndef PlanTransactions_EXPORT_H
#define PlanTransactions_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define PlanTransactions_DLL_IMPORT __declspec(dllimport)
  #define PlanTransactions_DLL_EXPORT __declspec(dllexport)
  #define PlanTransactions_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define PlanTransactions_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define PlanTransactions_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define PlanTransactions_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define PlanTransactions_DLL_IMPORT
    #define PlanTransactions_DLL_EXPORT
    #define PlanTransactions_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef PlanTransactions_BUILT_AS_STATIC
  #define PlanTransactions_EXPORT
  #define PlanTransactions_NO_EXPORT
#else /* NOT PlanTransactions_BUILT_AS_STATIC */
  #ifndef PlanTransactions_EXPORT
    #ifdef PlanTransactions_EXPORTS
/* We are building this library */
      #define PlanTransactions_EXPORT PlanTransactions_DLL_EXPORT
    #else
/* We are using this library */
      #define PlanTransactions_EXPORT PlanTransactions_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define PlanTransactions_LOCAL PlanTransactions_DLL_LOCAL_VISIBILITY

  #ifndef PlanTransactions_NO_EXPORT
    #define PlanTransactions_NO_EXPORT
  #endif
#endif /* PlanTransactions_BUILT_AS_STATIC */

#ifndef PlanTransactions_DEPRECATED
  #define PlanTransactions_DEPRECATED __declspec(deprecated)
#endif

#ifndef PlanTransactions_DEPRECATED_EXPORT
  #define PlanTransactions_DEPRECATED_EXPORT PlanTransactions_EXPORT PlanTransactions_DEPRECATED
#endif

#ifndef PlanTransactions_DEPRECATED_NO_EXPORT
  #define PlanTransactions_DEPRECATED_NO_EXPORT PlanTransactions_NO_EXPORT PlanTransactions_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef PlanTransactions_NO_DEPRECATED
    #define PlanTransactions_NO_DEPRECATED
  #endif
#endif

#endif //PlanTransactions_EXPORT_H
