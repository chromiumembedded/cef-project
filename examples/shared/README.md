# Shared Library

This directory contains the "shared" target which implements a static library shared by all example executable targets.

## Implementation Overview

The "shared" target is an abstraction of the cefsimple project described in the [CEF Tutorial](https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial.md). The cefsimple application has been restructured for these examples so that common implementations and functionality live in the "shared" target while example-specific implementations live in the example executable targets ("message_router", "minimal", etc). The concepts described in the CEF Tutorial excluding the "Getting Started" section still apply to these example targets.

Executables that depend on this target are implemented as follows:

 * Define the target-specific [CMake](https://cmake.org/) build configuration in the CMakeLists.txt file. See the "Configuration" section below for details.
 * Call the shared [entry point functions](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-entry-point-function) declared in [main.h](main.h) and [process_helper_mac.h](process_helper_mac.h) that initialize, run and shut down CEF.
      * Linux implementation: [main_linux.cc](main_linux.cc) (single executable, all processes)
      * macOS implementation: [main_mac.mm](main_mac.mm) (main executable, main process), [process_helper_mac.cc](process_helper_mac.cc) (helper executable, sub-processes)
      * Windows implementation: [main_win.cc](main_win.cc) (single executable, all processes)
 * Implement the `shared::Create*ProcessApp` functions declared in [app_factory.h](app_factory.h) to create a [CefApp](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefapp) instance appropriate to the [process type](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-processes).
 * Provide a concrete [CefClient](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefclient) implementation to handle [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) callbacks. A `shared::CreateBrowser` function is provided in [browser_util.h](browser_util.h) for convenience and will usually be called from the target-specific `CefBrowserProcessHandler::OnContextInitialized` implementation. 
 * Windows: When using resources compiled into the binary implement the `shared::GetResourceId` method declared in [resource_util.h](resource_util.h) to map resource paths to BINARY ID values.

See the [minimal](../minimal) target for a minimal implementation example.
See the [resource_manager](../resource_manager) target for a resource loading example.

## Configuration

See the [CEF Tutorial](https://bitbucket.org/chromiumembedded/cef/wiki/Tutorial.md#markdown-header-build-steps) for an overview of the steps performed by the [CMake](https://cmake.org/) build configuration.

To add a new example executable target:

 1. Create a new directory for the executable target inside the examples folder.
 2. Add source files in the new directory that implement the required functionality as described in the "Implementation Overview" section above, or reference existing implementations from the [minimal target](../minimal) directory.
 3. Copy the `CMakeLists.txt` file from an existing executable target to the new directory. If the new target contains resources start with the [resource_manager CMakeLists.txt configuration](../resource_manager/CMakeLists.txt). Otherwise, start with the [minimal CMakeLists.txt configuration](../minimal/CMakeLists.txt).
     * Modify the "Source files" section to specify the correct source files.
     * Modify the "Shared configuration" section to specify the correct target name.
 4. Add the new directory name to the "Example executable targets" section at the end of the [examples CMakeLists.txt configuration](../CMakeLists.txt).
 5. Add a description and link to the example in the [examples README.md](../README.md) file.
 6. Run the `cmake` command as described in the top-level [README.md](../../README.md) file to regenerate the project files. Verify that the new example builds and runs as expected.
 7. If you would like to upstream your changes create a [Pull Request](https://bitbucket.org/chromiumembedded/cef/wiki/ContributingWithGit.md#markdown-header-working-with-pull-requests).

## Setup and Build

Follow the Setup and Build instructions in the top-level [README.md](../../README.md) file. When building from within Visual Studio or Xcode the example targets are placed inside the "examples" folder. When building from the command-line the target name matches the directory name and can be specified directly (e.g. "message_router", "minimal", etc.).
