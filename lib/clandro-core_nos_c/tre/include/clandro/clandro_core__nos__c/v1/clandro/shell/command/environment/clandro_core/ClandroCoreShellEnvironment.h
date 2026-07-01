#ifndef LIBCLANDRO_CORE__NOS__C__CLANDRO_CORE_SHELL_ENVIRONMENT___H
#define LIBCLANDRO_CORE__NOS__C__CLANDRO_CORE_SHELL_ENVIRONMENT___H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif



/*
 * Environment for `clandro-core-tests`.
 */

/**
 * Environment variable for the log level for `clandro-core-tests`.
 *
 * Type: `int`
 * Default key: `CLANDRO_CORE__TESTS__LOG_LEVEL`
 * Default value: DEFAULT_LOG_LEVEL
 * Values:
 * - `0` (`OFF`) - Log nothing.
 * - `1` (`NORMAL`) - Log error, warn and info messages and stacktraces.
 * - `2` (`DEBUG`) - Log debug messages.
 * - `3` (`VERBOSE`) - Log verbose messages.
 * - `4` (`VVERBOSE`) - Log very verbose messages.
 */
#define ENV__CLANDRO_CORE__TESTS__LOG_LEVEL CLANDRO_ENV__S_CLANDRO_CORE__TESTS "LOG_LEVEL"



/**
 * Environment variable for the path to the clandro-core tests.
 */
#define ENV__CLANDRO_CORE__TESTS__TESTS_PATH CLANDRO_ENV__S_CLANDRO_CORE__TESTS "TESTS_PATH"





/**
 * Returns the `clandro-core-tests` config for `Logger` log level
 * based on the `ENV__CLANDRO_CORE__TESTS__LOG_LEVEL` env variable.
 *
 * @return Return the value if `ENV__CLANDRO_CORE__TESTS__LOG_LEVEL` is
 * set, otherwise defaults to `DEFAULT_LOG_LEVEL`.
 */
int clandroCore_tests_logLevel_get();



#ifdef __cplusplus
}
#endif

#endif // LIBCLANDRO_CORE__NOS__C__CLANDRO_CORE_SHELL_ENVIRONMENT___H
