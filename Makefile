export CLANDRO_CORE_PKG__VERSION := 0.4.0
export CLANDRO_CORE_PKG__ARCH
export CLANDRO_CORE_PKG__INSTALL_PREFIX

export CLANDRO__NAME := Clandro# Default value: `Clandro`
export CLANDRO__LNAME := clandro# Default value: `clandro`

export CLANDRO__REPOS_HOST_ORG_NAME := clandro# Default value: `clandro`
export CLANDRO__REPOS_HOST_ORG_URL := https://github.com/$(CLANDRO__REPOS_HOST_ORG_NAME)# Default value: `https://github.com/clandro`

export CLANDRO_APP__NAME := Clandro# Default value: `Clandro`
export CLANDRO_APP__PACKAGE_NAME := com.clandro# Default value: `com.clandro`
export CLANDRO_APP__DATA_DIR := /data/data/$(CLANDRO_APP__PACKAGE_NAME)# Default value: `/data/data/com.clandro`

export CLANDRO__ROOTFS := $(CLANDRO_APP__DATA_DIR)/files# Default value: `/data/data/com.clandro/files`
export CLANDRO__HOME := $(CLANDRO__ROOTFS)/home# Default value: `/data/data/com.clandro/files/home`
export CLANDRO__PREFIX := $(CLANDRO__ROOTFS)/usr# Default value: `/data/data/com.clandro/files/usr`
export CLANDRO__PREFIX__BIN_DIR := $(CLANDRO__PREFIX)/bin# Default value: `/data/data/com.clandro/files/usr/bin`
export CLANDRO__PREFIX__INCLUDE_DIR := $(CLANDRO__PREFIX)/include# Default value: `/data/data/com.clandro/files/usr/include`
export CLANDRO__PREFIX__LIB_DIR := $(CLANDRO__PREFIX)/lib# Default value: `/data/data/com.clandro/files/usr/lib`
export CLANDRO__PREFIX__TMP_DIR := $(CLANDRO__PREFIX)/tmp# Default value: `/data/data/com.clandro/files/usr/tmp`

export CLANDRO_ENV__S_ROOT := CLANDRO_# Default value: `CLANDRO_`
export CLANDRO_ENV__SS_CLANDRO := _# Default value: `_`
export CLANDRO_ENV__S_CLANDRO := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO)# Default value: `CLANDRO__`
export CLANDRO_ENV__SS_CLANDRO_APP := APP__# Default value: `APP__`
export CLANDRO_ENV__S_CLANDRO_APP := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO_APP)# Default value: `CLANDRO_APP__`
export CLANDRO_ENV__SS_CLANDRO_API_APP := API_APP__# Default value: `API_APP__`
export CLANDRO_ENV__S_CLANDRO_API_APP := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO_API_APP)# Default value: `CLANDRO_API_APP__`
export CLANDRO_ENV__SS_CLANDRO_ROOTFS := ROOTFS__# Default value: `ROOTFS__`
export CLANDRO_ENV__S_CLANDRO_ROOTFS := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO_ROOTFS)# Default value: `CLANDRO_ROOTFS__`
export CLANDRO_ENV__SS_CLANDRO_CORE := CORE__# Default value: `CORE__`
export CLANDRO_ENV__S_CLANDRO_CORE := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO_CORE)# Default value: `CLANDRO_CORE__`
export CLANDRO_ENV__SS_CLANDRO_CORE__TESTS := CORE__TESTS__# Default value: `CORE__TESTS__`
export CLANDRO_ENV__S_CLANDRO_CORE__TESTS := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO_CORE__TESTS)# Default value: `CLANDRO_CORE__TESTS__`
export CLANDRO_ENV__SS_CLANDRO_EXEC__TESTS := EXEC__TESTS__# Default value: `EXEC__TESTS__`
export CLANDRO_ENV__S_CLANDRO_EXEC__TESTS := $(CLANDRO_ENV__S_ROOT)$(CLANDRO_ENV__SS_CLANDRO_EXEC__TESTS)# Default value: `CLANDRO_EXEC__TESTS__`

export CLANDRO_APP__NAMESPACE := $(CLANDRO_APP__PACKAGE_NAME)# Default value: `com.clandro`
export CLANDRO_APP__SHELL_API__SHELL_API_ACTIVITY__CLASS_NAME := $(CLANDRO_APP__NAMESPACE).app.ClandroActivity# Default value: `com.clandro.app.ClandroActivity`
export CLANDRO_APP__SHELL_API__SHELL_API_SERVICE__CLASS_NAME := $(CLANDRO_APP__NAMESPACE).app.ClandroService# Default value: `com.clandro.app.ClandroService`

export CLANDRO_PKGS__REPO_NAME := clandro-packages# Default value: `clandro-packages`
export CLANDRO_PKGS__REPO_URL := $(CLANDRO__REPOS_HOST_ORG_URL)/$(CLANDRO_PKGS__REPO_NAME)# Default value: `https://github.com/cl-andro/clandro-packages`
export CLANDRO_PKGS__BUILD__REPO_ROOT_DIR

