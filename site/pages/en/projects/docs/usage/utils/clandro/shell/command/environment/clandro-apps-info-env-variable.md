---
page_ref: "@ARK_PROJECT__VARIANT@/clandro/clandro-core-package/docs/@ARK_DOC__VERSION@/usage/utils/clandro/shell/command/environment/clandro-apps-info-env-variable.md"
---

# `clandro-apps-info-env-variable` Utils Docs

The `clandro-apps-info-env-variable` scripts/codes provide a way, if running in a Clandro app, to source the `clandro-apps-info.env` file into the current environment or get variable values of Clandro app `CLANDRO_APP__`, its plugin apps `CLANDRO_*_APP__` and external apps `*_APP__` app scoped environment variables that exist in the `clandro-apps-info.env` file, with support for fallback values and validation of values.

This is only supported for Clandro app version `>= 0.119.0` and plugin app versions using its updated internal [`ClandroShellEnvironment`](https://github.com/cl-andro/clandro-app/blob/master/clandro-shared/src/main/java/com/clandro/shared/clandro/shell/command/environment/ClandroShellEnvironment.java) class changes.

### Contents

- [Rationale and Design](#rationale-and-design)
- [Implementations](#implementations)

---

&nbsp;





## Rationale and Design

*If you do not know what `clandro-scoped-env-variable` is and why it exists, or what `CLANDRO*__` scoped environment variables means, check the [Rationale](clandro-scoped-env-variable.md#rationale-and-design) and [Scoped Variables](clandro-scoped-env-variable.md#scoped-variables) sections of [`clandro-scoped-env-variable` Utils Docs](clandro-scoped-env-variable.md).*

`clandro-apps-info-env-variable` exists to solve the following issues in addition to the ones solved by `clandro-scoped-env-variable`.

1. A lot of Clandro internal packages rely on variables specific to Clandro apps, and so do lot of user programs. For examples, specific packages may read the Clandro app version name (`$CLANDRO_APP__APP_VERSION_NAME`) and Clandro:API app version name (`$CLANDRO_API_APP__APP_VERSION_NAME`) to see if app is installed and to run version specific logic, or read other variables get app data directory path or APK file path. The issue is that if environment variables are exported at shell creation time, they only represent the state of the apps at that point in time and any changes in the apps will result in the variables getting invalid. For example, if Clandro:API app is not installed when Clandro app creates a shell, its environment variables wouldn't be set. If user then installs the Clandro:API app, packages in older shells will not know that it got installed, and only new shells will know. Moreover, if the Clandro:API app was already installed at shell creation time and its variables were exported, it could either be updated or uninstalled afterwards, and its environment variables in the current shell would still refer to the old state. This will cause problems in running code dependent on app states.

2. So there needs to be way a for the current shell to get variable values representing the current state of apps. However, there are two main consideration for the mechanism that should be used to get the variable values. Firstly, latency must be very low, as there are time sensitive programs like [`clandro-api-package`](https://github.com/cl-andro/clandro-api-package) scripts that cannot waste time just getting the variable values. Secondly, it should be easily callable from shells like `bash` and POSIX `sh` shells, and other binaries. A filesystem socket server running in the Clandro app (like for [`clandro-am-socket`](https://github.com/cl-andro/clandro-am-socket)) that clients could connect to to get the required variable values cannot be used as that has a high latency and first a server must be connected to, then a command sent and then additional I/O and time needs to spent to receive the variable values from the server. Additionally, a single command will only be able to get a single value as the result, unless additional parsing is done on output, which isn't always possible depending on calling shell/binary and parsing may require additional external calls, increasing latency yet again. Instead, an `.env` file ([1](https://github.com/ko1nksm/shdotenv#env-file-syntax), [2](https://github.com/ko1nksm/shdotenv/blob/main/docs/specification.md)) based approach is better, where all the required variables related to apps are written to an `.env` file by the app hosting the current shell whenever any of the watched app is installed, updated or uninstalled. Whenever a variable value needs to be read, the file can be first sourced into the environment of the current shell so that latest value gets loaded, and then the value can be read. Programs that are not running in a shell (like `c`/`c++` code) cannot (easily) source a file, so additionally a `.json` file can also be written to which can be parsed, and an executable is `$PATH` can also be provided that can be executed to get the variable values, which internally first sources the `.env` file.

3. Each Clandro app that can host a shell, like the main Clandro app and Clandro:Float app, must manage its own `.env` and `.json` files. If only the main Clandro app managed a single file for all apps, then if the main Clandro app was not running and a plugin app like Clandro:Float was hosting a shell, then the file would not be getting updated and anyone reading it would get old and invalid values. The contents of files maintained by different apps could vary too, like if some external apps are bound to main Clandro app, its variables would get added to the file managed by Clandro app, but not the one managed by Clandro:Float as it wouldn't have info about the external apps bound to main Clandro app, at least without using some Clandro app API to get them.

4. Since each Clandro app needs to manage its own environment files, each app will need to export the paths for its own `.env` and `.json` files in environment variables which should be used for sourcing/reading, namely `$CLANDRO_CORE__APPS_INFO_ENV_FILE` and `$CLANDRO_CORE__APPS_INFO_JSON_FILE` respectively, check below for more info. Additionally, the environment variable names would need to be scoped to Clandro and could have a different root scope than the default `CLANDRO_` value defined by the `$CLANDRO_ENV__S_ROOT` variable, and so the name of the variable to read for the paths would need to be dynamically generated before sourcing. For example, if running under a forked Foo app with `FOO_` root scope set in `$CLANDRO_ENV__S_ROOT`, then it will have its `.env` file path set in `FOO_CORE__APPS_INFO_ENV_FILE` variable instead for the file managed by Foo app. If under the Foo app shell, a user wants to call Clandro packages with `root`/`su`, they could switch to a Clandro environment by sourcing `$CLANDRO__PREFIX/etc/clandro/clandro.env` file with `CLANDRO_` root scope set in `$CLANDRO_ENV__S_ROOT`, and starting a Clandro shell. Under this Clandro environment, the `$CLANDRO_CORE__APPS_INFO_ENV_FILE` variable would refer to the different file managed by Clandro app instead of the one managed by the Foo app with `$FOO_CORE__APPS_INFO_ENV_FILE`. If the forked app did not change the root scope and kept `CLANDRO_` as root scope, then just multiple environments wouldn't be possible and even `CLANDRO_APP__` variables would refer to values for the Foo app.

5. If a program wants to read the environment variables of the same app that is currently hosting the shell, then it may not need to source/read the `.env` and `.json` files as all or most variables for the current app would already be exported and can be read directly from the process environment, as they would not change as long as app is alive or not updated, and sourcing/reading the files would just waste time.

6. The variables for the apps exported in the environment files would be scoped to specific Clandro apps or external apps, and so [`clandro-scoped-env-variable`] or a similar logic will need to be used to read the variables after sourcing the `.env` file to the current environment, and optionally validation done as well on the values read.

7. If the `.env` file was already sourced earlier, and updated value needs to be read by sourcing the `.env` file again, then the variable to be read would need to be unset before sourcing the `.env` file as an updated version of the file may not have exported it, like if its respective app got uninstalled after the last sourcing. If its not unset beforehand, then the stale value would still be kept in the environment after the sourcing.

8. Multiple variables may need to be read for one ore more apps by a script, and sourcing should normally only be done once if variables are read in sequence in a short amount of time, so an option should be available to just source the `.env` file. Any variables that need to be read would have to be manually unset by users with the `clandro-scoped-env-variable unset-value` command before sourcing the file.

9. If variables of all Clandro and plugin apps are exported for every shell created by the app, then it clutters the shell environment and increases the space used for storing the environment in memory and time taken to copy it when processes are forked. The increased space usage will affect the max size of arguments that can be passed to commands as per `ARG_MAX` limits, which can result in `Argument list too long` errors. If all the non-current app variables exist in a file, then they can be sourced/read only when needed to reduce/prevent such issues.

To solve the above issues, each Clandro app version `>= 0.119.0` and plugin app versions using its updated internal [`ClandroShellEnvironment`](https://github.com/cl-andro/clandro-app/blob/master/clandro-shared/src/main/java/com/clandro/shared/clandro/shell/command/environment/ClandroShellEnvironment.java) class changes creates the `clandro-apps-info.env` and `clandro-apps-info.json` files at app startup with variables for the Clandro app, all official Clandro plugins apps, any apps with the same `sharedUserId` and external apps bound to the Clandro app plugin service. Additionally, the files are updated whenever any of those packages are installed, updated or uninstalled. The paths to the `clandro-apps-info.env` and `clandro-apps-info.json` files are exported in the `$CLANDRO_CORE__APPS_INFO_ENV_FILE` and `$CLANDRO_CORE__APPS_INFO_JSON_FILE` environment variables respectively. Since the variables are scoped, they can have a different root scope than the default `CLANDRO_` value defined by the `$CLANDRO_ENV__S_ROOT` variable, and so the name of the variable to read for the path must be dynamically generated before sourcing. The path to the files will be under the Clandro apps directory ([`$CLANDRO__APPS_DIR_BY_IDENTIFIER`](https://github.com/cl-andro/clandro-packages/wiki/Clandro-file-system-layout#clandro-apps-directory)) for the Clandro app or plugin that hosts the shell, which defaults to `/data/data/com.clandro/clandro/app/i`.

If running in Clandro app version `< 0.119.0` where environment variables are not exported, then `clandro-apps-info.env` file wouldn't exist and any calls to `clandro-apps-info-env-variable` utils would return with the exit code `81` (`C_EX__NOT_FOUND`) as the required environment variables would not be set, unless default fallback values are passed.

---

&nbsp;





## Implementations

The following implementations are currently provided for `clandro-apps-info-env-variable` utils. Implementations for additional languages are planned for future, for now the `clandro-apps-info-env-variable` executable in `$PATH` can be used by them.

- [Executable in `$PATH` (`clandro-apps-info-env-variable`)](#clandro-apps-info-env-variable)
- [`bash` shell (`clandro-apps-info-env-variable.bash`)](#bash)
- [POSIX shells (`clandro-apps-info-env-variable.sh`)](#sh)

&nbsp;



### `clandro-apps-info-env-variable`

`clandro-apps-info-env-variable` exists in Clandro default `bin` directory in `$PATH` in Clandro environments and can be executed as a command with arguments.

Currently, it is a symlink to [`clandro-apps-info-env-variable.bash`](#bash), check its [Help](#help) section for more info on supported arguments and [Examples](#examples-1) section for additional examples.

**DO NOT** [`source`](https://www.gnu.org/software/bash/manual/bash.html#index-_002e) this file, as underlying implementation may not be guaranteed to be a `bash` syntax. It should be executed (with [`exec()`](https://en.wikipedia.org/wiki/Exec_(system_call))) and its `stdout` captured for the result output.

The `output_mode` argument must be set to `>` so that output is returned in `stdout`, as if a variable name is passed instead, the variable will only be set in the `clandro-apps-info-env-variable` child process and not in the calling parent process. The `>` argument should be quoted with single `'` or double quotes `"` if running in a shell, otherwise it may be considered a [command redirection](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07).

&nbsp;



#### Examples

##### `CLANDRO_APP__DATA_DIR`

Get `$CLANDRO_APP__DATA_DIR` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not a valid absolute path (excluding rootfs `/`), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be printed to `stdout`.

```shell
clandro-apps-info-env-variable get-value '>' cn="clandro-app" "DATA_DIR" r+="^(/[^/]+)+$" || return $?
```

## &nbsp;

&nbsp;



### bash

`clandro-apps-info-env-variable.bash` is a [`bash` shell](https://www.gnu.org/software/bash/manual/bash.html) implementation for `clandro-apps-info-env-variable` and exists in Clandro default `bin` directory in `$PATH` in Clandro environments.

The source file for the `clandro-apps-info-env-variable.bash` script is the [`clandro-apps-info-env-variable.bash.in`] file in the `clandro-core-package` repo, and it internally uses the [`clandro_core__bash__clandro_apps_info_env_variable()`] function defined in the `clandro-packages` repo which is replaced at build time with the `@CLANDRO_CORE__BASH__CLANDRO_APPS_INFO_ENV_VARIABLE@` placeholder, see below for how.

`clandro-apps-info-env-variable.bash` script can be used at runtime by:

1. Sourcing the `clandro-apps-info-env-variable.bash` file in `$PATH` (with [`.`](https://www.gnu.org/software/bash/manual/bash.html#index-_002e) or [`source`](https://www.gnu.org/software/bash/manual/bash.html#index-source) command) by running the following commands and then calling the `clandro_core__bash__clandro_apps_info_env_variable()` function that should be defined in the current shell environment. The dependency functions like [`clandro_core__bash__clandro_scoped_env_variable()`] will also get automatically defined when sourcing the `clandro-apps-info-env-variable.bash` file and the `clandro-scoped-env-variable.bash` file will not need to be sourced.
For the `get-*` commands, the name of an environment variable in which the output should be set can be passed as the `output_mode` argument, instead of having to call the function in a subshell and capturing its `stdout` for the output.  
The `command -v` command is used to find the location of the script file instead of directly using the `.`/`source` command to prevent sourcing of a (malicious) file in the current working directory with the same name instead of the one in `$PATH`. A separate function is used to source so that arguments passed to calling script/function are not passed to the sourced script. Replace `exit` with `return` if running inside a function.
    ```shell
    source_file_from_path() { local source_file="${1:-}"; [ $# -gt 0 ] && shift 1; local source_path; if source_path="$(command -v "$source_file")" && [ -n "$source_path" ]; then source "$source_path" || return $?; else echo "Failed to find the '$source_file' file to source." 1>&2; return 1; fi; }

    source_file_from_path "clandro-apps-info-env-variable.bash" || exit $?

    clandro_core__bash__clandro_apps_info_env_variable <command> output_variable <arguments...> || exit $?
    ```

2. Executing `clandro-apps-info-env-variable.bash` directly (with [`exec()`](https://en.wikipedia.org/wiki/Exec_(system_call))) and capturing its `stdout`/`stderr` for the output and errors.
    ```shell
    output="$(clandro-apps-info-env-variable.bash <command> '>' <arguments...>)" || exit $?
    ```

Sourcing should be preferred, especially if multiple variable names or values need to be read. Sourcing the `clandro-apps-info-env-variable.bash` script once would be a single external call, and then any calls to the `clandro_core__bash__clandro_apps_info_env_variable()` function would all be local calls, so would be faster than if `clandro-apps-info-env-variable.bash` script is executed multiple times with external calls for each variable. If efficiency is not an issue, then it doesn't matter much if script is executed or sourced, other than being able to pass a variable name as `output_mode`.

&nbsp;

If efficiency is an issue for time critical calling scripts that require low latency, the `clandro_core__bash__clandro_apps_info_env_variable()` function can be imported into calling script source files so that external calls to source or execute `clandro-apps-info-env-variable.bash` is not required and the function can be called locally as it will already be defined. This can be done at build time by:

1. The [`clandro_core__bash__clandro_apps_info_env_variable()`] function and its dependency functions like [`clandro_core__bash__clandro_scoped_env_variable()`] can be copied into calling script source files manually. It will have to kept in sync with upstream whenever any changes or fixes are done. The `@CLANDRO_ENV__S_ROOT@` placeholder in the function should ideally be replaced at build time with the value defined in the [`properties.sh`] file of the `clandro-packages` repo.
2. The `@CLANDRO_CORE__BASH__CLANDRO_APPS_INFO_ENV_VARIABLE@` placeholder can be added to calling script source files as a commented line like `##### @CLANDRO_CORE__BASH__CLANDRO_APPS_INFO_ENV_VARIABLE@ to be replaced at build time. #####` and then during build time, the [`clandro-replace-clandro-core-src-scripts`] script in the `clandro-packages` repo can be executed and passed the paths to the script source files so that it replaces the placeholders with actual source content of the [`clandro_core__bash__clandro_apps_info_env_variable()`] function and its dependency functions like [`clandro_core__bash__clandro_scoped_env_variable()`]. The required variables listed in the `clandro-replace-clandro-core-src-scripts` script help must be exported when executing it. For example, the `clandro-core` package [`build.sh`](https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/build.sh) file used for compiling the package, passes the build time values for the required variables and the `$CLANDRO_PKGS__BUILD__REPO_ROOT_DIR` environment variable for the root directory of the local `clandro-packages` build repo directory, which is required to find the path of the `clandro-replace-clandro-core-src-scripts` script on the local filesystem so that it can be executed. The [`Makefile`](https://github.com/cl-andro/clandro-core-package/blob/v0.4.0/Makefile) of the `clandro-core` package then reads the variables and executes the `clandro-replace-clandro-core-src-scripts` script on the [`clandro-apps-info-env-variable.bash.in`] file that contains the `@CLANDRO_CORE__BASH__CLANDRO_APPS_INFO_ENV_VARIABLE@` placeholder.

&nbsp;



#### Help

```
clandro-apps-info-env-variable.bash can be used to source the
`clandro-apps-info.env` file into the current environment or get
variable values of Clandro app `CLANDRO_APP__`, its plugin apps
`CLANDRO_*_APP__` and external apps `*_APP__` app scoped environment
variables that exist in the `clandro-apps-info.env` file, with
support for fallback values and validation of values.


Usage:
  clandro-apps-info-env-variable.bash <command> <args...>


Available commands:
    source-env                   Source the apps info environment.
    get-value                    Get Clandro scoped variable value.



source-env:
  clandro-apps-info-env-variable.bash source-env \
    <output_mode> \
    <scoped_var_scope_mode> <scoped_var_sub_name>



get-value:
  clandro-apps-info-env-variable.bash get-value [<command_options>] \
    <output_mode> \
    <scoped_var_scope_mode> <scoped_var_sub_name> \
    <extended_validator> [<default_values...>]

Available command options:
  [ --ensure-sourcing ]
                     Ensure sourcing of `clandro-apps-info.env` file
                     before getting value.
  [ --skip-sourcing ]
                     Skip sourcing of `clandro-apps-info.env` file
                     before getting value.
  [ --skip-sourcing-if-cur-app-var ]
                     Skip sourcing of `clandro-apps-info.env` file
                     before getting value if app scope of the variable
                     to get is the same as the app scope of the
                     current app set in the `$CLANDRO_ENV__S_APP`
                     environment variable.
```

The `source-env` command type sources the `clandro-apps-info.env` file
into the current environment. If the file does not exist, then the
call will return with exit code `69` (`EX__UNAVAILABLE`).

The `get-value` command type returns the value for the Clandro scoped
environment variable generated depending on the variable scope and sub
name passed. First its value is read from the environment after
optionally sourcing the `clandro-apps-info.env`  file depending on
`--*-sourcing*` flags, followed by reading the optional values
passed as `default_values`, and whichever value first matches the
`extended_validator` is returned and if no value matches, then the
call will return with exit code `81` (`C_EX__NOT_FOUND`).
If the file does not exist and `--ensure-sourcing` flag was passed,
then the call will return with exit code `69` (`EX__UNAVAILABLE`).
The `scoped_var_scope_mode` argument must be set, and for scope mode
(`s=`) and sub scope mode (`ss=`), the values must end with `_APP__`,
and for the component name mode (`cn=`), the value must end with
`-app`.

The `source-env` command type is not available if executing the
`clandro-apps-info-env-variable.bash` script as that will not have any
effect on the calling process environment and is only available if
the script is sourced and the
`clandro_core__bash__clandro_apps_info_env_variable` function is called.

Check the help of `clandro-scoped-env-variable.bash` command for info
on the arguments for the `get-value` command type.

**See Also:**
- [`clandro-apps-info-env-variable.bash.in`]
- [`clandro_core__bash__clandro_apps_info_env_variable()`]
.
- [`clandro-scoped-env-variable`]
- [`clandro-scoped-env-variable.bash.in`]
- [`clandro_core__bash__clandro_scoped_env_variable()`]

&nbsp;



#### Examples

The following examples assume that `clandro-apps-info-env-variable.bash` script has been sourced in the current shell (so that/or) the `clandro_core__bash__clandro_apps_info_env_variable` function is defined and can be called. If `clandro-apps-info-env-variable.bash` needs to be executed instead, then replace `clandro_core__bash__clandro_apps_info_env_variable` in the following examples with `clandro-apps-info-env-variable`/`clandro-apps-info-env-variable.bash` and the second argument for `output_mode` with the value `>` so that the output is printed to `stdout`.

```shell
source_file_from_path() { local source_file="${1:-}"; [ $# -gt 0 ] && shift 1; local source_path; if source_path="$(command -v "$source_file")" && [ -n "$source_path" ]; then source "$source_path" || return $?; else echo "Failed to find the '$source_file' file to source." 1>&2; return 1; fi; }

source_file_from_path "clandro-apps-info-env-variable.bash" || exit $?
```

&nbsp;



##### Source Environment

Source the `clandro-apps-info.env` file into the current environment.

```shell
clandro_core__bash__clandro_apps_info_env_variable source-env || return $?
```

&nbsp;



##### `CLANDRO_APP__DATA_DIR`

Get `$CLANDRO_APP__DATA_DIR` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not a valid absolute path (excluding rootfs `/`), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$CLANDRO_APP__DATA_DIR` variable.

```shell
clandro_core__bash__clandro_apps_info_env_variable get-value CLANDRO_APP__DATA_DIR cn="clandro-app" "DATA_DIR" r+="^(/[^/]+)+$" || return $?
```

Get `$CLANDRO_APP__DATA_DIR` variable value from the current environment if running under Clandro app, otherwise from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not a valid absolute path (excluding rootfs `/`), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$CLANDRO_APP__DATA_DIR` variable.

```shell
clandro_core__bash__clandro_apps_info_env_variable get-value --skip-sourcing-if-cur-app-var CLANDRO_APP__DATA_DIR cn="clandro-app" "DATA_DIR" r+="^(/[^/]+)+$" || return $?
```

&nbsp;



##### `CLANDRO_APP__TARGET_SDK`

Get `$CLANDRO_APP__TARGET_SDK` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not an unsigned integer in the range `0-10000` (inclusive), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$CLANDRO_APP__TARGET_SDK` variable.

```shell
is_valid_target_sdk() { case "${1:-}" in ''|*[!0-9]*|0[0-9]*) return 1;; esac; [ "$1" -le 10000 ]; }

clandro_core__bash__clandro_apps_info_env_variable get-value CLANDRO_APP__TARGET_SDK cn="clandro-app" "TARGET_SDK" c+='is_valid_target_sdk' || return $?
```

&nbsp;



##### Multiple Variable Read

Unset `$CLANDRO_APP__APK_FILE` and `$CLANDRO_APP__DATA_DIR` variables, then source the `clandro-apps-info.env` file to set their latest values into the current environment, then get their variable values without sourcing the file again.

```shell
clandro_core__bash__clandro_scoped_env_variable unset-value cn="clandro-app" "APK_FILE" || return $?
clandro_core__bash__clandro_scoped_env_variable unset-value cn="clandro-app" "DATA_DIR" || return $?
clandro_core__bash__clandro_apps_info_env_variable source-env || return $?
clandro_core__bash__clandro_apps_info_env_variable get-value --skip-sourcing CLANDRO_APP__APK_FILE cn="clandro-app" "APK_FILE" r+="^(/[^/]+)+$" || return $?
clandro_core__bash__clandro_apps_info_env_variable get-value --skip-sourcing CLANDRO_APP__DATA_DIR cn="clandro-app" "DATA_DIR" r+="^(/[^/]+)+$" || return $?
```

&nbsp;



##### External App

Get `$FOO_APP__UID` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not an unsigned integer, then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$FOO_APP__UID` variable.

```shell
clandro_core__bash__clandro_apps_info_env_variable get-value FOO_APP__UID s="FOO_APP__" "UID" r+="^[0-9]+$" || return $?
```

## &nbsp;

&nbsp;



### sh

`clandro-apps-info-env-variable.sh` is a [POSIX shell](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) implementation for `clandro-apps-info-env-variable` and exists in Clandro default `bin` directory in `$PATH` in Clandro environments. However, the shell must support the [`local`](https://www.shellcheck.net/wiki/SC3043) keyword for variables, which normally is supported.

The source file for the `clandro-apps-info-env-variable.sh` script is the [`clandro-apps-info-env-variable.sh.in`] file in the `clandro-core-package` repo, and it internally uses the [`clandro_core__sh__clandro_apps_info_env_variable()`] function defined in the `clandro-packages` repo which is replaced at build time with the `@CLANDRO_CORE__SH__CLANDRO_APPS_INFO_ENV_VARIABLE@` placeholder, see below for how.

`clandro-apps-info-env-variable.sh` script can be used at runtime by:

1. Sourcing the `clandro-apps-info-env-variable.sh` file in `$PATH` (with [`.`](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_18_01) command) by running the following commands and then calling the `clandro_core__sh__clandro_apps_info_env_variable()` function that should be defined in the current shell environment. The dependency functions like [`clandro_core__sh__clandro_scoped_env_variable()`] will also get automatically defined when sourcing the `clandro-apps-info-env-variable.sh` file and the `clandro-scoped-env-variable.sh` file will not need to be sourced.
For the `get-*` commands, the name of an environment variable in which the output should be set can be passed as the `output_mode` argument, instead of having to call the function in a subshell and capturing its `stdout` for the output.  
The `command -v` command is used to find the location of the script file instead of directly using the `.`/`source` command to prevent sourcing of a (malicious) file in the current working directory with the same name instead of the one in `$PATH`. A separate function is used to source so that arguments passed to calling script/function are not passed to the sourced script. Passing `--sourcing-script` argument is necessary if sourcing from a `sh` shell script so that script `main` function is not run as there is no POSIX way to detect if current script is being sourced from another script. Replace `exit` with `return` if running inside a function.
    ```shell
    source_file_from_path() { local source_file="${1:-}"; [ $# -gt 0 ] && shift 1; local source_path; if source_path="$(command -v "$source_file")" && [ -n "$source_path" ]; then . "$source_path" || return $?; else echo "Failed to find the '$source_file' file to source." 1>&2; return 1; fi; }

    source_file_from_path "clandro-apps-info-env-variable.sh" --sourcing-script || exit $?

    clandro_core__sh__clandro_apps_info_env_variable <command> output_variable <arguments...> || exit $?
    ```

2. Executing `clandro-apps-info-env-variable.sh` directly (with [`exec()`](https://en.wikipedia.org/wiki/Exec_(system_call))) and capturing its `stdout`/`stderr` for the output and errors.
    ```shell
    output="$(clandro-apps-info-env-variable.sh <command> '>' <arguments...>)" || exit $?
    ```

Sourcing should be preferred, especially if multiple variable names or values need to be read. Sourcing the `clandro-apps-info-env-variable.sh` script once would be a single external call, and then any calls to the `clandro_core__sh__clandro_apps_info_env_variable()` function would all be local calls, so would be faster than if `clandro-apps-info-env-variable.sh` script is executed multiple times with external calls for each variable. If efficiency is not an issue, then it doesn't matter much if script is executed or sourced, other than being able to pass a variable name as `output_mode`.

&nbsp;

If efficiency is an issue for time critical calling scripts that require low latency, the `clandro_core__sh__clandro_apps_info_env_variable()` function can be imported into calling script source files so that external calls to source or execute `clandro-apps-info-env-variable.sh` is not required and the function can be called locally as it will already be defined. This can be done at build time by:

1. The [`clandro_core__sh__clandro_apps_info_env_variable()`] function and its dependency functions like [`clandro_core__sh__clandro_scoped_env_variable()`] can be copied into calling script source files manually. It will have to kept in sync with upstream whenever any changes or fixes are done. The `@CLANDRO_ENV__S_ROOT@` placeholder in the function should ideally be replaced at build time with the value defined in the [`properties.sh`] file of the `clandro-packages` repo.
2. The `@CLANDRO_CORE__SH__CLANDRO_APPS_INFO_ENV_VARIABLE@` placeholder can be added to calling script source files as a commented line like `##### @CLANDRO_CORE__SH__CLANDRO_APPS_INFO_ENV_VARIABLE@ to be replaced at build time. #####` and then during build time, the [`clandro-replace-clandro-core-src-scripts`] script in the `clandro-packages` repo can be executed and passed the paths to the script source files so that it replaces the placeholders with actual source content of the [`clandro_core__sh__clandro_apps_info_env_variable()`] function and its dependency functions like [`clandro_core__sh__clandro_scoped_env_variable()`]. The required variables listed in the `clandro-replace-clandro-core-src-scripts` script help must be exported when executing it. For example, the `clandro-core` package [`build.sh`](https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/build.sh) file used for compiling the package, passes the build time values for the required variables and the `$CLANDRO_PKGS__BUILD__REPO_ROOT_DIR` environment variable for the root directory of the local `clandro-packages` build  repo directory, which is required to find the path of the `clandro-replace-clandro-core-src-scripts` script on the local filesystem so that it can be executed. The [`Makefile`](https://github.com/cl-andro/clandro-core-package/blob/v0.4.0/Makefile) of the `clandro-core` package then reads the variables and executes the `clandro-replace-clandro-core-src-scripts` script on the [`clandro-apps-info-env-variable.sh.in`] file that contains the `@CLANDRO_CORE__SH__CLANDRO_APPS_INFO_ENV_VARIABLE@` placeholder.

&nbsp;



#### Help

```
clandro-apps-info-env-variable.sh can be used to source the
`clandro-apps-info.env` file into the current environment or get
variable values of Clandro app `CLANDRO_APP__`, its plugin apps
`CLANDRO_*_APP__` and external apps `*_APP__` app scoped environment
variables that exist in the `clandro-apps-info.env` file, with
support for fallback values and validation of values.


Usage:
  clandro-apps-info-env-variable.sh <command> <args...>


Available commands:
    source-env                   Source the apps info environment.
    get-value                    Get Clandro scoped variable value.



source-env:
  clandro-apps-info-env-variable.sh source-env \
    <output_mode> \
    <scoped_var_scope_mode> <scoped_var_sub_name>



get-value:
  clandro-apps-info-env-variable.sh get-value [<command_options>] \
    <output_mode> \
    <scoped_var_scope_mode> <scoped_var_sub_name> \
    <posix_validator> [<default_values...>]

Available command options:
  [ --ensure-sourcing ]
                     Ensure sourcing of `clandro-apps-info.env` file
                     before getting value.
  [ --skip-sourcing ]
                     Skip sourcing of `clandro-apps-info.env` file
                     before getting value.
  [ --skip-sourcing-if-cur-app-var ]
                     Skip sourcing of `clandro-apps-info.env` file
                     before getting value if app scope of the variable
                     to get is the same as the app scope of the
                     current app set in the `$CLANDRO_ENV__S_APP`
                     environment variable.
```

The `source-env` command type sources the `clandro-apps-info.env` file
into the current environment. If the file does not exist, then the
call will return with exit code `69` (`EX__UNAVAILABLE`).

The `get-value` command type returns the value for the Clandro scoped
environment variable generated depending on the variable scope and sub
name passed. First its value is read from the environment after
optionally sourcing the `clandro-apps-info.env`  file depending on
`--*-sourcing*` flags, followed by reading the optional values
passed as `default_values`, and whichever value first matches the
`posix_validator` is returned and if no value matches, then the
call will return with exit code `81` (`C_EX__NOT_FOUND`).
If the file does not exist and `--ensure-sourcing` flag was passed,
then the call will return with exit code `69` (`EX__UNAVAILABLE`).
The `scoped_var_scope_mode` argument must be set, and for scope mode
(`s=`) and sub scope mode (`ss=`), the values must end with `_APP__`,
and for the component name mode (`cn=`), the value must end with
`-app`.

The `source-env` command type is not available if executing the
`clandro-apps-info-env-variable.sh` script as that will not have any
effect on the calling process environment and is only available if
the script is sourced and the
`clandro_core__sh__clandro_apps_info_env_variable` function is called.

Check the help of `clandro-scoped-env-variable.sh` command for info
on the arguments for the `get-value` command type.

**See Also:**
- [`clandro-apps-info-env-variable.sh.in`]
- [`clandro_core__sh__clandro_apps_info_env_variable()`]
.
- [`clandro-scoped-env-variable`]
- [`clandro-scoped-env-variable.sh.in`]
- [`clandro_core__sh__clandro_scoped_env_variable()`]

&nbsp;



#### Examples

The following examples assume that `clandro-apps-info-env-variable.sh` script has been sourced in the current shell (so that/or) the `clandro_core__sh__clandro_apps_info_env_variable` function is defined and can be called. If `clandro-apps-info-env-variable.sh` needs to be executed instead, then replace `clandro_core__sh__clandro_apps_info_env_variable` in the following examples with `clandro-apps-info-env-variable.sh` and the second argument for `output_mode` with the value `>` so that the output is printed to `stdout`.

```shell
source_file_from_path() { local source_file="${1:-}"; [ $# -gt 0 ] && shift 1; local source_path; if source_path="$(command -v "$source_file")" && [ -n "$source_path" ]; then . "$source_path" || return $?; else echo "Failed to find the '$source_file' file to source." 1>&2; return 1; fi; }

source_file_from_path "clandro-apps-info-env-variable.sh" --sourcing-script || exit $?
```

&nbsp;



##### Source Environment

Source the `clandro-apps-info.env` file into the current environment.

```shell
clandro_core__sh__clandro_apps_info_env_variable source-env || return $?
```

&nbsp;



##### `CLANDRO_APP__DATA_DIR`

Get `$CLANDRO_APP__DATA_DIR` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not a valid absolute path (excluding rootfs `/`), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$CLANDRO_APP__DATA_DIR` variable.

```shell
clandro_core__sh__clandro_apps_info_env_variable get-value CLANDRO_APP__DATA_DIR cn="clandro-app" "DATA_DIR" p+="/*[!/]" || return $?
```

Get `$CLANDRO_APP__DATA_DIR` variable value from the current environment if running under Clandro app, otherwise from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not a valid absolute path (excluding rootfs `/`), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$CLANDRO_APP__DATA_DIR` variable.

```shell
clandro_core__sh__clandro_apps_info_env_variable get-value --skip-sourcing-if-cur-app-var CLANDRO_APP__DATA_DIR cn="clandro-app" "DATA_DIR" p+="/*[!/]" || return $?
```

&nbsp;



##### `CLANDRO_APP__TARGET_SDK`

Get `$CLANDRO_APP__TARGET_SDK` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not an unsigned integer in the range `0-10000` (inclusive), then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$CLANDRO_APP__TARGET_SDK` variable.

```shell
is_valid_target_sdk() { case "${1:-}" in ''|*[!0-9]*|0[0-9]*) return 1;; esac; [ "$1" -le 10000 ]; }

clandro_core__sh__clandro_apps_info_env_variable get-value CLANDRO_APP__TARGET_SDK cn="clandro-app" "TARGET_SDK" c+='is_valid_target_sdk' || return $?
```

&nbsp;



##### Multiple Variable Read

Unset `$CLANDRO_APP__APK_FILE` and `$CLANDRO_APP__DATA_DIR` variables, then source the `clandro-apps-info.env` file to set their latest values into the current environment, then get their variable values without sourcing the file again.

```shell
clandro_core__sh__clandro_scoped_env_variable unset-value cn="clandro-app" "APK_FILE" || return $?
clandro_core__sh__clandro_scoped_env_variable unset-value cn="clandro-app" "DATA_DIR" || return $?
clandro_core__sh__clandro_apps_info_env_variable source-env || return $?
clandro_core__sh__clandro_apps_info_env_variable get-value --skip-sourcing CLANDRO_APP__APK_FILE cn="clandro-app" "APK_FILE" p+="/*[!/]" || return $?
clandro_core__sh__clandro_apps_info_env_variable get-value --skip-sourcing CLANDRO_APP__DATA_DIR cn="clandro-app" "DATA_DIR" p+="/*[!/]" || return $?
```

&nbsp;



##### External App

Get `$FOO_APP__UID` variable value from the `clandro-apps-info.env` file after sourcing it. If the environment variable is not set or is not an unsigned integer, then call will return with exit code `81` (`C_EX__NOT_FOUND`). The output will be set to the `$FOO_APP__UID` variable.

```shell
clandro_core__sh__clandro_apps_info_env_variable get-value FOO_APP__UID s="FOO_APP__" "UID" p-="''|*[!0-9]*|0[0-9]*" || return $?
```

---

&nbsp;





[`properties.sh`]: https://github.com/cl-andro/clandro-packages/blob/master/scripts/properties.sh
[`clandro-apps-info-env-variable.bash.in`]: https://github.com/cl-andro/clandro-core-package/blob/master/app/main/scripts/clandro/shell/command/environment/clandro-apps-info-env-variable.bash.in
[`clandro-apps-info-env-variable.sh.in`]: https://github.com/cl-andro/clandro-core-package/blob/master/app/main/scripts/clandro/shell/command/environment/clandro-apps-info-env-variable.sh.in
[`clandro-scoped-env-variable`]: clandro-scoped-env-variable.md
[`clandro-scoped-env-variable.bash.in`]: https://github.com/cl-andro/clandro-core-package/blob/master/app/main/scripts/clandro/shell/command/environment/clandro-scoped-env-variable.bash.in
[`clandro-scoped-env-variable.sh.in`]: https://github.com/cl-andro/clandro-core-package/blob/master/app/main/scripts/clandro/shell/command/environment/clandro-scoped-env-variable.sh.in
[`clandro_core__bash__clandro_apps_info_env_variable()`]: https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/app/main/scripts/clandro/shell/command/environment/clandro_core__bash__clandro_apps_info_env_variable
[`clandro_core__sh__clandro_apps_info_env_variable()`]: https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/app/main/scripts/clandro/shell/command/environment/clandro_core__sh__clandro_apps_info_env_variable
[`clandro_core__bash__clandro_scoped_env_variable()`]: https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/app/main/scripts/clandro/shell/command/environment/clandro_core__bash__clandro_scoped_env_variable
[`clandro_core__sh__clandro_scoped_env_variable()`]: https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/app/main/scripts/clandro/shell/command/environment/clandro_core__sh__clandro_scoped_env_variable
[`clandro-replace-clandro-core-src-scripts`]: https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/build/scripts/clandro-replace-clandro-core-src-scripts
