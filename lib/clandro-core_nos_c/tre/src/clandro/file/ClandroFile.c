#define _GNU_SOURCE
#include <errno.h>
#include <libgen.h>
#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/limits.h>

#include <sys/stat.h>

#include <clandro/clandro_core__nos__c/v1/ClandroCoreLibraryConfig.h>
#include <clandro/clandro_core__nos__c/v1/data/DataUtils.h>
#include <clandro/clandro_core__nos__c/v1/logger/Logger.h>
#include <clandro/clandro_core__nos__c/v1/clandro/file/ClandroFile.h>
#include <clandro/clandro_core__nos__c/v1/clandro/shell/command/environment/ClandroShellEnvironment.h>
#include <clandro/clandro_core__nos__c/v1/unix/file/UnixFileUtils.h>
#include <clandro/clandro_core__nos__c/v1/unix/shell/command/environment/UnixShellEnvironment.h>

static const char* LOG_TAG = "ClandroFile";



static char sClandroAppDataDirBuffer[CLANDRO_APP__DATA_DIR___MAX_LEN];

/** The Clandro app data directory path. */
static const char* sClandroAppDataDir = NULL;


static char sClandroAppLegacyDataDirBuffer[CLANDRO_APP__DATA_DIR___MAX_LEN];

/** The Clandro legacy app data directory path. */
static const char* sClandroAppLegacyDataDir = NULL;



static char sClandroRootfsDirBuffer[CLANDRO__ROOTFS_DIR___MAX_LEN];

/** The Clandro rootfs directory path. */
static const char* sClandroRootfsDir = NULL;



static char sClandroPrefixDirBuffer[CLANDRO__PREFIX_DIR___MAX_LEN];

/** The Clandro prefix directory path. */
static const char* sClandroPrefixDir = NULL;



static char sClandroTmpDirBuffer[CLANDRO__PREFIX__TMP_DIR___MAX_LEN];

/** The Clandro tmp directory path. */
static const char* sClandroTmpDir = NULL;





const char* clandroApp_dataDir_get(const char* logTag) {
    if (sClandroAppDataDir == NULL) {
        sClandroAppDataDir = clandroApp_dataDir_getFromEnvOrDefault(logTag,
            sClandroAppDataDirBuffer, sizeof(sClandroAppDataDirBuffer));
    }

    return sClandroAppDataDir;
}

int clandroApp_dataDir_getFromEnv(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnv(LOG_LEVEL__VVERBOSE, logTag,
        "app_data_dir", ENV__CLANDRO_APP__DATA_DIR,
        true, CLANDRO_APP__DATA_DIR___MAX_LEN, true, true,
        buffer, bufferSize);
}

const char* clandroApp_dataDir_getFromEnvOrDefault(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnvOrDefault(LOG_LEVEL__VVERBOSE, logTag,
        "app_data_dir", ENV__CLANDRO_APP__DATA_DIR,
        true, CLANDRO_APP__DATA_DIR___MAX_LEN, true, true,
        CLANDRO_APP__DATA_DIR, -1,
        buffer, bufferSize);
}


const char* clandroApp_legacyDataDir_get(const char* logTag) {
    if (sClandroAppLegacyDataDir == NULL) {
        sClandroAppLegacyDataDir = clandroApp_legacyDataDir_getFromEnvOrDefault(logTag,
            sClandroAppLegacyDataDirBuffer, sizeof(sClandroAppLegacyDataDirBuffer));
    }

    return sClandroAppLegacyDataDir;
}

int clandroApp_legacyDataDir_getFromEnv(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnv(LOG_LEVEL__VVERBOSE, logTag,
        "legacy_app_data_dir", ENV__CLANDRO_APP__LEGACY_DATA_DIR,
        true, CLANDRO_APP__DATA_DIR___MAX_LEN, true, true,
        buffer, bufferSize);
}

