#include <stdbool.h>

#include <clandro/clandro_core__nos__cxx/v1/ClandroCoreLibraryConfig.h>

static bool sIsRunningTests = false;



bool libclandro_core__nos__cxx__getIsRunningTests() {
    return sIsRunningTests;
}

void libclandro_core__nos__cxx__setIsRunningTests(bool isRunningTests) {
    sIsRunningTests = isRunningTests;
}