export CLANDRO_CORE_PKG__REPO_NAME := clandro-core-package# Default value: `clandro-core-package`
export CLANDRO_CORE_PKG__REPO_URL := $(CLANDRO__REPOS_HOST_ORG_URL)/$(CLANDRO_CORE_PKG__REPO_NAME)# Default value: `https://github.com/cl-andro/clandro-core-package`
export CLANDRO_CORE__CLANDRO_REPLACE_CLANDRO_CORE_SRC_SCRIPTS_FILE := $(CLANDRO_PKGS__BUILD__REPO_ROOT_DIR)/packages/clandro-core/build/scripts/clandro-replace-clandro-core-src-scripts



# Check if CLANDRO_PKGS__BUILD__REPO_ROOT_DIR and CLANDRO_CORE__CLANDRO_REPLACE_CLANDRO_CORE_SRC_SCRIPTS_FILE are set and exist
ifeq ($(CLANDRO_PKGS__BUILD__REPO_ROOT_DIR),)
    $(error The CLANDRO_PKGS__BUILD__REPO_ROOT_DIR variable is not set)
else ifneq ($(patsubst /%,,$(CLANDRO_PKGS__BUILD__REPO_ROOT_DIR)),)
    $(error The CLANDRO_PKGS__BUILD__REPO_ROOT_DIR variable '$(CLANDRO_PKGS__BUILD__REPO_ROOT_DIR)' is not set to an absolute path)
else ifneq ($(shell test -d "$(CLANDRO_PKGS__BUILD__REPO_ROOT_DIR)" && echo 1 || echo 0), 1)
    $(error The clandro-pacakges build repo directory does not exist at CLANDRO_PKGS__BUILD__REPO_ROOT_DIR '$(CLANDRO_PKGS__BUILD__REPO_ROOT_DIR)' path)
else ifneq ($(shell test -f "$(CLANDRO_CORE__CLANDRO_REPLACE_CLANDRO_CORE_SRC_SCRIPTS_FILE)" && echo 1 || echo 0), 1)
    $(error The 'replace-clandro-core-src-scripts' file does not exist at CLANDRO_CORE__CLANDRO_REPLACE_CLANDRO_CORE_SRC_SCRIPTS_FILE '$(CLANDRO_CORE__CLANDRO_REPLACE_CLANDRO_CORE_SRC_SCRIPTS_FILE)' path)
endif



