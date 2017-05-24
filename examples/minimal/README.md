# Minimal Example Application

This directory contains the "minimal" target which demonstrates the minimal functionality required to build an executable using the [shared library](../shared) target.

See the [shared library](../shared) target for details common to all executable targets.

## Implementation Overview

The "minimal" target is implemented as follows:

 * Define the target-specific [CMake](https://cmake.org/) build configuration in the [CMakeLists.txt](CMakeLists.txt) file.
 * Call the shared [entry point functions](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-entry-point-function) that initialize, run and shut down CEF.
     * Main process (all platforms): [main_minimal.cc](main_minimal.cc)
     * Sub-process (macOS only): [process_helper_mac_minimal.cc](process_helper_mac_minimal.cc)
 * Implement the [shared::Create*ProcessApp](../shared/app_factory.h) functions to create a [CefApp](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefapp) instance appropriate to the [process type](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-processes).
     * Browser process: [app_browser_minimal.cc](app_browser_minimal.cc) implements the `shared::CreateBrowserProcessApp` method to return a `CefApp` instance.
         * The `OnContextInitialized` method creates the initial [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) instance using the [shared::CreateBrowser](../shared/browser_util.h) helper function.
     * Renderer process: [app_renderer_minimal.cc](app_renderer_minimal.cc) implements the `shared::CreateRendererProcessApp` method to return NULL (no `CefApp` for this process).
     * Other sub-processes: [app_other_minimal.cc](app_other_minimal.cc) implements the `shared::CreateOtherProcessApp` method to return NULL (no `CefApp` for this process).
 * Provide a concrete [CefClient](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefclient) implementation in [client_minimal.cc](client_minimal.cc) and [client_minimal.h](client_minimal.h) to handle [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) callbacks.

Other targets use the minimal implementation source files (*_minimal.cc) in cases where example-specific customization is not required.

## Configuration

See the [shared library](../shared) target for configuration details.

## Setup and Build

See the [shared library](../shared) target for setup and build instructions.
