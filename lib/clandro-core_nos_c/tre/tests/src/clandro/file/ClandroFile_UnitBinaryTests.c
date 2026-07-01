#include <fcntl.h>
#include <limits.h>

#include <clandro/clandro_core__nos__c/v1/clandro/file/ClandroFile.h>
#include <clandro/clandro_core__nos__c/v1/clandro/shell/command/environment/ClandroShellEnvironment.h>
#include <clandro/clandro_core__nos__c/v1/unix/shell/command/environment/UnixShellEnvironment.h>



#define CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1 "/data/user/0/com.foo"
#define CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2 "/data/data/com.foo"

#define CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1 "/data/data/com.foo/foo/rootfs"
#define CLANDRO_CORE__TESTS__CLANDRO_PREFIX_DIR_1 CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1 "/usr"
#define CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_1 CLANDRO_CORE__TESTS__CLANDRO_PREFIX_DIR_1 "/bin"

#define CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2 "/"
#define CLANDRO_CORE__TESTS__CLANDRO_PREFIX_DIR_2 CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1 "/usr"
#define CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_2 CLANDRO_CORE__TESTS__CLANDRO_PREFIX_DIR_1 "/bin"



void test__clandroApp_dataDir_getFromEnv();
void test__clandro_prefixDir_getFromEnv();
void test__clandro_rootfsDir_getFromEnv();
void test__clandroApp_dataDir_convertToLegacyPath();
void test__clandroPrefixPath();
void test__clandroApp_dataDir_isPathUnder();
void test__clandro_rootfsDir_isPathUnder();



void ClandroFile_runTests() {
    logVerbose(LOG_TAG, "ClandroFile_runTests()");

    test__clandroApp_dataDir_getFromEnv();
    test__clandro_prefixDir_getFromEnv();
    test__clandro_rootfsDir_getFromEnv();
    test__clandroApp_dataDir_convertToLegacyPath();
    test__clandroPrefixPath();
    test__clandroApp_dataDir_isPathUnder();
    test__clandro_rootfsDir_isPathUnder();

    int__AEqual(0, errno);
}





void test__getClandroAppDataDirFromEnv__Basic();

void test__clandroApp_dataDir_getFromEnv() {
    logVerbose(LOG_TAG, "test__clandroApp_dataDir_getFromEnv()");

    test__getClandroAppDataDirFromEnv__Basic();

    int__AEqual(0, errno);
}

void test__getClandroAppDataDirFromEnv__Basic() {
    logVVerbose(LOG_TAG, "test__getClandroAppDataDirFromEnv__Basic()");

    size_t envVarLength = strlen(ENV__CLANDRO_APP__DATA_DIR) + 1;

    char buffer[CLANDRO_APP__DATA_DIR___MAX_LEN];
    size_t bufferSize = sizeof(buffer);

    int result;

    putenv(ENV__CLANDRO_APP__DATA_DIR "=" CLANDRO_APP__DATA_DIR);
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual(CLANDRO_APP__DATA_DIR, buffer);

    putenv(ENV__CLANDRO_APP__DATA_DIR "=/");
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual("/", buffer);

    putenv(ENV__CLANDRO_APP__DATA_DIR "=/a");
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual("/a", buffer);

    putenv(ENV__CLANDRO_APP__DATA_DIR "=a");
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    putenv(ENV__CLANDRO_APP__DATA_DIR "=a/");
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    putenv(ENV__CLANDRO_APP__DATA_DIR "=a" CLANDRO_APP__DATA_DIR);
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    unsetenv(ENV__CLANDRO_APP__DATA_DIR);
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    state__ATrue(PATH_MAX >= CLANDRO_APP__DATA_DIR___MAX_LEN);

    char rootfsDir1[envVarLength + PATH_MAX];
    snprintf(rootfsDir1, sizeof(rootfsDir1), "%s=/%0*d", ENV__CLANDRO_APP__DATA_DIR, CLANDRO_APP__DATA_DIR___MAX_LEN - 1, 0);

    putenv(rootfsDir1);
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    char rootfsDir2[envVarLength + PATH_MAX];
    size_t rootfsDir2Length = snprintf(rootfsDir2, sizeof(rootfsDir2), "%s=/%0*d", ENV__CLANDRO_APP__DATA_DIR, CLANDRO_APP__DATA_DIR___MAX_LEN - 2, 0);

    putenv(rootfsDir2);
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    state__ATrue(rootfsDir2Length - envVarLength == strlen(buffer));

    char buffer1[CLANDRO_APP__DATA_DIR___MAX_LEN - 1];
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer1, sizeof(buffer1));
    state__ATrue(result == -1);
    errno = 0;

    char buffer2[CLANDRO_APP__DATA_DIR___MAX_LEN - 2];
    result = clandroApp_dataDir_getFromEnv(LOG_TAG, buffer2, sizeof(buffer2));
    state__ATrue(result == -1);
    errno = 0;
}