# If architecture not set, find it for the compiler based on which
# predefined architecture macro is defined. The `shell` function
# replaces newlines with a space and a literal space cannot be entered
# in a makefile as its used as a splitter, hence $(SPACE) variable is
# created and used for matching.
ifeq ($(CLANDRO_CORE_PKG__ARCH),)
	export override PREDEFINED_MACROS := $(shell $(CC) -x c /dev/null -dM -E)
	override EMPTY :=
	override SPACE := $(EMPTY) $(EMPTY)
	ifneq (,$(findstring $(SPACE)#define __i686__ 1$(SPACE),$(SPACE)$(PREDEFINED_MACROS)$(SPACE)))
		override CLANDRO_CORE_PKG__ARCH := i686
	else ifneq (,$(findstring $(SPACE)#define __x86_64__ 1$(SPACE),$(SPACE)$(PREDEFINED_MACROS)$(SPACE)))
		override CLANDRO_CORE_PKG__ARCH := x86_64
	else ifneq (,$(findstring $(SPACE)#define __aarch64__ 1$(SPACE),$(SPACE)$(PREDEFINED_MACROS)$(SPACE)))
		override CLANDRO_CORE_PKG__ARCH := aarch64
	else ifneq (,$(findstring $(SPACE)#define __arm__ 1$(SPACE),$(SPACE)$(PREDEFINED_MACROS)$(SPACE)))
		override CLANDRO_CORE_PKG__ARCH := arm
	else ifneq (,$(findstring $(SPACE)#define __riscv 1$(SPACE),$(SPACE)$(PREDEFINED_MACROS)$(SPACE)))
		override CLANDRO_CORE_PKG__ARCH := riscv64
	else
        $(error Unsupported package arch)
	endif
endif


export override IS_ON_DEVICE_BUILD := $(shell test -f "/system/bin/app_process" && echo 1 || echo 0)



export override BUILD_DIR := build# Default value: `build`

export override BUILD_OUTPUT_DIR := $(BUILD_DIR)/output# Default value: `build/output`

export override TMP_BUILD_OUTPUT_DIR := $(BUILD_OUTPUT_DIR)/tmp# Default value: `build/output/tmp`

export override PREFIX_BUILD_OUTPUT_DIR := $(BUILD_OUTPUT_DIR)/usr# Default value: `build/output/usr`
export override BIN_BUILD_OUTPUT_DIR := $(PREFIX_BUILD_OUTPUT_DIR)/bin# Default value: `build/output/usr/bin`
export override LIB_BUILD_OUTPUT_DIR := $(PREFIX_BUILD_OUTPUT_DIR)/lib# Default value: `build/output/usr/lib`
export override LIBEXEC_BUILD_OUTPUT_DIR := $(PREFIX_BUILD_OUTPUT_DIR)/libexec# Default value: `build/output/usr/libexec`
export override TESTS_BUILD_OUTPUT_DIR := $(LIBEXEC_BUILD_OUTPUT_DIR)/installed-tests/clandro-core# Default value: `build/output/usr/libexec/installed-tests/clandro-core`

export override PACKAGING_BUILD_OUTPUT_DIR := $(BUILD_OUTPUT_DIR)/packaging# Default value: `build/output/packaging`
export override DEBIAN_PACKAGING_BUILD_OUTPUT_DIR := $(PACKAGING_BUILD_OUTPUT_DIR)/debian# Default value: `build/output/packaging/debian`



export override BUILD_INSTALL_DIR := $(BUILD_DIR)/install# Default value: `build/install`
export override PREFIX_BUILD_INSTALL_DIR := $(BUILD_INSTALL_DIR)/usr# Default value: `build/install/usr`

ifeq ($(CLANDRO_CORE_PKG__INSTALL_PREFIX),)
	ifeq ($(DESTDIR)$(PREFIX),)
		override CLANDRO_CORE_PKG__INSTALL_PREFIX := $(CLANDRO__PREFIX)
	else
		override CLANDRO_CORE_PKG__INSTALL_PREFIX := $(DESTDIR)$(PREFIX)
	endif
endif
export CLANDRO_CORE_PKG__INSTALL_PREFIX



# Escape `&`, `\` and `/` characters to be used as replacement string
# in sed `s/regexp/replacement/` expression.
# The `\` character needs to be escaped twice since used in command
# string with double quoted arguments, which are then passed to `sh`
# as a single quoted argument.
# - https://stackoverflow.com/a/29613573/14686958
export override CLANDRO_PKGS__REPO_URL__ESCAPED := $(shell printf '%s' "$(CLANDRO_PKGS__REPO_URL)" | sed -e '$$!{:a;N;$$!ba;}; s/[\]/\\\\&/g; s/[&/]/\\&/g; s/\n/\\&/g')
export override CLANDRO_CORE_PKG__REPO_URL__ESCAPED := $(shell printf '%s' "$(CLANDRO_CORE_PKG__REPO_URL)" | sed -e '$$!{:a;N;$$!ba;}; s/[\]/\\\\&/g; s/[&/]/\\&/g; s/\n/\\&/g')


export override CLANDRO__CONSTANTS__MACRO_FLAGS := \
	-DCLANDRO_CORE_PKG__VERSION=\"$(CLANDRO_CORE_PKG__VERSION)\" \
	-DCLANDRO__NAME=\"$(CLANDRO__NAME)\" \
	-DCLANDRO__LNAME=\"$(CLANDRO__LNAME)\" \
	-DCLANDRO__REPOS_HOST_ORG_NAME=\"$(CLANDRO__REPOS_HOST_ORG_NAME)\" \
	-DCLANDRO_APP__DATA_DIR=\"$(CLANDRO_APP__DATA_DIR)\" \
	-DCLANDRO__ROOTFS=\"$(CLANDRO__ROOTFS)\" \
	-DCLANDRO__PREFIX=\"$(CLANDRO__PREFIX)\" \
	-DCLANDRO__PREFIX__BIN_DIR=\"$(CLANDRO__PREFIX__BIN_DIR)\" \
	-DCLANDRO__PREFIX__TMP_DIR=\"$(CLANDRO__PREFIX__TMP_DIR)\" \
	-DCLANDRO_ENV__S_CLANDRO=\"$(CLANDRO_ENV__S_CLANDRO)\" \
	-DCLANDRO_ENV__S_CLANDRO_APP=\"$(CLANDRO_ENV__S_CLANDRO_APP)\" \
	-DCLANDRO_ENV__S_CLANDRO_ROOTFS=\"$(CLANDRO_ENV__S_CLANDRO_ROOTFS)\" \
	-DCLANDRO_ENV__S_CLANDRO_CORE__TESTS=\"$(CLANDRO_ENV__S_CLANDRO_CORE__TESTS)\"

export override CLANDRO__CONSTANTS__SED_ARGS := \
	-e "s%[@]CLANDRO_CORE_PKG__VERSION[@]%$(CLANDRO_CORE_PKG__VERSION)%g" \
	-e "s%[@]CLANDRO_CORE_PKG__ARCH[@]%$(CLANDRO_CORE_PKG__ARCH)%g" \
	-e "s%[@]CLANDRO__LNAME[@]%$(CLANDRO__LNAME)%g" \
	-e "s%[@]CLANDRO__REPOS_HOST_ORG_NAME[@]%$(CLANDRO__REPOS_HOST_ORG_NAME)%g" \
	-e "s%[@]CLANDRO_APP__NAME[@]%$(CLANDRO_APP__NAME)%g" \
	-e "s%[@]CLANDRO_APP__PACKAGE_NAME[@]%$(CLANDRO_APP__PACKAGE_NAME)%g" \
	-e "s%[@]CLANDRO_APP__DATA_DIR[@]%$(CLANDRO_APP__DATA_DIR)%g" \
	-e "s%[@]CLANDRO__ROOTFS[@]%$(CLANDRO__ROOTFS)%g" \
	-e "s%[@]CLANDRO__HOME[@]%$(CLANDRO__HOME)%g" \
	-e "s%[@]CLANDRO__PREFIX[@]%$(CLANDRO__PREFIX)%g" \
	-e "s%[@]CLANDRO_ENV__S_ROOT[@]%$(CLANDRO_ENV__S_ROOT)%g" \
	-e "s%[@]CLANDRO_ENV__S_CLANDRO[@]%$(CLANDRO_ENV__S_CLANDRO)%g" \
	-e "s%[@]CLANDRO_ENV__S_CLANDRO_APP[@]%$(CLANDRO_ENV__S_CLANDRO_APP)%g" \
	-e "s%[@]CLANDRO_ENV__S_CLANDRO_API_APP[@]%$(CLANDRO_ENV__S_CLANDRO_API_APP)%g" \
	-e "s%[@]CLANDRO_ENV__S_CLANDRO_CORE[@]%$(CLANDRO_ENV__S_CLANDRO_CORE)%g" \
	-e "s%[@]CLANDRO_ENV__S_CLANDRO_CORE__TESTS[@]%$(CLANDRO_ENV__S_CLANDRO_CORE__TESTS)%g" \
	-e "s%[@]CLANDRO_ENV__S_CLANDRO_EXEC__TESTS[@]%$(CLANDRO_ENV__S_CLANDRO_EXEC__TESTS)%g" \
	-e "s%[@]CLANDRO_APP__NAMESPACE[@]%$(CLANDRO_APP__NAMESPACE)%g" \
	-e "s%[@]CLANDRO_APP__SHELL_API__SHELL_API_ACTIVITY__CLASS_NAME[@]%$(CLANDRO_APP__SHELL_API__SHELL_API_ACTIVITY__CLASS_NAME)%g" \
	-e "s%[@]CLANDRO_APP__SHELL_API__SHELL_API_SERVICE__CLASS_NAME[@]%$(CLANDRO_APP__SHELL_API__SHELL_API_SERVICE__CLASS_NAME)%g" \
	-e "s%[@]CLANDRO_PKGS__REPO_URL[@]%$(CLANDRO_PKGS__REPO_URL__ESCAPED)%g" \
	-e "s%[@]CLANDRO_CORE_PKG__REPO_URL[@]%$(CLANDRO_CORE_PKG__REPO_URL__ESCAPED)%g"

define replace-clandro-constants
	sed $(CLANDRO__CONSTANTS__SED_ARGS) "$1.in" > "$2/$$(basename "$1")"
endef



export override CFLAGS_DEFAULT :=
export override CPPFLAGS_DEFAULT :=
export override LDFLAGS_DEFAULT :=

override CPPFLAGS_DEFAULT += -isystem$(CLANDRO__PREFIX__INCLUDE_DIR)
override LDFLAGS_DEFAULT += -L$(CLANDRO__PREFIX__LIB_DIR)

ifeq ($(CLANDRO_CORE_PKG__ARCH),arm)
	# "We recommend using the -mthumb compiler flag to force the generation of 16-bit Thumb-2 instructions".
	# - https://developer.android.com/ndk/guides/standalone_toolchain.html#abi_compatibility
	override CFLAGS_DEFAULT += -march=armv7-a -mfpu=neon -mfloat-abi=softfp -mthumb
	override LDFLAGS_DEFAULT += -march=armv7-a
else ifeq ($(CLANDRO_CORE_PKG__ARCH),i686)
	# From $NDK/docs/CPU-ARCH-ABIS.html:
	override CFLAGS_DEFAULT += -march=i686 -msse3 -mstackrealign -mfpmath=sse
	# i686 seem to explicitly require '-fPIC'.
	# - https://github.com/cl-andro/clandro-packages/issues/7215#issuecomment-906154438
	override CFLAGS_DEFAULT += -fPIC
endif

# - https://github.com/cl-andro/clandro-packages/commit/b997c4ea
ifeq ($(IS_ON_DEVICE_BUILD), 0)
	override LDFLAGS_DEFAULT += -Wl,-rpath=$(CLANDRO__PREFIX__LIB_DIR)
endif

# Android 7 started to support DT_RUNPATH (but not DT_RPATH).
override LDFLAGS_DEFAULT += -Wl,--enable-new-dtags

# Avoid linking extra (unneeded) libraries.
override LDFLAGS_DEFAULT += -Wl,--as-needed

# Basic hardening.
override LDFLAGS_DEFAULT += -Wl,-z,relro,-z,now


# Set default flags if building with make directly without clandro-pacakges build infrastructure.
CFLAGS ?= $(CFLAGS_DEFAULT)
CXXFLAGS ?= $(CFLAGS_DEFAULT)
CPPFLAGS ?= $(CPPFLAGS_DEFAULT)
LDFLAGS ?= $(LDFLAGS_DEFAULT)

# Force optimize for speed and do basic hardening.
export override CFLAGS_FORCE := -Wall -Wextra -Werror -Wshadow -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-strong

CFLAGS += $(CFLAGS_FORCE)
CXXFLAGS += $(CFLAGS_FORCE)

FSANTIZE_FLAGS += -fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer



override LIBCLANDRO_CORE__NOS__C__SOURCE_FILES := \
	lib/clandro-core_nos_c/tre/src/android/shell/command/environment/AndroidShellEnvironment.c \
	lib/clandro-core_nos_c/tre/src/ClandroCoreLibraryConfig.c \
	lib/clandro-core_nos_c/tre/src/data/AssertUtils.c \
	lib/clandro-core_nos_c/tre/src/data/DataUtils.c \
	lib/clandro-core_nos_c/tre/src/logger/FileLoggerImpl.c \
	lib/clandro-core_nos_c/tre/src/logger/Logger.c \
	lib/clandro-core_nos_c/tre/src/logger/StandardLoggerImpl.c \
	lib/clandro-core_nos_c/tre/src/security/SecurityUtils.c \
	lib/clandro-core_nos_c/tre/src/clandro/file/ClandroFile.c \
	lib/clandro-core_nos_c/tre/src/clandro/shell/command/environment/ClandroShellEnvironment.c \
	lib/clandro-core_nos_c/tre/src/clandro/shell/command/environment/clandro_core/ClandroCoreShellEnvironment.c \
	lib/clandro-core_nos_c/tre/src/unix/file/UnixFileUtils.c \
	lib/clandro-core_nos_c/tre/src/unix/os/process/UnixForkUtils.c \
	lib/clandro-core_nos_c/tre/src/unix/os/process/UnixSafeStrerror.c \
	lib/clandro-core_nos_c/tre/src/unix/os/process/UnixSignalUtils.c \
	lib/clandro-core_nos_c/tre/src/unix/os/selinux/UnixSeLinuxUtils.c \
	lib/clandro-core_nos_c/tre/src/unix/shell/command/environment/UnixShellEnvironment.c

override LIBCLANDRO_CORE__NOS__C__OBJECT_FILES := $(patsubst lib/%.c,$(TMP_BUILD_OUTPUT_DIR)/lib/%.o,$(LIBCLANDRO_CORE__NOS__C__SOURCE_FILES))

override LIBCLANDRO_CORE__NOS__C__CPPFLAGS := $(CPPFLAGS) -I "lib/clandro-core_nos_c/tre/include"

override LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR := $(TESTS_BUILD_OUTPUT_DIR)/lib/clandro-core_nos_c/tre



override LIBCLANDRO_CORE__NOS__CXX__SOURCE_FILES := \
	lib/clandro-core_nos_cxx/tre/src/ClandroCoreLibraryConfig.cxx

override LIBCLANDRO_CORE__NOS__CXX__OBJECT_FILES := $(patsubst lib/%.cxx,$(TMP_BUILD_OUTPUT_DIR)/lib/%.o,$(LIBCLANDRO_CORE__NOS__CXX__SOURCE_FILES))

override LIBCLANDRO_CORE__NOS__CXX__CPPFLAGS := $(CPPFLAGS) -I "lib/clandro-core_nos_c/tre/include" -I "lib/clandro-core_nos_cxx/tre/include"



override CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR := $(TESTS_BUILD_OUTPUT_DIR)/app/main



# The `-L` flag must come before `$LDFLAGS`, otherwise old library
# installed in system library directory from previous builds
# will get used instead of newly built one in `$LIB_BUILD_OUTPUT_DIR`.
# The `-fvisibility=hidden` flag is passed so that no internal
# functions are exported. All exported functions must explicitly enable
# `default` visibility with `__attribute__((visibility("default")))`,
# like for the `main()` function.
# The `-Wl,--exclude-libs=ALL` flag is passed so that symbols from
# the `libclandro-core_nos_c_tre.a` static library linked are not exported.
# Run `nm --demangle --defined-only --extern-only <executable>` to
# find exported symbols.
override CLANDRO_CORE_EXECUTABLE__C__BUILD_COMMAND := \
	$(CC) $(CFLAGS) $(LIBCLANDRO_CORE__NOS__C__CPPFLAGS) \
	-L$(LIB_BUILD_OUTPUT_DIR) $(LDFLAGS) -Wl,--exclude-libs=ALL \
	$(CLANDRO__CONSTANTS__MACRO_FLAGS) \
	-fPIE -pie -fvisibility=hidden

# The `-l` flags must be passed after object files for proper linking.
# The order of libraries matters too and any dependencies of a library
# must come after it.
override CLANDRO_CORE_EXECUTABLE__C__POST_LDFLAGS := -l:libclandro-core_nos_c_tre.a



# - https://www.gnu.org/software/make/manual/html_node/Parallel-Disable.html
.NOTPARALLEL:

all: | pre-build build-clandro-core-main-app build-libclandro-core_nos_c_tre build-libclandro-core_nos_cxx_tre
	@printf "\nclandro-core-package: %s\n" "Building packaging/debian/*"
	@mkdir -p $(DEBIAN_PACKAGING_BUILD_OUTPUT_DIR)
	find packaging/debian -mindepth 1 -maxdepth 1 -type f -name "*.in" -exec sh -c \
		'sed $(CLANDRO__CONSTANTS__SED_ARGS) "$$1" > $(DEBIAN_PACKAGING_BUILD_OUTPUT_DIR)/"$$(basename "$$1" | sed "s/\.in$$//")"' sh "{}" \;
	find $(DEBIAN_PACKAGING_BUILD_OUTPUT_DIR) -mindepth 1 -maxdepth 1 -type f \
		-regextype posix-extended -regex "^.*/(postinst|postrm|preinst|prerm)$$" \
		-exec chmod 700 {} \;
	find $(DEBIAN_PACKAGING_BUILD_OUTPUT_DIR) -mindepth 1 -maxdepth 1 -type f \
		-regextype posix-extended -regex "^.*/(config|conffiles|templates|triggers|clilibs|fortran_mod|runit|shlibs|starlibs|symbols)$$" \
		-exec chmod 600 {} \;


	@printf "\nclandro-core-package: %s\n\n" "Build clandro-core-package successful"

pre-build: | clean
	@printf "clandro-core-package: %s\n" "Building clandro-core-package"
	@mkdir -p $(BUILD_OUTPUT_DIR)
	@mkdir -p $(TMP_BUILD_OUTPUT_DIR)

build-clandro-core-main-app:
	@printf "\nclandro-core-package: %s\n" "Building app/main"

	@printf "\nclandro-core-package: %s\n" "Building app/main/scripts/*"
	@mkdir -p $(BIN_BUILD_OUTPUT_DIR)
	find app/main/scripts -type f -name "*.in" -exec sh -c \
		'sed $(CLANDRO__CONSTANTS__SED_ARGS) "$$1" > $(BIN_BUILD_OUTPUT_DIR)/"$$(basename "$$1" | sed "s/\.in$$//")"' sh "{}" \;
	find $(BIN_BUILD_OUTPUT_DIR) -maxdepth 1 -type f -exec chmod 700 "{}" \;
	find app/main/scripts -type l -exec cp -a "{}" $(BIN_BUILD_OUTPUT_DIR)/ \;
	"$(CLANDRO_CORE__CLANDRO_REPLACE_CLANDRO_CORE_SRC_SCRIPTS_FILE)" $(BIN_BUILD_OUTPUT_DIR)/*


	@printf "\nclandro-core-package: %s\n" "Building app/main/tests/*"
	@mkdir -p $(CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR)
	find app/main/tests -maxdepth 1 -type f -name "*.in" -print0 | xargs -0 -n1 sh -c \
		'output_file="$(CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR)/$$(printf "%s" "$$0" | sed -e "s|^app/main/tests/||" -e "s/\.in$$//")" && mkdir -p "$$(dirname "$$output_file")" && sed $(CLANDRO__CONSTANTS__SED_ARGS) "$$0" > "$$output_file"'
	find $(CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR) -maxdepth 1 -type f -exec chmod 700 "{}" \;

	@printf "\nclandro-core-package: %s\n" "Building app/main/tests/scripts/*"
	@mkdir -p $(CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR)/scripts
	find app/main/tests/scripts -type f -name "*.in" -print0 | xargs -0 -n1 sh -c \
		'output_file="$(CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR)/scripts/$$(printf "%s" "$$0" | sed -e "s|^app/main/tests/scripts/||" -e "s/\.in$$//")" && mkdir -p "$$(dirname "$$output_file")" && sed $(CLANDRO__CONSTANTS__SED_ARGS) "$$0" > "$$output_file"'
	find $(CLANDRO_CORE__MAIN_APP__TESTS_BUILD_OUTPUT_DIR)/scripts -type f -exec chmod 700 "{}" \;

build-libclandro-core_nos_c_tre:
	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_c/tre"
	@mkdir -p $(LIB_BUILD_OUTPUT_DIR)

	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_c/tre/lib/*.o"
	for source_file in $(LIBCLANDRO_CORE__NOS__C__SOURCE_FILES); do \
		mkdir -p "$$(dirname "$(TMP_BUILD_OUTPUT_DIR)/$$source_file")" || exit $$?; \
		$(CC) -c $(CFLAGS) $(LIBCLANDRO_CORE__NOS__C__CPPFLAGS) \
			$(CLANDRO__CONSTANTS__MACRO_FLAGS) \
			-fPIC -fvisibility=default \
			-o $(TMP_BUILD_OUTPUT_DIR)/"$$(echo "$$source_file" | sed -E "s/(.*)\.c$$/\1.o/")" \
			"$$source_file" || exit $$?; \
	done

	@# `nm --demangle --dynamic --defined-only --extern-only /home/builder/.clandro-build/clandro-core/src/build/output/usr/lib/libclandro-core_nos_c_tre.so`
	@printf "\nclandro-core-package: %s\n" "Building lib/libclandro-core_nos_c_tre.so"
	$(CC) $(CFLAGS) $(LIBCLANDRO_CORE__NOS__C__CPPFLAGS) \
		$(LDFLAGS) \
		$(CLANDRO__CONSTANTS__MACRO_FLAGS) \
		-fPIC -shared -fvisibility=default \
		-o $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_c_tre.so \
		$(LIBCLANDRO_CORE__NOS__C__OBJECT_FILES)

	@printf "\nclandro-core-package: %s\n" "Building lib/libclandro-core_nos_c_tre.a"
	$(AR) rcs $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_c_tre.a $(LIBCLANDRO_CORE__NOS__C__OBJECT_FILES)



	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_c/tre/tests/*"
	@mkdir -p $(LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR)


	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_c/tre/tests/libclandro-core_nos_c_tre_tests"
	$(call replace-clandro-constants,lib/clandro-core_nos_c/tre/tests/libclandro-core_nos_c_tre_tests,$(LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR))
	chmod 700 $(LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR)/libclandro-core_nos_c_tre_tests


	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_c/tre/tests/bin/libclandro-core_nos_c_tre_unit-binary-tests"
	@mkdir -p $(LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR)/bin

	@# `nm --demangle --defined-only --extern-only /home/builder/.clandro-build/clandro-core/src/build/output/usr/libexec/installed-tests/clandro-core/lib/clandro-core_nos_c/tre/bin/libclandro-core_nos_c_tre_unit-binary-tests-fsanitize`
	$(CLANDRO_CORE_EXECUTABLE__C__BUILD_COMMAND) -O0 -g \
		$(FSANTIZE_FLAGS) \
		-o $(LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR)/bin/libclandro-core_nos_c_tre_unit-binary-tests-fsanitize \
		lib/clandro-core_nos_c/tre/tests/src/libclandro-core_nos_c_tre_unit-binary-tests.c \
		$(CLANDRO_CORE_EXECUTABLE__C__POST_LDFLAGS)

	@# `nm --demangle --defined-only --extern-only /home/builder/.clandro-build/clandro-core/src/build/output/usr/libexec/installed-tests/clandro-core/lib/clandro-core_nos_c/tre/bin/libclandro-core_nos_c_tre_unit-binary-tests-nofsanitize`
	$(CLANDRO_CORE_EXECUTABLE__C__BUILD_COMMAND) -O0 -g \
		-o $(LIBCLANDRO_CORE__NOS__C__TESTS_BUILD_OUTPUT_DIR)/bin/libclandro-core_nos_c_tre_unit-binary-tests-nofsanitize \
		lib/clandro-core_nos_c/tre/tests/src/libclandro-core_nos_c_tre_unit-binary-tests.c \
		$(CLANDRO_CORE_EXECUTABLE__C__POST_LDFLAGS)

build-libclandro-core_nos_cxx_tre:
	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_cxx/tre"
	@mkdir -p $(LIB_BUILD_OUTPUT_DIR)

	@printf "\nclandro-core-package: %s\n" "Building lib/clandro-core_nos_cxx/tre/lib/*.o"
	for source_file in $(LIBCLANDRO_CORE__NOS__CXX__SOURCE_FILES); do \
		mkdir -p "$$(dirname "$(TMP_BUILD_OUTPUT_DIR)/$$source_file")" || exit $$?; \
		$(CXX) -c $(CXXFLAGS) $(LIBCLANDRO_CORE__NOS__CXX__CPPFLAGS) \
			$(CLANDRO__CONSTANTS__MACRO_FLAGS) \
			-fPIC -fvisibility=default \
			-o $(TMP_BUILD_OUTPUT_DIR)/"$$(echo "$$source_file" | sed -E "s/(.*)\.cxx$$/\1.o/")" \
			"$$source_file" || exit $$?; \
	done

	@# `nm --demangle --dynamic --defined-only --extern-only /home/builder/.clandro-build/clandro-core/src/build/output/usr/lib/libclandro-core_nos_cxx_tre.so`
	@printf "\nclandro-core-package: %s\n" "Building lib/libclandro-core_nos_cxx_tre.so"
	$(CXX) $(CXXFLAGS) $(LIBCLANDRO_CORE__NOS__CXX__CPPFLAGS) \
		-L$(LIB_BUILD_OUTPUT_DIR) $(LDFLAGS) -Wl,--exclude-libs=ALL \
		$(CLANDRO__CONSTANTS__MACRO_FLAGS) \
		-fPIC -shared -fvisibility=default \
		-o $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_cxx_tre.so \
		$(LIBCLANDRO_CORE__NOS__CXX__OBJECT_FILES) \
		-l:libclandro-core_nos_c_tre.a

	@printf "\nclandro-core-package: %s\n" "Building lib/libclandro-core_nos_cxx_tre.a"
	$(AR) rcs $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_cxx_tre.a $(LIBCLANDRO_CORE__NOS__CXX__OBJECT_FILES)



clean:
	rm -rf $(BUILD_OUTPUT_DIR)

install:
	@printf "clandro-core-package: %s\n" "Installing clandro-core-package in $(CLANDRO_CORE_PKG__INSTALL_PREFIX)"
	install -d $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/bin
	install -d $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include
	install -d $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib
	install -d $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/libexec


	find $(BIN_BUILD_OUTPUT_DIR) -maxdepth 1 \( -type f -o -type l \) -exec cp -a "{}" $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/bin/ \;


	rm -rf $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core
	install -d $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core/clandro

	cp -a lib/clandro-core_nos_c/tre/include/clandro/clandro_core__nos__c $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core/clandro/clandro_core__nos__c
	install $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_c_tre.so $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_c_tre.so
	install $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_c_tre.a $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_c_tre.a

	cp -a lib/clandro-core_nos_cxx/tre/include/clandro/clandro_core__nos__cxx $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core/clandro/clandro_core__nos__cxx
	install $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_cxx_tre.so $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_cxx_tre.so
	install $(LIB_BUILD_OUTPUT_DIR)/libclandro-core_nos_cxx_tre.a $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_cxx_tre.a

	find $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core -type d -exec chmod 700 {} \;
	find $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core -type f -exec chmod 600 {} \;


	rm -rf $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/libexec/installed-tests/clandro-core
	install -d $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/libexec/installed-tests
	cp -a $(TESTS_BUILD_OUTPUT_DIR) $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/libexec/installed-tests/clandro-core

	@printf "\nclandro-core-package: %s\n\n" "Install clandro-core-package successful"

uninstall:
	@printf "clandro-core-package: %s\n" "Uninstalling clandro-core-package from $(CLANDRO_CORE_PKG__INSTALL_PREFIX)"

	find app/main/scripts \( -type f -o -type l \) -exec sh -c \
		'rm -f "$(CLANDRO_CORE_PKG__INSTALL_PREFIX)/bin/$$(basename "$$1" | sed "s/\.in$$//")"' sh "{}" \;

	rm -rf $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/include/clandro-core


	rm -f $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_c_tre.so
	rm -f $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_c_tre.a

	rm -f $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_cxx_tre.so
	rm -f $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/lib/libclandro-core_nos_cxx_tre.a


	rm -rf $(CLANDRO_CORE_PKG__INSTALL_PREFIX)/libexec/installed-tests/clandro-core

	@printf "\nclandro-core-package: %s\n\n" "Uninstall clandro-core-package successful"



packaging-debian-build: all
	clandro-create-package $(DEBIAN_PACKAGING_BUILD_OUTPUT_DIR)/clandro-core-package.json



test: all
	$(MAKE) CLANDRO_CORE_PKG__INSTALL_PREFIX=$(PREFIX_BUILD_INSTALL_DIR) install

	@printf "\nclandro-core-package: %s\n" "Executing clandro-core-package tests"
	bash $(PREFIX_BUILD_INSTALL_DIR)/libexec/installed-tests/clandro-core/app/main/clandro-core-tests \
		--tests-path="$(PREFIX_BUILD_INSTALL_DIR)/libexec/installed-tests/clandro-core" \
		--only-clandro-core-tests \
		-vvv all

test-unit: all
	$(MAKE) CLANDRO_CORE_PKG__INSTALL_PREFIX=$(PREFIX_BUILD_INSTALL_DIR) install

	@printf "\nclandro-core-package: %s\n" "Executing clandro-core-package unit tests"
	bash $(PREFIX_BUILD_INSTALL_DIR)/libexec/installed-tests/clandro-core/app/main/clandro-core-tests \
		--tests-path="$(PREFIX_BUILD_INSTALL_DIR)/libexec/installed-tests/clandro-core" \
		--only-clandro-core-tests \
		-vvv unit

test-runtime: all
	$(MAKE) CLANDRO_CORE_PKG__INSTALL_PREFIX=$(PREFIX_BUILD_INSTALL_DIR) install

	@printf "\nclandro-core-package: %s\n" "Executing clandro-core-package runtime tests"
	bash $(PREFIX_BUILD_INSTALL_DIR)/libexec/installed-tests/clandro-core/app/main/clandro-core-tests \
		--tests-path="$(PREFIX_BUILD_INSTALL_DIR)/libexec/installed-tests/clandro-core" \
		--only-clandro-core-tests \
		-vvv runtime



.PHONY: all pre-build build-clandro-core-main-app build-libclandro-core_nos_c_tre build-libclandro-core_nos_cxx_tre clean install uninstall packaging-debian-build test test-unit test-runtime
