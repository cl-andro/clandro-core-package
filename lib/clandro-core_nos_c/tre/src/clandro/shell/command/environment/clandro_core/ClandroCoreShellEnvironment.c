#define _GNU_SOURCE
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <clandro/clandro_core__nos__c/v1/logger/Logger.h>
#include <clandro/clandro_core__nos__c/v1/clandro/shell/command/environment/ClandroShellEnvironment.h>
#include <clandro/clandro_core__nos__c/v1/clandro/shell/command/environment/clandro_core/ClandroCoreShellEnvironment.h>
#include <clandro/clandro_core__nos__c/v1/unix/shell/command/environment/UnixShellEnvironment.h>



int clandroCore_tests_logLevel_get() {
    return getLogLevelFromEnv(ENV__CLANDRO_CORE__TESTS__LOG_LEVEL);
}