void test__getClandroPrefixDirFromEnv__Basic();

void test__clandro_prefixDir_getFromEnv() {
    logVerbose(LOG_TAG, "test__clandro_prefixDir_getFromEnv()");

    test__getClandroPrefixDirFromEnv__Basic();

    int__AEqual(0, errno);
}

void test__getClandroPrefixDirFromEnv__Basic() {
    logVVerbose(LOG_TAG, "test__getClandroPrefixDirFromEnv__Basic()");

    size_t envVarLength = strlen(ENV__CLANDRO__PREFIX) + 1;

    char buffer[CLANDRO__PREFIX_DIR___MAX_LEN];
    size_t bufferSize = sizeof(buffer);

    int result;

    putenv(ENV__CLANDRO__PREFIX "=" CLANDRO__PREFIX);
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual(CLANDRO__PREFIX, buffer);

    putenv(ENV__CLANDRO__PREFIX "=/");
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual("/", buffer);

    putenv(ENV__CLANDRO__PREFIX "=/a");
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual("/a", buffer);

    putenv(ENV__CLANDRO__PREFIX "=a");
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    putenv(ENV__CLANDRO__PREFIX "=a/");
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    putenv(ENV__CLANDRO__PREFIX "=a" CLANDRO__PREFIX);
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    unsetenv(ENV__CLANDRO__PREFIX);
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    state__ATrue(PATH_MAX >= CLANDRO__PREFIX_DIR___MAX_LEN);

    char rootfsDir1[envVarLength + PATH_MAX];
    snprintf(rootfsDir1, sizeof(rootfsDir1), "%s=/%0*d", ENV__CLANDRO__PREFIX, CLANDRO__PREFIX_DIR___MAX_LEN - 1, 0);

    putenv(rootfsDir1);
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    char rootfsDir2[envVarLength + PATH_MAX];
    size_t rootfsDir2Length = snprintf(rootfsDir2, sizeof(rootfsDir2), "%s=/%0*d", ENV__CLANDRO__PREFIX, CLANDRO__PREFIX_DIR___MAX_LEN - 2, 0);

    putenv(rootfsDir2);
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    state__ATrue(rootfsDir2Length - envVarLength == strlen(buffer));

    char buffer1[CLANDRO__PREFIX_DIR___MAX_LEN - 1];
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer1, sizeof(buffer1));
    state__ATrue(result == -1);
    errno = 0;

    char buffer2[CLANDRO__PREFIX_DIR___MAX_LEN - 2];
    result = clandro_prefixDir_getFromEnv(LOG_TAG, buffer2, sizeof(buffer2));
    state__ATrue(result == -1);
    errno = 0;
}





void test__getClandroRootfsDirFromEnv__Basic();

void test__clandro_rootfsDir_getFromEnv() {
    logVerbose(LOG_TAG, "test__clandro_rootfsDir_getFromEnv()");

    test__getClandroRootfsDirFromEnv__Basic();

    int__AEqual(0, errno);
}

