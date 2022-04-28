#ifndef _LOGGER_CLOSURE_H_
#define _LOGGER_CLOSURE_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef int (*ptr_callback_logger_t)(void * ptr_logger, char const * ptr_err_msg, int err_code);

typedef struct tag_logger_closure{
  ptr_callback_logger_t callback_logger;
  void * ptr_logger;
} logger_closure;

#ifdef __cplusplus
}
#endif

#endif // _LOGGER_CLOSURE_H_
