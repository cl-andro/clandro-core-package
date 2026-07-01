#ifndef LIBCLANDRO_CORE__NOS__C__CLANDRO_CORE_LIBRARY_CONFIG___H
#define LIBCLANDRO_CORE__NOS__C__CLANDRO_CORE_LIBRARY_CONFIG___H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif



/** Get `sIsRunningTests`. */
bool libclandro_core__nos__c__getIsRunningTests();

/** Set `sIsRunningTests`. */
void libclandro_core__nos__c__setIsRunningTests(bool isRunningTests);



#ifdef __cplusplus
}
#endif

#endif // LIBCLANDRO_CORE__NOS__C__CLANDRO_CORE_LIBRARY_CONFIG___H
