
#ifndef DataSetHelper_EXPORT_H
#define DataSetHelper_EXPORT_H

#ifdef DataSetHelper_BUILT_AS_STATIC
  #define DataSetHelper_EXPORT
  #define DATASETHELPER_NO_EXPORT
#else /* NOT DataSetHelper_BUILT_AS_STATIC */
  #ifndef DataSetHelper_EXPORT
    #ifdef DataSetHelper_EXPORTS
/* We are building this library */
      #define DataSetHelper_EXPORT __declspec(dllexport)
    #else
/* We are using this library */
      #define DataSetHelper_EXPORT __declspec(dllimport)
    #endif
  #endif

  #ifndef DATASETHELPER_NO_EXPORT
    #define DATASETHELPER_NO_EXPORT
  #endif
#endif /* DataSetHelper_BUILT_AS_STATIC */

#ifndef DATASETHELPER_DEPRECATED
  #define DATASETHELPER_DEPRECATED __declspec(deprecated)
#endif

#ifndef DATASETHELPER_DEPRECATED_EXPORT
  #define DATASETHELPER_DEPRECATED_EXPORT DataSetHelper_EXPORT DATASETHELPER_DEPRECATED
#endif

#ifndef DATASETHELPER_DEPRECATED_NO_EXPORT
  #define DATASETHELPER_DEPRECATED_NO_EXPORT DATASETHELPER_NO_EXPORT DATASETHELPER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
  #ifndef DATASETHELPER_NO_DEPRECATED
    #define DATASETHELPER_NO_DEPRECATED
  #endif
#endif

#endif