const char* clandroApp_legacyDataDir_getFromEnvOrDefault(const char* logTag, char *buffer, size_t bufferSize) {
    const char*  clandroLegacyAppDataDir = getPathFromEnvOrDefault(LOG_LEVEL__VVERBOSE, logTag,
        "legacy_app_data_dir", ENV__CLANDRO_APP__LEGACY_DATA_DIR,
        true, CLANDRO_APP__DATA_DIR___MAX_LEN, true, true,
        CLANDRO_APP__DATA_DIR, -1,
        buffer, bufferSize);
    if (clandroLegacyAppDataDir == NULL) {
        return NULL;
    }

    // If default path is not for a legacy app data directory path,
    // then convert it into a legacy path by extracting the package
    // name from the `basename` of path found and appending it to
    // `/data/data/`.
    if (!stringStartsWith(clandroLegacyAppDataDir, "/data/data/")) {
        char clandroLegacyAppDataDirCopy[strlen(clandroLegacyAppDataDir) + 1];
        strcpy(clandroLegacyAppDataDirCopy, clandroLegacyAppDataDir);

        clandroLegacyAppDataDir = clandroApp_dataDir_convertToLegacyPath(logTag,
            clandroLegacyAppDataDirCopy, buffer, bufferSize);
        if (clandroLegacyAppDataDir == NULL) {
            return NULL;
        }

        if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorVVerbose(logTag, "updated_legacy_app_data_dir: '%s'", clandroLegacyAppDataDir);
        }
    }

    return clandroLegacyAppDataDir;

}


const char* clandroApp_dataDir_convertToLegacyPath(const char* logTag,
    const char *clandroAppDataDir, char *buffer, size_t bufferSize) {
    if (clandroAppDataDir == NULL || *clandroAppDataDir != '/') {
        if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorDebug(logTag, "The app_data_dir '%s' to be converted to legacy path is not an absolute path",
                clandroAppDataDir == NULL ? "" : clandroAppDataDir);
        }
        errno = EINVAL;
        return NULL;
    }

    char *lastPathSeparatorIndex = strrchr(clandroAppDataDir, '/');
    if (!lastPathSeparatorIndex) {
        if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorDebug(logTag, "Failed to find last path separator '/' in app_data_dir '%s' to be converted to legacy path",
                clandroAppDataDir);
        }
        errno = EINVAL;
        return NULL;
    }

    size_t lastPathSeparatorLength = lastPathSeparatorIndex - clandroAppDataDir;
    size_t clandroAppDataDirLength = strlen(clandroAppDataDir);

    if (lastPathSeparatorLength == 0) {
        if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorDebug(logTag, "The last path separator '/' is at rootfs in app_data_dir '%s' to be converted to legacy path",
                clandroAppDataDir);
        }
        errno = EINVAL;
        return NULL;
    }

    // If path does not contain at least one character after last path
    // separator `/`, ideally for package name.
    if ((lastPathSeparatorLength + 1) >= clandroAppDataDirLength) {
      if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorDebug(logTag, "No basename found in app_data_dir '%s' to be converted to legacy path",
                clandroAppDataDir);
        }
        errno = EINVAL;
        return NULL;
    }

    // Copy package name from basename.
    const char *src = lastPathSeparatorIndex + 1;
    size_t clandroLegacyAppDataDirLength = 11 + strlen(src);
    if (bufferSize <= clandroLegacyAppDataDirLength) {
        if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorDebug(logTag, "The legacy_app_data_dir '/data/data/%s' with length '%zu' is too long to fit in the buffer with size '%zu'",
                src, clandroLegacyAppDataDirLength, bufferSize);
        }
        errno = ENAMETOOLONG;
        return NULL;
    }

    strcpy(buffer, "/data/data/");
    strcpy(buffer + 11, src);

    return buffer;
}



const char* clandro_rootfsDir_get(const char* logTag) {
    if (sClandroRootfsDir == NULL) {
        sClandroRootfsDir = clandro_rootfsDir_getFromEnvOrDefault(logTag,
            sClandroRootfsDirBuffer, sizeof(sClandroRootfsDirBuffer));
    }

    return sClandroRootfsDir;
}

int clandro_rootfsDir_getFromEnv(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnv(LOG_LEVEL__VVERBOSE, logTag,
        "rootfs_dir", ENV__CLANDRO__ROOTFS,
        true, CLANDRO__ROOTFS_DIR___MAX_LEN, true, true,
        buffer, bufferSize);
}

const char* clandro_rootfsDir_getFromEnvOrDefault(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnvOrDefault(LOG_LEVEL__VVERBOSE, logTag,
        "rootfs_dir", ENV__CLANDRO__ROOTFS,
        true, CLANDRO__ROOTFS_DIR___MAX_LEN, true, true,
        CLANDRO__ROOTFS, 3 /* (R_OK | X_OK) */,
        buffer, bufferSize);
}



const char* clandro_prefixDir_get(const char* logTag) {
    if (sClandroPrefixDir == NULL) {
        sClandroPrefixDir = clandro_prefixDir_getFromEnvOrDefault(logTag,
            sClandroPrefixDirBuffer, sizeof(sClandroPrefixDirBuffer));
    }

    return sClandroPrefixDir;
}

