#ifndef __LOG_H__633569422542968750
#define __LOG_H__633569422542968750

#include <string>

#include "Logger_Export.h"

class Logger_EXPORT Logger
{
public:
    enum CriticalErrorLevels {
        WORKFLOW_TASKMANAGER_CRITICAL_ERROR,
        WORKFLOW_TASK_CRITICAL_ERROR,
        ALGORITHM_MODELDATA_CRITICAL_ERROR,
        ALGORITHM_ESTIMATOR_CRITICAL_ERROR,
        FAKE_CRITICAL_ERROR,
    };

    constexpr static char const * const CriticalErrorMessages[FAKE_CRITICAL_ERROR] = {
        "WORKFLOW_TASKMANAGER_CRITICAL_ERROR",
        "WORKFLOW_TASK_CRITICAL_ERROR",
        "ALGORITHM_MODELDATA_CRITICAL_ERROR",
        "ALGORITHM_ESTIMATOR_CRITICAL_ERROR"
    };

    enum ErrorLevels {
        WORKFLOW_TASKMANAGER_ERROR,
        WORKFLOW_TASK_ERROR,
        ALGORITHM_MODELDATA_ERROR,
        ALGORITHM_ESTIMATOR_ERROR,
        FAKE_ERROR
    };

    constexpr static char const * const ErrorMessages[FAKE_ERROR] = {
        "WORKFLOW_TASKMANAGER_ERROR",
        "WORKFLOW_TASK_ERROR",
        "ALGORITHM_MODELDATA_ERROR",
        "ALGORITHM_ESTIMATOR_ERROR"
    };

    enum WarningLevels {
        WORKFLOW_TASKMANAGER_WARNING,
        WORKFLOW_TASK_WARNING,
        ALGORITHM_MODELDATA_WARNING,
        ALGORITHM_ESTIMATOR_WARNING,
        FAKE_WARNING
    };

    constexpr static char const * const WarningMessages[FAKE_WARNING] = {
        "WORKFLOW_TASKMANAGER_WARNING",
        "WORKFLOW_TASK_WARNING",
        "ALGORITHM_MODELDATA_WARNING",
        "ALGORITHM_ESTIMATOR_WARNING",
    };

    enum LogLevels {
        WORKFLOW_TASKMANAGER_NOTIFICATION,
        WORKFLOW_TASK_NOTIFICATION,
        ALGORITHM_MODELDATA_NOTIFICATION,
        ALGORITHM_ESTIMATOR_NOTIFICATION,
        ALGORITHM_GENERAL_INFO,
        ALGORITHM_1_LEVEL_INFO,
        ALGORITHM_2_LEVEL_INFO,
        ALGORITHM_3_LEVEL_INFO,
        ALGORITHM_4_LEVEL_INFO,
        ALGORITHM_5_LEVEL_INFO,
        ALGORITHM_6_LEVEL_INFO,
        ALGORITHM_7_LEVEL_INFO,
        FAKE_LOG_LEVEL
    };
    constexpr static char const * const LogMessages[FAKE_LOG_LEVEL] = {
        "WORKFLOW_TASKMANAGER_NOTIFICATION",
        "WORKFLOW_TASK_NOTIFICATION",
        "ALGORITHM_MODELDATA_NOTIFICATION",
        "ALGORITHM_ESTIMATOR_NOTIFICATION",
        "ALGORITHM_GENERAL_INFO",
        "ALGORITHM_1_LEVEL_INFO",
        "ALGORITHM_2_LEVEL_INFO",
        "ALGORITHM_3_LEVEL_INFO",
        "ALGORITHM_4_LEVEL_INFO",
        "ALGORITHM_5_LEVEL_INFO",
        "ALGORITHM_6_LEVEL_INFO",
        "ALGORITHM_7_LEVEL_INFO"
    };


    static Logger * createLogger();

    explicit Logger() = default;
    virtual ~Logger() = default;
    Logger(const Logger &) = delete;
    Logger & operator=(const Logger &) = delete;

    virtual bool setLogFile(std::string const & fileName) = 0;
    virtual bool setLogLevel(int level) = 0;

    virtual void log(enum LogLevels level, std::string const & message) = 0;
    virtual void warning(enum WarningLevels warning, std::string const & message) = 0;

    virtual void error(enum ErrorLevels error, std::string const & message) = 0;
    virtual void criticalError(enum CriticalErrorLevels errorLevel, std::string const & message) = 0;
    virtual void finish() = 0;

    virtual void startTimer() = 0;
    virtual void stopTimer() = 0;

};
#endif
