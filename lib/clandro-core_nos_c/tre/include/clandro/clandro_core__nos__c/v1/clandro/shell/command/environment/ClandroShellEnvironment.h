#ifndef LIBCLANDRO_CORE__NOS__C__CLANDRO_SHELL_ENVIRONMENT___H
#define LIBCLANDRO_CORE__NOS__C__CLANDRO_SHELL_ENVIRONMENT___H

#ifdef __cplusplus
extern "C" {
#endif



/*
 * Environment for Clandro.
 */

/**
 * Environment variable for the Clandro app data directory path.
 *
 * Type: `string`
 * Default key: `CLANDRO_APP__DATA_DIR`
 * Default value: null
 * Values:
 * - An absolute path with max length `CLANDRO_APP__DATA_DIR___MAX_LEN` (`69`)
 *   including the null `\0` terminator.
 */
#define ENV__CLANDRO_APP__DATA_DIR CLANDRO_ENV__S_CLANDRO_APP "DATA_DIR"

/**
 * Environment variable for the Clandro legacy app data directory path.
 *
 * Type: `string`
 * Default key: `CLANDRO_APP__LEGACY_DATA_DIR`
 * Default value: null
 * Values:
 * - An absolute path with max length `CLANDRO_APP__DATA_DIR___MAX_LEN` (`69`)
 *   including the null `\0` terminator.
 */
#define ENV__CLANDRO_APP__LEGACY_DATA_DIR CLANDRO_ENV__S_CLANDRO_APP "LEGACY_DATA_DIR"





/**
 * Environment variable for the Clandro rootfs directory path.
 *
 * Type: `string`
 * Default key: `CLANDRO__ROOTFS`
 * Default value: null
 * Values:
 * - An absolute path with max length `CLANDRO__ROOTFS_DIR___MAX_LEN` (`85`)
 *   including the null `\0` terminator.
 */
#define ENV__CLANDRO__ROOTFS CLANDRO_ENV__S_CLANDRO "ROOTFS"

/**
 * Environment variable for the Clandro prefix directory path.
 *
 * Type: `string`
 * Default key: `CLANDRO__PREFIX`
 * Default value: null
 * Values:
 * - An absolute path with max length `CLANDRO__PREFIX_DIR___MAX_LEN` (`90`)
 *   including the null `\0` terminator.
 */
#define ENV__CLANDRO__PREFIX CLANDRO_ENV__S_CLANDRO "PREFIX"





/**
 * Environment variable for the SeLinux process context of the Clandro
 * app process and its child processes.
 *
 * Type: `string`
 * Default key: `CLANDRO__SE_PROCESS_CONTEXT`
 * Default value: null
 * Values:
 * - A valid Android SeLinux process context that matches `REGEX__PROCESS_CONTEXT`.
 */
#define ENV__CLANDRO__SE_PROCESS_CONTEXT CLANDRO_ENV__S_CLANDRO "SE_PROCESS_CONTEXT"





/**
 * Environment variable for the Clandro rootfs package manager.
 *
 * Type: `string`
 * Default key: `CLANDRO_ROOTFS__PACKAGE_MANAGER`
 * Default value: null
 * Values: `apt` or `pacman`
 */
#define ENV__CLANDRO_ROOTFS__PACKAGE_MANAGER CLANDRO_ENV__S_CLANDRO_ROOTFS "PACKAGE_MANAGER"



#ifdef __cplusplus
}
#endif

#endif // LIBCLANDRO_CORE__NOS__C__CLANDRO_SHELL_ENVIRONMENT___H