int clandro_prefixDir_getFromEnv(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnv(LOG_LEVEL__VVERBOSE, logTag,
        "prefix_dir", ENV__CLANDRO__PREFIX,
        true, CLANDRO__PREFIX_DIR___MAX_LEN, true, true,
        buffer, bufferSize);
}

const char* clandro_prefixDir_getFromEnvOrDefault(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnvOrDefault(LOG_LEVEL__VVERBOSE, logTag,
        "prefix_dir", ENV__CLANDRO__PREFIX,
        true, CLANDRO__PREFIX_DIR___MAX_LEN, true, true,
        CLANDRO__PREFIX, 3 /* (R_OK | X_OK) */,
        buffer, bufferSize);
}



const char* clandro_tmpDir_get(const char* logTag) {
    if (sClandroTmpDir == NULL) {
        sClandroTmpDir = clandro_tmpDir_getFromEnvOrDefault(logTag,
            sClandroTmpDirBuffer, sizeof(sClandroTmpDirBuffer));
    }

    return sClandroTmpDir;
}

int clandro_tmpDir_getFromEnv(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnv(LOG_LEVEL__VVERBOSE, logTag,
        "tmp_dir", ENV__TMPDIR,
        true, CLANDRO__PREFIX__TMP_DIR___MAX_LEN, true, true,
        buffer, bufferSize);
}

const char* clandro_tmpDir_getFromEnvOrDefault(const char* logTag, char *buffer, size_t bufferSize) {
    return getPathFromEnvOrDefault(LOG_LEVEL__VVERBOSE, logTag,
        "tmp_dir", ENV__TMPDIR,
        true, CLANDRO__PREFIX__TMP_DIR___MAX_LEN, true, true,
        CLANDRO__PREFIX__TMP_DIR, -1,
        buffer, bufferSize);
}





char *clandroPrefixPath(const char* logTag, const char *clandroPrefixDir, const char *executablePath,
    char *buffer, size_t bufferSize) {
    size_t executablePathLength = strlen(executablePath);
    if (bufferSize <= executablePathLength) {
        if (!libclandro_core__nos__c__getIsRunningTests()) {
            logErrorDebug(LOG_TAG, "The original executable path '%s' with length '%zu' to prefix is too long to fit in the buffer with size '%zu'",
                executablePath, executablePathLength, bufferSize);
        }
        errno = ENAMETOOLONG;
        return NULL;
    }

    // If `executablePath` is not an absolute path.
    if (executablePath[0] != '/') {
        strcpy(buffer, executablePath);
        return buffer;
    }

    char clandroBinPath[CLANDRO__PREFIX__BIN_DIR___MAX_LEN + 1];

    // If `executablePath` equals with `/bin` or `/usr/bin` (currently not `/xxx/bin`).
    if (strcmp(executablePath, "/bin") == 0 || strcmp(executablePath, "/usr/bin") == 0) {
        if (clandroPrefixDir == NULL) {
            clandroPrefixDir = clandro_prefixDir_get(logTag);
            if (clandroPrefixDir == NULL) { return NULL; }
        }

        // If `clandroPrefixDir` equals `/`.
        if (strlen(clandroPrefixDir) == 1 && clandroPrefixDir[0] == '/') {
            strcpy(buffer, executablePath);
            return buffer;
        }

        snprintf(clandroBinPath, sizeof(clandroBinPath), "%s/bin", clandroPrefixDir);
        strcpy(buffer, clandroBinPath);
        return buffer;
    }

    char *binMatchIndex = strstr(executablePath, "/bin/");
    // If `executablePath` starts with `/bin/` or `/xxx/bin`.
    if (binMatchIndex == executablePath || binMatchIndex == (executablePath + 4)) {
        if (clandroPrefixDir == NULL) {
            clandroPrefixDir = clandro_prefixDir_get(logTag);
            if (clandroPrefixDir == NULL) { return NULL; }
        }

        // If `clandroPrefixDir` equals `/`.
        if (strlen(clandroPrefixDir) == 1 && clandroPrefixDir[0] == '/') {
            strcpy(buffer, executablePath);
            return buffer;
        }

        int clandroBinPathLength = snprintf(clandroBinPath, sizeof(clandroBinPath),
            "%s/bin/", clandroPrefixDir);

        strcpy(buffer, clandroBinPath);
        char *dest = buffer + clandroBinPathLength;
        // Copy what comes after `/bin/`.
        const char *src = binMatchIndex + 5;
        size_t prefixedPathLen = clandroBinPathLength + strlen(src);
        if (bufferSize <= prefixedPathLen) {
            if (!libclandro_core__nos__c__getIsRunningTests()) {
                logErrorDebug(logTag, "The prefixed_path '%s%s' with length '%zu' is too long to fit in the buffer with size '%zu'",
                    clandroBinPath, src, prefixedPathLen, bufferSize);
            }
            errno = ENAMETOOLONG;
            return NULL;
        }

        strcpy(dest, src);
        return buffer;
    } else {
        strcpy(buffer, executablePath);
        return buffer;
    }
}





