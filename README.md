The [Chromium Embedded Framework](https://bitbucket.org/chromiumembedded/cef/) (CEF) is a simple framework for embedding Chromium-based browsers in other applications. This repository hosts a sample project called "cef-project" that can be used as the starting point for third-party applications built using CEF.

# Quick Links

* Project Page - https://bitbucket.org/chromiumembedded/cef-project
* Tutorial - https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial
* Support Forum - http://www.magpcss.org/ceforum/

# Setup

First install some necessary tools and download the cef-project source code.

1\. Install [Python](https://www.python.org/downloads/). Version 3.9 to 3.11 is required.

2\. Install platform-specific build tools.

* Linux: Currently supported distributions include Debian 10 (Buster), Ubuntu 18 (Bionic Beaver), and related, with minimum GCC version 7.5.0. Ubuntu 22.04 64-bit with GCC 11+ is recommended. Newer versions will likely also work but may not have been tested. Required packages include: build-essential, libgtk-3-dev.
* MacOS: Xcode 12.2 to 15.0 building on MacOS 10.15.4 (Catalina) or newer. The Xcode command-line tools must also be installed.
* Windows: Visual Studio 2022 building on Windows 10 or newer. Windows 10/11 64-bit is recommended.

3\. Download the cef-project source code from the [Downloads page](https://bitbucket.org/chromiumembedded/cef-project/downloads) or by using [Git](https://git-scm.com/) command-line tools:

```
git clone https://bitbucket.org/chromiumembedded/cef-project.git
```

# Build

The CEF examples included in this project can be built using either [CMake](https://cmake.org/) or [Bazel](https://bazel.build/).
These are both highly regarded cross-platform open-source build systems.

## Using CMake

[CMake](https://cmake.org/) can be used to generate project files in many different formats.

To build the cef-project example applications using CMake:

1\. Install [CMake](https://cmake.org/download/). Version 3.21 or newer is required.

2\. Set the `PYTHON_EXECUTABLE` environment variable if required (watch for errors during the CMake generation step below).

3\. Run CMake to download the CEF binary distribution from the [Spotify automated builder](https://cef-builds.spotifycdn.com/index.html) and generate build files for your platform. 

4\. Build using platform build tools. For example, using the most recent tool versions on each platform:

```
cd /path/to/cef-project

# Create and enter the build directory.
mkdir build
cd build

# To perform a Linux build using a CEF binary distribution matching the host
# architecture (x64, ARM or ARM64):
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j4

# To perform a MacOS build using a 64-bit CEF binary distribution:
cmake -G "Xcode" -DPROJECT_ARCH="x86_64" ..
# Then, open build\cef.xcodeproj in Xcode and select Product > Build.

# To perform a MacOS build using an ARM64 CEF binary distribution:
cmake -G "Xcode" -DPROJECT_ARCH="arm64" ..
# Then, open build\cef.xcodeproj in Xcode and select Product > Build.

# To perform a Windows build using a 32-bit CEF binary distribution:
cmake -G "Visual Studio 17" -A Win32 ..
# Then, open build\cef.sln in Visual Studio 2022 and select Build > Build Solution.

# To perform a Windows build using a 64-bit CEF binary distribution:
cmake -G "Visual Studio 17" -A x64 ..
# Then, open build\cef.sln in Visual Studio 2022 and select Build > Build Solution.

# To perform a Windows build using an ARM64 CEF binary distribution:
cmake -G "Visual Studio 17" -A arm64 ..
# Then, open build\cef.sln in Visual Studio 2022 and select Build > Build Solution.
```

CMake supports different generators on each platform. Run `cmake --help` to list all supported generators. Generators that have been tested with CEF include:

* Linux: Ninja, GCC 7.5.0+, Unix Makefiles
* MacOS: Ninja, Xcode 12.2 to 15.0
* Windows: Ninja, Visual Studio 2022+

Ninja is a cross-platform open-source tool for running fast builds using pre-installed platform toolchains (GNU, clang, Xcode or MSVC). See comments in the "third_party/cef/cef_binary_*/CMakeLists.txt" file for Ninja usage instructions.

## Using Bazel

CEF support for [Bazel](https://bazel.build/) is considered experimental. For current development status see
https://github.com/chromiumembedded/cef/issues/3757.

To build the cef-project example applications using Bazel:

1\. Install [Bazelisk](https://github.com/bazelbuild/bazelisk/blob/master/README.md).

2\. (Linux only) Install the patchelf package:
```
sudo apt install patchelf
```

3\. Configure the CEF platform (see command output for details):
```
cd /path/to/cef-project
python3 ./tools/bazel/platform_updater.py
```
4\. Build using Bazel:
```
bazel build //examples/minimal
```
This will perform the following actions:

* Download/install Bazel at the required [version](.bazelversion) (if necessary).
* Download the CEF binary distribution at the required [version](bazel/cef/version.bzl) from the
[Spotify automated builder](https://cef-builds.spotifycdn.com/index.html) (if necessary).
* Build using the default platform toolchain.

5\. Run using Bazel:
```
# On Linux/MacOS:
bazel run //examples/minimal

# On Windows:
bazel run //examples/minimal/win:minimal.exe
```

To build other cef-project example applications replace `minimal` with the name of
the other application. To build CEF sample applications from the binary distribution
(cefsimple, cefclient, ceftests) use the `@cef//tests/cefsimple` target syntax.

Additional notes:

* To generate a Debug build add `-c dbg` (both `build` and `run`
  command-line).
* To pass arguments using the `run` command add `-- [...]` at the end.
* See `platform_updater.py` output for additional instructions when cross-compiling.

# Examples

CEF provides a number of examples that you can use as a starting point or reference for your own CEF-based development.

* By default all example targets will be included in the project files generated using CMake.
* The CEF binary distribution includes cefsimple and cefclient sample applications.
    * The cefsimple application demonstrates the minimal implementation required for a standalone executable target and is described on the [Tutorial](https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial.md) Wiki page.
    * The cefclient application demonstrates a wide range of CEF functionality most of which is documented on the [GeneralUsage](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md) Wiki page.
* The [examples directory](examples) contains example targets that demonstrate specific aspects of CEF functionality.
    * See the [examples README.md file](examples/README.md) for information about the examples targets.
    * Using CMake: Add `-DWITH_EXAMPLES=Off` to the CMake command-line if you do not wish to build the examples targets.

# Next Steps

Here are some activities you might want to try next to gain a better understanding of CEF:

1\. Update the CEF version used to build your local copy of cef-project:

* Visit the [Spotify automated builder](https://cef-builds.spotifycdn.com/index.html) page to see what CEF versions are available.
* Using CMake:
    * Change the "CEF_VERSION" value near the top of the [top-level CMakeLists.txt file](https://bitbucket.org/chromiumembedded/cef-project/src/master/CMakeLists.txt?fileviewer=file-view-default).
    * Re-run the CMake and build commands. Add `-DWITH_EXAMPLES=Off` to the CMake command-line to disable targets from the [examples directory](examples) because they may not build successfully with the new CEF version.
* Using Bazel:
    * Run the `./tools/bazel/version_updater.py` script to update the CEF version (see command output for details).
    * Build and run the `@cef//tests/cefsimple` target. See instructions above.

2\. Add your own project source code:

* Create a new "myproject" directory in the root cef-project directory (e.g. "/path/to/cef-project/myproject").
* Copy the contents of the "third_party/cef/cef_binary_*/tests/cefsimple" directory to "myproject" as a starting point.
* Replace all instances of "cefsimple" with "myproject" and "tests" with "examples" in file names and file contents.
* Using CMake:
    * Add a new `add_subdirectory(myproject)` command near the end of [top-level CMakeLists.txt file](https://bitbucket.org/chromiumembedded/cef-project/src/master/CMakeLists.txt?fileviewer=file-view-default) after the existing add_subdirectory commands.
    * Re-run the cmake and build commands.
* Using Bazel:
    * In all copied `BUILD.bazel` files change `load("//bazel...` to `load("@cef//bazel...`
    * Build and run the `//examples/myproject` target. See instructions above.

3\. Gain a better understanding of the cefsimple application by reading the [Tutorial](https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial.md) Wiki page.

4\. Fork the cef-project repository using Bitbucket and Git to store the source code for your own CEF-based project. See the [ContributingWithGit](https://bitbucket.org/chromiumembedded/cef/wiki/ContributingWithGit.md) Wiki page for details (replace all instances of "cef" with "cef-project" in those instructions).

5\. Review the [GeneralUsage](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md) Wiki page for additional details on CEF implementation and usage.

# Support and Contributions

If you have any questions about CEF or cef-project please ask on the [CEF Forum](http://www.magpcss.org/ceforum/). If you would like to make contributions please see the "Helping Out" section of the [CEF Main Page](https://bitbucket.org/chromiumembedded/cef/).
