The [Chromium Embedded Framework](https://bitbucket.org/chromiumembedded/cef/) (CEF) is a simple framework for embedding Chromium-based browsers in other applications. This repository hosts a sample project called "cef-project" that can be used as the starting point for third-party applications built using CEF.

# Quick Links

* Project Page - https://bitbucket.org/chromiumembedded/cef-project
* Tutorial - https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial
* Support Forum - http://www.magpcss.org/ceforum/

# Setup

First install some necessary tools and download the cef-project source code.

1\. Install [CMake](https://cmake.org/), a cross-platform open-source build system. Version 2.8.12.1 or newer is required.

2\. Install [Python](https://www.python.org/downloads/). Version 2.x is required. If Python is not installed to the default location you can set the `PYTHON_EXECUTABLE` environment variable before running CMake (watch for errors during the CMake generation step below).

3\. Install platform-specific build tools.

* Linux: Currently supported distributions include Debian Wheezy, Ubuntu Precise, and related. Ubuntu 14.04 64-bit is recommended. Newer versions will likely also work but may not have been tested. Required packages include: build-essential, libgtk2.0-dev, libgtkglext1-dev.
* macOS: Xcode 6 or newer building on macOS 10.9 (Mavericks) or newer is required. Xcode 8.3 and macOS 10.12 (Sierra) are recommended. The Xcode command-line tools must also be installed. Only 64-bit builds are supported on macOS.
* Windows: Visual Studio 2013 or newer building on Windows 7 or newer is required. Visual Studio 2017 and Windows 10 64-bit are recommended.

4\. Download the cef-project source code from the [Downloads page](https://bitbucket.org/chromiumembedded/cef-project/downloads) or by using [Git](https://git-scm.com/) command-line tools:

```
git clone https://bitbucket.org/chromiumembedded/cef-project.git
```

# Build

Now run CMake which will download the CEF binary distribution from the [Spotify automated builder](http://opensource.spotify.com/cefbuilds/index.html) and generate build files for your platform. Then build using platform build tools. For example, using the most recent tool versions on each platform:

```
cd /path/to/cef-project

# Create and enter the build directory.
mkdir build
cd build

# To perform a Linux build using a 32-bit CEF binary distribution on a 32-bit
# Linux platform or a 64-bit CEF binary distribution on a 64-bit Linux platform:
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j4 cefclient cefsimple

# To perform a macOS build using a 64-bit CEF binary distribution:
cmake -G "Xcode" ..
# Then, open build\cef.xcodeproj in Xcode and select Product > Build.

# To perform a Windows build using a 32-bit CEF binary distribution:
cmake -G "Visual Studio 15" ..
# Then, open build\cef.sln in Visual Studio 2017 and select Build > Build Solution.

# To perform a Windows build using a 64-bit CEF binary distribution:
cmake -G "Visual Studio 15 Win64" ..
# Then, open build\cef.sln in Visual Studio 2017 and select Build > Build Solution.
```

CMake supports different generators on each platform. Run `cmake --help` to list all supported generators. Generators that have been tested with CEF include:

* Linux: Ninja, Unix Makefiles
* macOS: Ninja, Xcode 6+
* Windows: Ninja, Visual Studio 2013+

Ninja is a cross-platform open-source tool for running fast builds using pre-installed platform toolchains (GNU, clang, Xcode or MSVC). See comments in the "third_party/cef/cef_binary_*/CMakeLists.txt" file for Ninja usage instructions.

# Examples

CEF provides a number of examples that you can use as a starting point or reference for your own CEF-based development.

* By default all example targets will be included in the project files generated using CMake.
* The CEF binary distribution includes cefsimple and cefclient sample applications.
    * The cefsimple application demonstrates the minimal implementation required for a standalone executable target and is described on the [Tutorial](https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial.md) Wiki page.
    * The cefclient application demonstrates a wide range of CEF functionality most of which is documented on the [GeneralUsage](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md) Wiki page.
* The [examples directory](examples) contains example targets that demonstrate specific aspects of CEF functionality.
    * See the [examples README.md file](examples/README.md) for information about the examples targets.
    * Add `-DWITH_EXAMPLES=Off` to the cmake command-line if you do not wish to build the examples targets.

# Next Steps

Here are some activities you might want to try next to gain a better understanding of CEF:

1\. Update the CEF version used to build your local copy of cef-project:

* Visit the [Spotify automated builder](http://opensource.spotify.com/cefbuilds/index.html) page to see what CEF versions are available.
* Change the "CEF_VERSION" value near the top of the [top-level CMakeLists.txt file](https://bitbucket.org/chromiumembedded/cef-project/src/master/CMakeLists.txt?fileviewer=file-view-default).
* Re-run the cmake and build commands. Add `-DWITH_EXAMPLES=Off` to the cmake command-line to disable targets from the [examples directory](examples) because they may not build successfully with the new CEF version.

2\. Add your own project source code:

* Create a new "myproject" directory in the root cef-project directory (e.g. "/path/to/cef-project/myproject").
* Copy the contents of the "third_party/cef/cef_binary_*/cefsimple" directory to "myproject" as a starting point.
* Add a new `add_subdirectory(myproject)` command near the end of [top-level CMakeLists.txt file](https://bitbucket.org/chromiumembedded/cef-project/src/master/CMakeLists.txt?fileviewer=file-view-default) after the existing add_subdirectory commands.
* Change the "CEF_TARGET" and "CEF_HELPER_TARGET" values in "myproject/CMakeLists.txt" from "cefsimple" to "myproject".
* (Windows only) Rename the "cefclient.exe.manifest" file to "myproject.exe.manifest" in both "myproject/CMakeLists.txt" and the "myproject" directory.
* Re-run the cmake and build commands.

3\. Gain a better understanding of the cefsimple application by reading the [Tutorial](https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial.md) Wiki page.

4\. Fork the cef-project repository using Bitbucket and Git to store the source code for your own CEF-based project. See the [ContributingWithGit](https://bitbucket.org/chromiumembedded/cef/wiki/ContributingWithGit.md) Wiki page for details (replace all instances of "cef" with "cef-project" in those instructions).

5\. Review the [GeneralUsage](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md) Wiki page for additional details on CEF implementation and usage.

# Support and Contributions

If you have any questions about CEF or cef-project please ask on the [CEF Forum](http://www.magpcss.org/ceforum/). If you would like to make contributions please see the "Helping Out" section of the [CEF Main Page](https://bitbucket.org/chromiumembedded/cef/).