int clandroApp_dataDir_isPathUnder(const char* logTag, const char *path,
    const char *clandroAppDataDir, const char *clandroLegacyAppDataDir) {
    if (path == NULL || *path == '\0') {
        return 1;
    }


    const char* realPath;
    char realPathBuffer[PATH_MAX];
    (void)realPathBuffer;
    if (isFdPath(path)) {
        realPath = getRegularFileFdRealPath(logTag, path, realPathBuffer, sizeof(realPathBuffer));
        if (realPath == NULL) {
            return -1;
        }

        path = realPath;
    }


    // Clandro app for version `>= 0.119.0` will export
    // `CLANDRO_APP__DATA_DIR` with the non-legacy app data directory
    // paths (`/data/user/<user_id>/<package_name>` or
    // `/mnt/expand/<volume_uuid>/user/0/<package_name>`) that
    // are normally returned by Android `ApplicationInfo.dataDir` call.
    // It will also export `CLANDRO_APP__LEGACY_DATA_DIR` with the
    // legacy app data directory path (`/data/data/<package_name>`),
    // however, it will only be accessible if app is running on
    // primary user `0`, or if Android vendor does a bind mount for
    // secondary users/profiles as well or if
    // bind mount was done manually on rooted devices with
    // `MountLegacyAppDataDirPaths.java`.
    //
    // The checking if `path` passed to this function is under clandro
    // app data directory is done based on following logic, assuming
    // `clandroAppDataDir` and `clandroLegacyAppDataDir` passed
    // are `NULL`. The below `FAIL` condition, like where `clandro-exec`
    // was compiled with the default value of a legacy path
    // `/data/data/<package_name>` and a path starting with
    // `/data/user/0/<package_name>` is executed instead
    // of it starting with `/data/data/<package_name>`, would not
    // normally occur as rootfs would be for a legacy path as well,
    // and if solving it is needed, then user should used the app
    // version (like `>= 0.119.0`) where `CLANDRO_APP__DATA_DIR`
    // variable is exported automatically.
    // - Executing path under legacy app data directory:
    //   - If `ENV__CLANDRO_APP__LEGACY_DATA_DIR` is set and valid:
    //       - The env path will be used as is.
    //   - Else:
    //       - A non-legacy default path will be used after being
    //         converted to a legacy path.
    //       - A legacy default path will be used as is.
    // - Executing path under non-legacy app data directory:
    //   - If `ENV__CLANDRO_APP__DATA_DIR` is set and valid:
    //       - The env path will be used as is.
    //   - Else:
    //       - A non-legacy default path will be used as is.
    //       - A legacy default path will be used as is. (FAIL)
    if (stringStartsWith(path, "/data/data/")) {
        if (clandroLegacyAppDataDir == NULL) {
            clandroLegacyAppDataDir = clandroApp_legacyDataDir_get(logTag);
            if (clandroLegacyAppDataDir == NULL) { return -1; }
        }

        clandroAppDataDir = clandroLegacyAppDataDir;
    } else {
        if (clandroAppDataDir == NULL) {
            clandroAppDataDir = clandroApp_dataDir_get(logTag);
            if (clandroAppDataDir == NULL) { return -1; }
        }
    }

    return isPathInDirPath("app_data_dir", path, clandroAppDataDir, true);
}



int clandro_rootfsDir_isPathUnder(const char* logTag, const char *path,
    const char *clandroRootfsDir) {
    if (clandroRootfsDir == NULL) {
        clandroRootfsDir = clandro_rootfsDir_get(logTag);
        if (clandroRootfsDir == NULL) { return -1; }
    }

    return isPathOrFdPathInDirPath(logTag, "rootfs_dir", path, clandroRootfsDir, true);
}
