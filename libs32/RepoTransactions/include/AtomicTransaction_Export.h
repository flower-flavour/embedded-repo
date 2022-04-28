#ifndef AtomicTransaction_EXPORT_H
#define AtomicTransaction_EXPORT_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
  #define AtomicTransaction_DLL_IMPORT __declspec(dllimport)
  #define AtomicTransaction_DLL_EXPORT __declspec(dllexport)
  #define AtomicTransaction_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define AtomicTransaction_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define AtomicTransaction_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define AtomicTransaction_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define AtomicTransaction_DLL_IMPORT
    #define AtomicTransaction_DLL_EXPORT
    #define AtomicTransaction_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef AtomicTransaction_BUILT_AS_STATIC
  #define AtomicTransaction_EXPORT
  #define AtomicTransaction_NO_EXPORT
#else /* NOT AtomicTransaction_BUILT_AS_STATIC */
  #ifndef AtomicTransaction_EXPORT
    #ifdef AtomicTransaction_EXPORTS
/* We are building this library */
      #define AtomicTransaction_EXPORT AtomicTransaction_DLL_EXPORT
    #else
/* We are using this library */
      #define AtomicTransaction_EXPORT AtomicTransaction_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define AtomicTransaction_LOCAL AtomicTransaction_DLL_LOCAL_VISIBILITY

  #ifndef AtomicTransaction_NO_EXPORT
    #define AtomicTransaction_NO_EXPORT
  #endif
#endif /* AtomicTransaction_BUILT_AS_STATIC */

#ifndef AtomicTransaction_DEPRECATED
  #define AtomicTransaction_DEPRECATED __declspec(deprecated)
#endif

#ifndef AtomicTransaction_DEPRECATED_EXPORT
  #define AtomicTransaction_DEPRECATED_EXPORT AtomicTransaction_EXPORT AtomicTransaction_DEPRECATED
#endif

#ifndef AtomicTransaction_DEPRECATED_NO_EXPORT
  #define AtomicTransaction_DEPRECATED_NO_EXPORT AtomicTransaction_NO_EXPORT AtomicTransaction_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef AtomicTransaction_NO_DEPRECATED
    #define AtomicTransaction_NO_DEPRECATED
  #endif
#endif

#endif //AtomicTransaction_EXPORT_H