void test__getClandroRootfsDirFromEnv__Basic() {
    logVVerbose(LOG_TAG, "test__getClandroRootfsDirFromEnv__Basic()");

    size_t envVarLength = strlen(ENV__CLANDRO__ROOTFS) + 1;

    char buffer[CLANDRO__ROOTFS_DIR___MAX_LEN];
    size_t bufferSize = sizeof(buffer);

    int result;

    putenv(ENV__CLANDRO__ROOTFS "=" CLANDRO__ROOTFS);
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual(CLANDRO__ROOTFS, buffer);

    putenv(ENV__CLANDRO__ROOTFS "=/");
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual("/", buffer);

    putenv(ENV__CLANDRO__ROOTFS "=/a");
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    string__AEqual("/a", buffer);

    putenv(ENV__CLANDRO__ROOTFS "=a");
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    putenv(ENV__CLANDRO__ROOTFS "=a/");
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    putenv(ENV__CLANDRO__ROOTFS "=a" CLANDRO__ROOTFS);
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    unsetenv(ENV__CLANDRO__ROOTFS);
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    state__ATrue(PATH_MAX >= CLANDRO__ROOTFS_DIR___MAX_LEN);

    char rootfsDir1[envVarLength + PATH_MAX];
    snprintf(rootfsDir1, sizeof(rootfsDir1), "%s=/%0*d", ENV__CLANDRO__ROOTFS, CLANDRO__ROOTFS_DIR___MAX_LEN - 1, 0);

    putenv(rootfsDir1);
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 1);

    char rootfsDir2[envVarLength + PATH_MAX];
    size_t rootfsDir2Length = snprintf(rootfsDir2, sizeof(rootfsDir2), "%s=/%0*d", ENV__CLANDRO__ROOTFS, CLANDRO__ROOTFS_DIR___MAX_LEN - 2, 0);

    putenv(rootfsDir2);
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer, bufferSize);
    state__ATrue(result == 0);
    state__ATrue(rootfsDir2Length - envVarLength == strlen(buffer));

    char buffer1[CLANDRO__ROOTFS_DIR___MAX_LEN - 1];
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer1, sizeof(buffer1));
    state__ATrue(result == -1);
    errno = 0;

    char buffer2[CLANDRO__ROOTFS_DIR___MAX_LEN - 2];
    result = clandro_rootfsDir_getFromEnv(LOG_TAG, buffer2, sizeof(buffer2));
    state__ATrue(result == -1);
    errno = 0;
}





void test__clandroApp_dataDir_convertToLegacyPath__Basic();

void test__clandroApp_dataDir_convertToLegacyPath() {
    logVerbose(LOG_TAG, "test__clandroApp_dataDir_convertToLegacyPath()");

    test__clandroApp_dataDir_convertToLegacyPath__Basic();

    int__AEqual(0, errno);
}



#define ctaddtlp__AEqual(expected, clandroAppDataDir, buffer, bufferSize)                           \
    if (1) {                                                                                       \
    assertStringEqualsWithError(expected, clandroApp_dataDir_convertToLegacyPath(LOG_TAG, clandroAppDataDir, buffer, bufferSize), \
        LOG_TAG, "%d: clandroApp_dataDir_convertToLegacyPath('%s')", __LINE__, clandroAppDataDir);   \
    errno = 0;                                                                                     \
    } else ((void)0)



