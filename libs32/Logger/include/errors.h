#ifndef _ERRORS_H_1234567890
#define _ERRORS_H_1234567890

#define _RC_SUCCESS_ 0
/*** ERRORs AND WARNINGs SECTION! *****/

#define _ERROR_NO_ROOM_ -1
#define _ERROR_OUT_OF_ARRAY_BOUNDARY_ -2
#define _ERROR_NO_ARGUMENT_ -3
#define _ERROR_WRONG_ARGUMENT_ -4

#define _ERROR_NO_INPUT_DATA_ -5
#define _ERROR_WRONG_INPUT_DATA_ -6
#define _ERROR_WRONG_OUTPUT_DATA_ -7

#define _ERROR_NO_MODEL_ -8
#define _ERROR_NO_MODEL_PARAMS_ -9
#define _ERROR_WRONG_MODEL_PARAMS_ -10

#define _ERROR_NO_ESTIMATOR_ -11
#define _ERROR_NO_ESTIMATOR_PARAMS_ -12
#define _ERROR_WRONG_ESTIMATOR_PARAMS_ -13
#define _ERROR_ESTIMATES_NOT_FOUND_ -14

#define _ERROR_WRONG_WORKFLOW_ -15

/** this macro MUST BE the VERY LAST
    because other module's error codes are evaluated as
    _ERROR_FAKE_UNSPECIFIED_ - positive_decrement
*/
#define _ERROR_FAKE_UNSPECIFIED_ -16

/*** END of ERRORs AND WARNINGs SECTION! *****/

#define VERIFY_ANSWER(ANSWER, ERROR) \
    if (ANSWER != _RC_SUCCESS_) {    \
        return ERROR;                \
    }

#define VERIFY_NOT_NULL(ANSWER, ERROR) \
    if (!ANSWER) {                     \
        return ERROR;                  \
    }

#define _ERROR_STORAGE_ -100
#define _ERROR_KEY_NOT_FOUND_IN_CACHE_ -101
#define _ERROR_KEY_NOT_FOUND_IN_STORAGE_ -102
#define _ERROR_ELEMENT_IS_TOO_BIG_ -103
#define _ERROR_ELEMENT_IS_TOO_BIG_AND_HAS_BEEN_MOVED_TO_DISK_  -104
#define _ERROR_UNSUPPORTED_OS_ - 105
#define _ERROR_KEY_NOT_FOUND_IN_REPO_CACHE_LOGIC_ -106
#define _ERROR_LOCKED_DS_IN_REPO_CACHE_ -107
#define _ERROR_RCL_CAN_NOT_FREE_ENOUGH_ROOM_IN_CACHE_ -108

#endif
