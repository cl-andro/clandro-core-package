---
page_ref: "@ARK_PROJECT__VARIANT@/clandro/clandro-core-package/docs/@ARK_DOC__VERSION@/developer/build/index.md"
---

# clandro-core-package Build Docs

<!-- @ARK_DOCS__HEADER_PLACEHOLDER@ -->

The [`clandro-core`](https://github.com/cl-andro/clandro-core-package) package build instructions are available below. For install instructions, check [`install`](../../install/index.md) docs.

### Contents

- [Build Methods](#build-methods)

---

&nbsp;





## Build Methods

The `clandro-core` package provided by Clandro is built from the [`clandro/clandro-core-package`](https://github.com/cl-andro/clandro-core-package) repository. It can be built with the following methods.

- [Clandro Packages Build Infrastructure](#clandro-packages-build-infrastructure)
- [On Device With `make`](#on-device-with-make)

**The [Clandro Packages Build Infrastructure](#clandro-packages-build-infrastructure) is the recommended way to build `clandro-core`.** If the `clandro-core` package is built with the [Clandro Packages Build Infrastructure](#clandro-packages-build-infrastructure), then the Clandro variable values in the `Makefile` are dynamically set to the values defined in the [`properties.sh`] file of the build infrastructure by passing them to `make` via the `$CLANDRO_PKG_EXTRA_MAKE_ARGS` variable set in the [`packages/clandro-core/build.sh`] file. If `clandro-core` is built with `make` instead, then the hardcoded fallback/default Clandro variable values in the `Makefile` will get used during build time, which may affect or break `clandro-core` at runtime if current app/environment is different from the Clandro default one (`CLANDRO_APP__PACKAGE_NAME=com.clandro` and `CLANDRO__ROOTFS=/data/data/com.clandro/files`). However, if `make` must be used for some reason, and building for a different app/environment than the Clandro default, like for a Clandro fork or alternate package name/rootfs, then manually update the hardcoded values in the `Makefile` or manually pass the alternate values to the `make` command.

## &nbsp;

&nbsp;



### Clandro Packages Infrastructure

To build the `clandro-core` package with the [`clandro-packages`](https://github.com/cl-andro/clandro-packages) build infrastructure, the provided [`build-package.sh`](https://github.com/cl-andro/clandro-packages/blob/master/build-package.sh) script can be used. Check the [Build environment](https://github.com/cl-andro/clandro-packages/wiki/Build-environment) and [Building packages](https://github.com/cl-andro/clandro-packages/wiki/Building-packages) docs for how to build packages.

#### Default Sources

To build the `clandro-core` package from its default repository release tag or git branch sources that are used for building the package provided in Clandro repositories, just clone the `clandro-packages` repository and build.

```shell
# Clone `clandro-packages` repo and switch current working directory to it.
git clone https://github.com/cl-andro/clandro-packages.git
cd clandro-packages

# (OPTIONAL) Run clandro-packages docker container if running off-device.
./scripts/run-docker.sh

# Force build package and download dependencies from Clandro packages repositories.
./build-package.sh -f -I clandro-core
```

#### Local Sources

To build the `clandro-core` package from its local sources or a pull request branch, clone the `clandro-packages` repository, clone/create the `clandro-core-package` repository locally, make required changes to the [`packages/clandro-core/build.sh`] file to update the source url and then build.

Check [Build Local Package](https://github.com/cl-andro/clandro-packages/wiki/Building-packages#build-local-package) and [Package Build Local Source URLs](https://github.com/cl-andro/clandro-packages/wiki/Creating-new-package#package-build-local-source-urls) docs for more info on how to building packages from local sources.*

```shell
# Clone `clandro-packages` repo and switch current working directory to it.
git clone https://github.com/cl-andro/clandro-packages.git
cd clandro-packages

# Update `$CLANDRO_PKG_SRCURL` variable in `packages/clandro-core/build.sh`.
# We use `file:///path/to/source/dir` format for the local source URL.
CLANDRO_PKG_SRCURL=file:///home/builder/clandro-packages/sources/clandro-core-package
CLANDRO_PKG_SHA256=SKIP_CHECKSUM

# Clone/copy `clandro-core-package` repo at `clandro-packages/sources/clandro-core-package`
# directory. Make sure current working directory is root directory of
# clandro-packages repo when cloning.
git clone https://github.com/cl-andro/clandro-core-package.git sources/clandro-core-package

# (OPTIONAL) Manually switch to different (pull) branch that exists on
# origin if required, or to the one defined in $CLANDRO_PKG_GIT_BRANCH
# variable of build.sh file, as it will not be automatically checked out.
# By default, the repo default/current branch that's cloned
# will get built, which is usually `master` or `main`.
# Whatever is the current state of the source directory will
# be built as is, including any uncommitted changes to current
# branch.
(cd sources/clandro-core-package; git checkout <branch_name>)

# (OPTIONAL) Run clandro-packages docker container if running off-device.
./scripts/run-docker.sh

# Force build package and download dependencies from Clandro packages repositories.
./build-package.sh -f -I clandro-core
```

## &nbsp;

&nbsp;



### On Device With `make`

To build `clandro-core` package on the device inside the Clandro app with [`make`](https://www.gnu.org/software/make), check below. Do not use a PC to build the package as PC architecture may be different from target device architecture and the `clang` compiler wouldn't have been patched like Clandro provided one is so that built packages are compatible with Clandro, like patches done for `DT_RUNPATH`.

```shell
# Install dependencies.
pkg install clang git make clandro-create-package

# Export path to `clandro-packages` build repo directory needed to run
# `clandro-replace-clandro-core-src-scripts` script in `Makefile`.
export CLANDRO_PKGS__BUILD__REPO_ROOT_DIR="/path/to/clandro-packages/repo/dir"

# Clone/copy `clandro-core-package` repo at `clandro-core-package` directory
# and switch current working directory to it.
git clone https://github.com/cl-andro/clandro-core-package.git clandro-core-package
cd clandro-core-package

# Whatever is the current state of the `clandro-core-package` directory will be built.
# If required, manually switch to different (pull) branch that exists on origin.
git checkout <branch_name>

# Remove any existing deb files in current directory.
rm -f clandro-core_*.deb

# Build deb file for the architecture of the host device/clang compiler.
make packaging-debian-build

# Install.
# We use shell * glob expansion to automatically select the deb file
# regardless of `_<version>_<arch>.deb` suffix, that's why existing
# deb files were deleted earlier in case any existed with the wrong version.
dpkg -i clandro-core_*.deb
```

---

&nbsp;





[`packages/clandro-core/build.sh`]: https://github.com/cl-andro/clandro-packages/blob/master/packages/clandro-core/build.sh
[`properties.sh`]: https://github.com/cl-andro/clandro-packages/blob/master/scripts/properties.sh