void test__clandroApp_dataDir_convertToLegacyPath__Basic() {
    logVVerbose(LOG_TAG, "test__clandroApp_dataDir_convertToLegacyPath__Basic()");

    char buffer[CLANDRO_APP__DATA_DIR___MAX_LEN];
    size_t bufferSize = sizeof(buffer);

    ctaddtlp__AEqual(NULL, NULL, buffer, bufferSize);
    ctaddtlp__AEqual(NULL, "a", buffer, bufferSize);
    ctaddtlp__AEqual(NULL, "a/", buffer, bufferSize);
    ctaddtlp__AEqual(NULL, "/", buffer, bufferSize);
    ctaddtlp__AEqual(NULL, "/a", buffer, bufferSize);
    ctaddtlp__AEqual(NULL, "/a/", buffer, bufferSize);
    ctaddtlp__AEqual(NULL, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1 "/", buffer, bufferSize);
    ctaddtlp__AEqual(CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, buffer, bufferSize);

    // `11` is length of `/data/data/`.
    char clandroAppDataDir1[PATH_MAX];
    snprintf(clandroAppDataDir1, sizeof(clandroAppDataDir1), "/data/user/0/%0*d", CLANDRO_APP__DATA_DIR___MAX_LEN - 11, 0);
    ctaddtlp__AEqual(NULL, clandroAppDataDir1, buffer, bufferSize);

    char clandroAppDataDir2_1[PATH_MAX];
    snprintf(clandroAppDataDir2_1, sizeof(clandroAppDataDir2_1), "/data/user/0/%0*d", CLANDRO_APP__DATA_DIR___MAX_LEN - 11 - 1, 0);
    char clandroAppDataDir2_2[PATH_MAX];
    snprintf(clandroAppDataDir2_2, sizeof(clandroAppDataDir2_2), "/data/data/%0*d", CLANDRO_APP__DATA_DIR___MAX_LEN - 11 - 1, 0);
    ctaddtlp__AEqual(clandroAppDataDir2_2, clandroAppDataDir2_1, buffer, bufferSize);

}





void test__clandroPrefixPath__Basic();

void test__clandroPrefixPath() {
    logVerbose(LOG_TAG, "test__clandroPrefixPath()");

    test__clandroPrefixPath__Basic();

    int__AEqual(0, errno);
}



#define tpp__AEqual(expected, clandroPrefixDir, executablePath, buffer, bufferSize)                 \
    if (1) {                                                                                       \
    assertStringEqualsWithError(expected, clandroPrefixPath(LOG_TAG, clandroPrefixDir, executablePath, buffer, bufferSize), \
        LOG_TAG, "%d: clandroPrefixPath('%s', '%s')", __LINE__, clandroPrefixDir , executablePath);  \
    errno = 0;                                                                                     \
    } else ((void)0)



void test__clandroPrefixPath__Basic() {
    logVVerbose(LOG_TAG, "test__clandroPrefixPath__Basic()");

    char buffer[PATH_MAX];

    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR, CLANDRO__PREFIX, "/bin", buffer, PATH_MAX);
    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR "/", CLANDRO__PREFIX, "/bin/", buffer, PATH_MAX);
    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR, CLANDRO__PREFIX, "/usr/bin", buffer, PATH_MAX);
    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR "/", CLANDRO__PREFIX, "/usr/bin/", buffer, PATH_MAX);
    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR "/sh", CLANDRO__PREFIX, "/bin/sh", buffer, PATH_MAX);
    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR "/sh", CLANDRO__PREFIX, "/usr/bin/sh", buffer, PATH_MAX);
    tpp__AEqual("/system/bin/sh", CLANDRO__PREFIX, "/system/bin/sh", buffer, PATH_MAX);
    tpp__AEqual("/system/bin/tool", CLANDRO__PREFIX, "/system/bin/tool", buffer, PATH_MAX);
    tpp__AEqual(CLANDRO__PREFIX__BIN_DIR "/sh", CLANDRO__PREFIX, CLANDRO__PREFIX__BIN_DIR "/sh", buffer, PATH_MAX);

    tpp__AEqual("./ab/sh", CLANDRO__PREFIX, "./ab/sh", buffer, PATH_MAX);

}





void test__clandroApp_dataDir_isPathUnder__Basic();

void test__clandroApp_dataDir_isPathUnder() {
    logVerbose(LOG_TAG, "test__clandroApp_dataDir_isPathUnder()");

    test__clandroApp_dataDir_isPathUnder__Basic();

    int__AEqual(0, errno);
}



