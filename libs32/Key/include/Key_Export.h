#ifndef Key_EXPORT_H
#define Key_EXPORT_H

// Generic helper definitions for shared library support
#if defined (_WIN32) || defined(WIN32) || defined (_WIN64) || defined (WIN64) || defined __CYGWIN__
  #define Key_DLL_IMPORT __declspec(dllimport)
  #define Key_DLL_EXPORT __declspec(dllexport)
  #define Key_DLL_LOCAL_VISIBILITY
#else
  #if __GNUC__ >= 4
    #define Key_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define Key_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define Key_DLL_LOCAL_VISIBILITY  __attribute__ ((visibility ("hidden")))
  #else
    #define Key_DLL_IMPORT
    #define Key_DLL_EXPORT
    #define Key_DLL_LOCAL_VISIBILITY
  #endif
#endif


#ifdef Key_BUILT_AS_STATIC
  #define Key_EXPORT
  #define Key_NO_EXPORT
#else /* NOT Key_BUILT_AS_STATIC */
  #ifndef Key_EXPORT
    #ifdef Key_EXPORTS
/* We are building this library */
      #define Key_EXPORT Key_DLL_EXPORT
    #else
/* We are using this library */
      #define Key_EXPORT Key_DLL_IMPORT
    #endif
  #endif
/* We hide code for library scope only */
  #define Key_LOCAL Key_DLL_LOCAL_VISIBILITY

  #ifndef Key_NO_EXPORT
    #define Key_NO_EXPORT
  #endif
#endif /* Key_BUILT_AS_STATIC */

#ifndef Key_DEPRECATED
  #define Key_DEPRECATED __declspec(deprecated)
#endif

#ifndef Key_DEPRECATED_EXPORT
  #define Key_DEPRECATED_EXPORT Key_EXPORT Key_DEPRECATED
#endif

#ifndef Key_DEPRECATED_NO_EXPORT
  #define Key_DEPRECATED_NO_EXPORT Key_NO_EXPORT Key_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef Key_NO_DEPRECATED
    #define Key_NO_DEPRECATED
  #endif
#endif

#endif //Key_EXPORT_H
