#ifndef LIBCLANDRO_CORE__NOS__C__CLANDRO_FILE___H
#define LIBCLANDRO_CORE__NOS__C__CLANDRO_FILE___H

#ifdef __cplusplus
extern "C" {
#endif



/**
 * The max length for the `CLANDRO_APP__DATA_DIR` directory including
 * the null '\0' terminator.
 *
 * Check https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#file-path-limits
 * for why the value `69` is chosen.
 *
 * Constant value: `69`
 */
#define CLANDRO_APP__DATA_DIR___MAX_LEN 69





/**
 * The max length for the `CLANDRO__APPS_DIR` including the null '\0'
 * terminator.
 *
 * Check https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#file-path-limits
 * for why the value `84` is chosen.
 *
 * Constant value: `84`
 */
#define CLANDRO__APPS_DIR___MAX_LEN 84



/**
 * The max length for a subdirectory name under the
 * `CLANDRO__APPS_DIR_BY_IDENTIFIER` excluding the null '\0' terminator
 * that represents an app identifier.
 *
 * Check https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#file-path-limits
 * for why the value `10` is chosen.
 *
 * Constant value: `10`
 */
#define CLANDRO__APPS_APP_IDENTIFIER___MAX_LEN 10



/**
 * The max length for the Clandro apps api socket server parent directory
 * including the null '\0' terminator.
 *
 * Check https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#file-path-limits
 * for why the value `98` is chosen.
 *
 * Constant value: `98`
 */
#define CLANDRO__APPS_API_SOCKET__SERVER_PARENT_DIR___MAX_LEN (CLANDRO__APPS_DIR___MAX_LEN + 1 + CLANDRO__APPS_APP_IDENTIFIER___MAX_LEN + 2) // "/NNNNNNNNNN/s" (98)





/**
 * The max length for the `CLANDRO__ROOTFS` directory including the
 * null '\0' terminator.
 *
 * Check https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#file-path-limits
 * for why the value `86` is chosen.
 *
 * Constant value: `86`
 */
#define CLANDRO__ROOTFS_DIR___MAX_LEN 86



/**
 * The max length for the `CLANDRO__PREFIX` directory including the
 * null '\0' terminator.
 *
 * Constant value: `90`
 */
#define CLANDRO__PREFIX_DIR___MAX_LEN (CLANDRO__ROOTFS_DIR___MAX_LEN + 1 + 3) // "/usr" (90)



/**
 * The max length for the `CLANDRO__BIN_DIR` including the null '\0' terminator.
 *
 * Constant value: `94`
 */
#define CLANDRO__PREFIX__BIN_DIR___MAX_LEN (CLANDRO__PREFIX_DIR___MAX_LEN + 1 + 3) // "/bin" (94)

/**
 * The max safe length for a sub file path under the `CLANDRO__BIN_DIR`
 * including the null '\0' terminator.
 *
 * This allows for a filename with max length `33` so that the path
 * length is under `128` (`BINPRM_BUF_SIZE`) for Linux kernel `< 5.1`,
 * and ensures `argv[0]` length is `< 128` on Android `< 6`, otherwise
 * commands will fail with exit code 1 without any error on `stderr`,
 * but with the `library name "<library_name>" too long` error in
 * `logcat` if linker debugging is enabled.
 *
 * **See Also:**
 * - https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#file-path-limits
 * - https://github.com/cl-andro/clandro-exec-package/blob/master/lib/clandro-exec_nos_c/tre/include/clandro/clandro_exec__nos__c/v1/clandro/api/clandro_exec/service/ld_preload/direct/exec/ExecIntercept.h
 *
 * Constant value: `127`
 */
#define CLANDRO__PREFIX__BIN_FILE___SAFE_MAX_LEN (CLANDRO__PREFIX__BIN_DIR___MAX_LEN + 1 + 33) // "/<filename_with_len_33>" (127)



/**
 * The max length for the `CLANDRO__PREFIX__TMP_DIR` directory including
 * the null '\0' terminator.
 *
 * Constant value: `94`
 */
#define CLANDRO__PREFIX__TMP_DIR___MAX_LEN (CLANDRO__PREFIX_DIR___MAX_LEN + 1 + 3) // "/tmp" (94)





/**
 * Get cached `sClandroAppDataDir` that is set to the path returned by
 * `clandroApp_dataDir_getFromEnvOrDefault()` on its first call.
 */
const char* clandroApp_dataDir_get(const char* logTag);

/**
 * Get the Clandro app data directory from the `ENV__CLANDRO_APP__DATA_DIR`
 * env variable value if its set to a valid absolute path with max
 * length `CLANDRO_APP__DATA_DIR___MAX_LEN`.
 *
 *
 * @return Returns `0` if a valid app data directory is found and
 * copied to the buffer, `1` if valid app data directory is not found,
 * otherwise `-1` on other failures.
 */
int clandroApp_dataDir_getFromEnv(const char* logTag,
    char *buffer, size_t bufferSize);

/**
 * Get the Clandro app data directory from the `ENV__CLANDRO_APP__DATA_DIR`
 * env variable if its set to a valid absolute path with max length
 * `CLANDRO_APP__DATA_DIR___MAX_LEN`, otherwise if it fails, then
 * return `CLANDRO_APP__DATA_DIR` set by `Makefile` if it is an absolute
 * path.
 *
 * @return Returns the `char *` to app data directory on success,
 * otherwise `NULL`.
 */
const char* clandroApp_dataDir_getFromEnvOrDefault(const char* logTag,
    char *buffer, size_t bufferSize);



/**
 * Get cached `sClandroAppLegacyDataDir` that is set to the path
 * returned by `clandroApp_legacyDataDir_getFromEnvOrDefault()`
 * on its first call.
 */
const char* clandroApp_legacyDataDir_get(const char* logTag);

/**
 * Get the Clandro legacy app data directory from the
 * `ENV__CLANDRO_APP__LEGACY_DATA_DIR` env variable value if its set to
 * a valid absolute path with max length `CLANDRO_APP__DATA_DIR___MAX_LEN`.
 *
 *
 * @return Returns `0` if a valid directory is found and
 * copied to the buffer, `1` if valid directory is not found,
 * otherwise `-1` on other failures.
 */
int clandroApp_legacyDataDir_getFromEnv(const char* logTag,
    char *buffer, size_t bufferSize);

/**
 * Get the Clandro legacy app data directory from the
 * `ENV__CLANDRO_APP__LEGACY_DATA_DIR` env variable if its set to a
 * valid absolute path with max length `CLANDRO_APP__DATA_DIR___MAX_LEN`,
 * otherwise if it fails, then return `CLANDRO_APP__DATA_DIR` set by
 * `Makefile` if it is readable and executable after converting it to
 * a legacy path if required by calling
 * `clandroApp_dataDir_convertToLegacyPath()`.
 *
 * @return Returns the `char *` to directory on success,
 * otherwise `NULL`.
 */
const char* clandroApp_legacyDataDir_getFromEnvOrDefault(const char* logTag,
    char *buffer, size_t bufferSize);



/**
 * Convert a clandro app data directory in the format
 * `/data/user/<user_id>/<package_name>` or
 * `/mnt/expand/<volume_uuid>/user/0/<package_name>` to a legacy path
 * `/data/data/<package_name>` by extracting the package name from
 * the `basename` and appending it to `/data/data/`.
 *
 * No validation is currently done to ensure `clandroAppDataDir`
 * is in correct format and `basename` is used even if it is not a for
 * a package name. So its callers responsibility to pass a valid path.
 *
 * @return Returns the `char *` to directory on success,
 * otherwise `NULL`.
 */
const char* clandroApp_dataDir_convertToLegacyPath(const char* logTag,
    const char *clandroAppDataDir, char *buffer, size_t bufferSize);





/**
 * Get cached `sClandroRootfsDir` that is set to the path returned by
 * `clandro_rootfsDir_getFromEnvOrDefault()` on its first call.
 */
const char* clandro_rootfsDir_get(const char* logTag);

/**
 * Get the Clandro rootfs directory from the `ENV__CLANDRO__ROOTFS` env
 * variable value if its set to a valid absolute path with max length
 * `CLANDRO__ROOTFS_DIR___MAX_LEN`.
 *
 *
 * @return Returns `0` if a valid directory is found and copied
 * to the buffer, `1` if valid directory is not found, otherwise
 * `-1` on other failures.
 */
int clandro_rootfsDir_getFromEnv(const char* logTag,
    char *buffer, size_t bufferSize);

/**
 * Get the Clandro rootfs directory from the `ENV__CLANDRO__ROOTFS`
 * env variable if its set to a valid absolute path with max length
 * `CLANDRO__ROOTFS_DIR___MAX_LEN`, otherwise if it fails, then return
 * `CLANDRO__ROOTFS` set by `Makefile` if it is readable and executable.
 *
 * @return Returns the `char *` to directory on success,
 * otherwise `NULL`.
 */
const char* clandro_rootfsDir_getFromEnvOrDefault(const char* logTag,
    char *buffer, size_t bufferSize);





/**
 * Get cached `sClandroPrefixDir` that is set to the path returned by
 * `clandro_prefixDir_getFromEnvOrDefault()` on its first call.
 */
const char* clandro_prefixDir_get(const char* logTag);

/**
 * Get the Clandro prefix directory from the `ENV__CLANDRO__PREFIX` env
 * variable value if its set to a valid absolute path with max length
 * `CLANDRO__PREFIX_DIR___MAX_LEN`.
 *
 *
 * @return Returns `0` if a valid directory is found and copied
 * to the buffer, `1` if valid directory is not found, otherwise
 * `-1` on other failures.
 */
int clandro_prefixDir_getFromEnv(const char* logTag,
    char *buffer, size_t bufferSize);

/**
 * Get the Clandro prefix directory from the `ENV__CLANDRO__PREFIX`
 * env variable if its set to a valid absolute path with max length
 * `CLANDRO__PREFIX_DIR___MAX_LEN`, otherwise if it fails, then return
 * `CLANDRO__PREFIX` set by `Makefile` if it is readable and executable.
 *
 * @return Returns the `char *` to directory on success,
 * otherwise `NULL`.
 */
const char* clandro_prefixDir_getFromEnvOrDefault(const char* logTag,
    char *buffer, size_t bufferSize);





/**
 * Get cached `sClandroTmpDir` that is set to the path returned by
 * `clandro_tmpDir_getFromEnvOrDefault()` on its first call.
 */
const char* clandro_tmpDir_get(const char* logTag);

/**
 * Get the Clandro tmp directory from the `ENV__TMPDIR` env
 * variable value if its set to a valid absolute path with max length
 * `CLANDRO__PREFIX__TMP_DIR___MAX_LEN`.
 *
 *
 * @return Returns `0` if a valid tmp directory is found and copied
 * to the buffer, `1` if valid tmp directory is not found, otherwise
 * `-1` on other failures.
 */
int clandro_tmpDir_getFromEnv(const char* logTag,
    char *buffer, size_t bufferSize);

/**
 * Get the Clandro tmp directory from the `ENV__TMPDIR`
 * env variable if its set to a valid absolute path with max length
 * `CLANDRO__PREFIX__TMP_DIR___MAX_LEN`, otherwise if it fails, then return
 * `CLANDRO__PREFIX__TMP_DIR` set by `Makefile` if it is an absolute path.
 *
 * @return Returns the `char *` to tmp directory on success,
 * otherwise `NULL`.
 */
const char* clandro_tmpDir_getFromEnvOrDefault(const char* logTag,
    char *buffer, size_t bufferSize);





/**
 * Prefix `bin` directory paths like `/bin` and `/usr/bin` with
 * clandro prefix directory, like convert `/bin/sh` to `<clandroPrefixDir>/usr/bin/sh`.
 *
 * The buffer size must at least be `CLANDRO__PREFIX_DIR___MAX_LEN` + strlen(executablePath)`,
 * or preferably `PATH_MAX`.
 *
 * @param logTag The log tag to use for logging.
 * @param clandroPrefixDir The **normalized** path to clandro prefix
 *                        directory. If `NULL`, then path returned by
 *                        `clandro_prefixDir_getFromEnvOrDefault()`
 *                         will be used by calling `clandro_prefixDir_get()`.
 * @param executablePath The executable path to prefix.
 * @param buffer The output path buffer.
 * @param bufferSize The output path buffer size.
 * @return Returns the `char *` to original or prefixed directory on
 * success, otherwise `NULL` on failures.
 */
char *clandroPrefixPath(const char* logTag, const char *clandroPrefixDir,
    const char *executablePath, char *buffer, size_t bufferSize);





/**
 * Check whether the `path` is in `clandroAppDataDir`. If path is
 * a fd path matched by `REGEX__PROC_FD_PATH`, then the real path
 * of the fd returned by `getRegularFileFdRealPath()` will be checked
 * instead.
 *
 * **Both `path` and `clandroAppDataDir` must be normalized paths,
 * as `isPathOrFdPathInDirPath()` called by this function will
 * currently not normalize either path by itself.**
 *
 * @param logTag The log tag to use for logging.
 * @param path The `path` to check.
 * @param clandroAppDataDir The **normalized** path to clandro app
 *                data directory. If `NULL`, then path returned by
 *                `clandroApp_dataDir_getFromEnvOrDefault()`
 *                will be used by calling `clandroApp_dataDir_get()`.
 * @param clandroLegacyAppDataDir The **normalized** path to clandro
 *                legacy app data directory in the format
 *                `/data/data/<package_name>`. If `NULL`, then path
 *                returned by `clandroApp_legacyDataDir_getFromEnvOrDefault()`
 *                will be used by calling `clandroApp_legacyDataDir_get()`.
 * @return Returns `0` if `path` is in `clandroAppDataDir`, `1` if
 * `path` is not in `clandroAppDataDir`, otherwise `-1` on other
 * failures.
 */
int clandroApp_dataDir_isPathUnder(const char* logTag, const char *path,
    const char *clandroAppDataDir, const char *clandroLegacyAppDataDir);



/**
 * Check whether the `path` is in `clandroRootfsDir`. If path is
 * a fd path matched by `REGEX__PROC_FD_PATH`, then the real path
 * of the fd returned by `getRegularFileFdRealPath()` will be checked
 * instead.
 *
 * **Both `path` and `clandroRootfsDir` must be normalized paths, as
 * `isPathOrFdPathInDirPath()` called by this function will
 * currently not normalize either path by itself.**
 *
 * @param logTag The log tag to use for logging.
 * @param path The `path` to check.
 * @param clandroRootfsDir The **normalized** path to clandro rootfs
 *                  directory. If `NULL`, then path returned by
 *                  `clandro_rootfsDir_getFromEnvOrDefault()`
 *                  will be used by calling `clandro_rootfsDir_get()`.
 * @return Returns `0` if `path` is in `clandroRootfsDir`, `1` if
 * `path` is not in `clandroRootfsDir`, otherwise `-1` on other
 * failures.
 */
int clandro_rootfsDir_isPathUnder(const char* logTag, const char *path,
    const char *clandroRootfsDir);



#ifdef __cplusplus
}
#endif

#endif // LIBCLANDRO_CORE__NOS__C__CLANDRO_FILE___H