#define iputadd__ABool(expected, path, clandroAppDataDir, clandroLegacyAppDataDir)                   \
    if (1) {                                                                                       \
    assertIntWithError(expected ? 0 : 1, clandroApp_dataDir_isPathUnder(LOG_TAG, path, clandroAppDataDir, clandroLegacyAppDataDir), \
        LOG_TAG, "%d: clandroApp_dataDir_isPathUnder('%s', '%s', '%s')", __LINE__, path, clandroAppDataDir, clandroLegacyAppDataDir); \
    errno = 0;                                                                                     \
    } else ((void)0)

#define iputadd__AInt(expected, path, clandroAppDataDir, clandroLegacyAppDataDir)                    \
    if (1) {                                                                                       \
    assertIntWithError(expected, clandroApp_dataDir_isPathUnder(LOG_TAG, path, clandroAppDataDir, clandroLegacyAppDataDir), \
        LOG_TAG, "%d: clandroApp_dataDir_isPathUnder('%s', '%s', '%s')", __LINE__, path, clandroAppDataDir, clandroLegacyAppDataDir); \
    errno = 0;                                                                                     \
    } else ((void)0)



void test__clandroApp_dataDir_isPathUnder__Basic() {
    logVVerbose(LOG_TAG, "test__clandroApp_dataDir_isPathUnder__Basic()");

    bool isClandroBinDirUnderClandroAppDataDir = stringStartsWith(CLANDRO__PREFIX__BIN_DIR, CLANDRO_APP__DATA_DIR "/");
    bool isClandroAppDataDirALegacyPath = stringStartsWith(CLANDRO_APP__DATA_DIR, "/data/data/");

    state__ATrue(strlen(CLANDRO_APP__DATA_DIR) < PATH_MAX);
    state__ATrue(strlen(CLANDRO__PREFIX__BIN_DIR) < PATH_MAX);


    iputadd__ABool(false, NULL, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(false, "", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(false, "/", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);

    iputadd__ABool(false, "/a", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(false, "/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(false, "/usr/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(false, "/system/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);


    iputadd__ABool(false, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(true, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2 "/bar", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);

    iputadd__ABool(false, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);
    iputadd__ABool(true, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1 "/bar", CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_APP_DATA_DIR_2);


    if (isClandroAppDataDirALegacyPath) {
        iputadd__ABool(false, CLANDRO_APP__DATA_DIR, NULL, CLANDRO_APP__DATA_DIR);
        iputadd__ABool(true, CLANDRO_APP__DATA_DIR "/foo", NULL, CLANDRO_APP__DATA_DIR);
        iputadd__ABool(isClandroBinDirUnderClandroAppDataDir, CLANDRO__PREFIX__BIN_DIR "/sh", NULL, CLANDRO_APP__DATA_DIR);
        iputadd__ABool(false, "/" CLANDRO__PREFIX__BIN_DIR "/sh", NULL, CLANDRO_APP__DATA_DIR);
        iputadd__ABool(false, "/./" CLANDRO__PREFIX__BIN_DIR "/sh", NULL, CLANDRO_APP__DATA_DIR);
    } else {
        iputadd__ABool(false, CLANDRO_APP__DATA_DIR, CLANDRO_APP__DATA_DIR, NULL);
        iputadd__ABool(true, CLANDRO_APP__DATA_DIR "/foo", CLANDRO_APP__DATA_DIR, NULL);
        iputadd__ABool(isClandroBinDirUnderClandroAppDataDir, CLANDRO__PREFIX__BIN_DIR "/sh", CLANDRO_APP__DATA_DIR, NULL);
        iputadd__ABool(false, "/" CLANDRO__PREFIX__BIN_DIR "/sh", CLANDRO_APP__DATA_DIR, NULL);
        iputadd__ABool(false, "/./" CLANDRO__PREFIX__BIN_DIR "/sh", CLANDRO_APP__DATA_DIR, NULL);
    }


    if (access(CLANDRO__PREFIX__BIN_DIR "/sh", X_OK) == 0) {
        int fd = open(CLANDRO__PREFIX__BIN_DIR "/sh", 0);
        state__ATrue(fd != -1);

        char realPath[PATH_MAX];
        ssize_t length = readlink(CLANDRO__PREFIX__BIN_DIR "/sh", realPath, sizeof(realPath) - 1);
        state__ATrue(length >= 0);
        realPath[length] = '\0';

        // If not running on device, clandro-packages `build-package.sh`
        // `clandro_step_override_config_scripts` step creates a
        // symlink from `$CLANDRO__PREFIX/bin/sh` to `/bin/sh`.
        bool isPathClandroBuilderSymlink = isClandroBinDirUnderClandroAppDataDir &&
            strcmp(realPath, "/bin/sh") == 0;

        char procFdPath[40];
        snprintf(procFdPath, sizeof(procFdPath), "/proc/self/fd/%d", fd);
        if (isClandroAppDataDirALegacyPath) {
            iputadd__ABool(isClandroBinDirUnderClandroAppDataDir && !isPathClandroBuilderSymlink,
                procFdPath, NULL, CLANDRO_APP__DATA_DIR);
        } else {
            iputadd__ABool(isClandroBinDirUnderClandroAppDataDir && !isPathClandroBuilderSymlink,
                procFdPath, CLANDRO_APP__DATA_DIR, NULL);
        }
        close(fd);
    }
    errno = 0;


    if (access("/system/bin/sh", X_OK) == 0) {
        int fd = open("/system/bin/sh", 0);
        state__ATrue(fd != -1);
        char procFdPath[40];
        snprintf(procFdPath, sizeof(procFdPath), "/proc/self/fd/%d", fd);
        if (isClandroAppDataDirALegacyPath) {
            iputadd__ABool(false, procFdPath, NULL, CLANDRO_APP__DATA_DIR);
        } else {
            iputadd__ABool(false, procFdPath, CLANDRO_APP__DATA_DIR, NULL);
        }
        close(fd);
    }
    errno = 0;


    if (access(CLANDRO__PREFIX__BIN_DIR, X_OK) == 0) {
        // S_ISREG should fail in `getRegularFileFdRealPath()`.
        int fd = open(CLANDRO__PREFIX__BIN_DIR, 0);
        state__ATrue(fd != -1);
        char procFdPath[40];
        snprintf(procFdPath, sizeof(procFdPath), "/proc/self/fd/%d", fd);
        if (isClandroAppDataDirALegacyPath) {
            iputadd__AInt(-1, procFdPath, NULL, CLANDRO_APP__DATA_DIR);
        } else {
            iputadd__AInt(-1, procFdPath, CLANDRO_APP__DATA_DIR, NULL);
        }
        close(fd);
    }
    errno = 0;

}





void test__clandro_rootfsDir_isPathUnder__Basic();

void test__clandro_rootfsDir_isPathUnder() {
    logVerbose(LOG_TAG, "test__clandro_rootfsDir_isPathUnder()");

    test__clandro_rootfsDir_isPathUnder__Basic();

    int__AEqual(0, errno);
}



#define iputrd__ABool(expected, path, clandro_rootfs_dir)                                           \
    if (1) {                                                                                       \
    assertIntWithError(expected ? 0 : 1, clandro_rootfsDir_isPathUnder(LOG_TAG, path, clandro_rootfs_dir), \
        LOG_TAG, "%d: clandro_rootfsDir_isPathUnder('%s', '%s')", __LINE__, path, clandro_rootfs_dir); \
    errno = 0;                                                                                     \
    } else ((void)0)

#define iputrd__AInt(expected, path, clandro_rootfs_dir)                                            \
    if (1) {                                                                                       \
    assertIntWithError(expected, clandro_rootfsDir_isPathUnder(LOG_TAG, path, clandro_rootfs_dir),   \
        LOG_TAG, "%d: clandro_rootfsDir_isPathUnder('%s', '%s')", __LINE__, path, clandro_rootfs_dir); \
    errno = 0;                                                                                     \
    } else ((void)0)



void test__clandro_rootfsDir_isPathUnder__Basic() {
    logVVerbose(LOG_TAG, "test__clandro_rootfsDir_isPathUnder__Basic()");

    state__ATrue(strlen(CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1) < PATH_MAX);
    state__ATrue(strlen(CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_1) < PATH_MAX);

    iputrd__ABool(false, NULL, CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);

    iputrd__ABool(false, "/a", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/usr/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/system/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);

    iputrd__ABool(false, CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1, CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(true, CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_1 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/" CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_1 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/./" CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_1 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);
    iputrd__ABool(false, "/../" CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_1 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_1);



    state__ATrue(strlen(CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2) < PATH_MAX);
    state__ATrue(strlen(CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_2) < PATH_MAX);

    iputrd__ABool(false, NULL, CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(false, "", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(false, "/", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);

    iputrd__ABool(false, CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2, CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/a", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/usr/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/system/bin/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);

    iputrd__ABool(true, CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_2 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/" CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_2 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/./" CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_2 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);
    iputrd__ABool(true, "/../" CLANDRO_CORE__TESTS__CLANDRO_BIN_DIR_2 "/sh", CLANDRO_CORE__TESTS__CLANDRO_ROOTFS_DIR_2);



    bool clandroRootfsIsRootfs = strcmp(CLANDRO__ROOTFS, "/") == 0;
    bool clandroRootfsIsSystem = strcmp(CLANDRO__ROOTFS, "/system") == 0;
    bool isClandroBinUnderClandroRootfs = stringStartsWith(CLANDRO__PREFIX__BIN_DIR,
        clandroRootfsIsRootfs ? "/" : CLANDRO__ROOTFS "/");

    state__ATrue(strlen(CLANDRO__ROOTFS) < PATH_MAX);
    state__ATrue(strlen(CLANDRO__PREFIX__BIN_DIR) < PATH_MAX);


    if (access(CLANDRO__PREFIX__BIN_DIR "/sh", X_OK) == 0) {
        int fd = open(CLANDRO__PREFIX__BIN_DIR "/sh", 0);
        state__ATrue(fd != -1);

        char realPath[PATH_MAX];
        ssize_t length = readlink(CLANDRO__PREFIX__BIN_DIR "/sh", realPath, sizeof(realPath) - 1);
        state__ATrue(length >= 0);
        realPath[length] = '\0';

        // If not running on device, clandro-packages `build-package.sh`
        // `clandro_step_override_config_scripts` step creates a
        // symlink from `$CLANDRO__PREFIX/bin/sh` to `/bin/sh`.
        bool isPathClandroBuilderSymlink = isClandroBinUnderClandroRootfs &&
            strcmp(realPath, "/bin/sh") == 0;

        char procFdPath[40];
        snprintf(procFdPath, sizeof(procFdPath), "/proc/self/fd/%d", fd);
        iputrd__ABool(isClandroBinUnderClandroRootfs && !isPathClandroBuilderSymlink,
            procFdPath, CLANDRO__ROOTFS);
        close(fd);
    }
    errno = 0;


    if (access("/system/bin/sh", X_OK) == 0) {
        int fd = open("/system/bin/sh", 0);
        state__ATrue(fd != -1);
        char procFdPath[40];
        snprintf(procFdPath, sizeof(procFdPath), "/proc/self/fd/%d", fd);
        iputrd__ABool(clandroRootfsIsRootfs || clandroRootfsIsSystem, procFdPath, CLANDRO__ROOTFS);
        close(fd);
    }
    errno = 0;


    if (access(CLANDRO__PREFIX__BIN_DIR, X_OK) == 0) {
        // S_ISREG should fail in `getRegularFileFdRealPath()`.
        int fd = open(CLANDRO__PREFIX__BIN_DIR, 0);
        state__ATrue(fd != -1);
        char procFdPath[40];
        snprintf(procFdPath, sizeof(procFdPath), "/proc/self/fd/%d", fd);
        iputrd__AInt(-1, procFdPath, CLANDRO__ROOTFS);
        close(fd);
    }
    errno = 0;
}
