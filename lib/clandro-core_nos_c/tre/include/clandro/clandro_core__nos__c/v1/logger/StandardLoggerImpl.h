#ifndef LIBCLANDRO_CORE__NOS__C__STANDARD_LOGGER_IMPL___H
#define LIBCLANDRO_CORE__NOS__C__STANDARD_LOGGER_IMPL___H

#include <stdbool.h>

#include <clandro/clandro_core__nos__c/v1/logger/Logger.h>

#ifdef __cplusplus
extern "C" {
#endif



extern const struct ILogger sStandardLoggerImpl;

void printMessageToStdStream(bool logOnStderr, const char* message);



#ifdef __cplusplus
}
#endif

#endif // LIBCLANDRO_CORE__NOS__C__STANDARD_LOGGER_IMPL___H
