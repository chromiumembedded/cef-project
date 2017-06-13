# Scheme Handler Example Application

This directory contains the "scheme_handler" target which demonstrates how to handle resource requests using [CefSchemeHandlerFactory](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-scheme-handler).

See the [shared library](../shared) target for details common to all executable targets.

## Implementation Overview

The "scheme_handler" target is implemented as follows:

 * Define the target-specific [CMake](https://cmake.org/) build configuration in the [CMakeLists.txt](CMakeLists.txt) file.
 * Call the shared [entry point functions](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-entry-point-function) that initialize, run and shut down CEF.
     * Uses the [minimal target](../minimal) implementation.
 * Implement the [shared::Create*ProcessApp](../shared/app_factory.h) functions to create a [CefApp](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefapp) instance appropriate to the [process type](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-processes).
     * Browser process: [app_browser_impl.cc](app_browser_impl.cc) implements the `shared::CreateBrowserProcessApp` method.
         * Register the custom scheme name in [OnRegisterCustomSchemes](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-request-handling).
         * Register the custom scheme handler factory by calling `RegisterSchemeHandlerFactory` implemented in [scheme_handler_impl.cc](scheme_handler_impl.cc).
         * Create the initial [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) instance.
     * Other processes: [app_subprocess_impl.cc](app_subprocess_impl.cc) implements the `shared::CreateRendererProcessApp` and `shared::CreateOtherProcessApp` methods.
         * Register the custom scheme name in [OnRegisterCustomSchemes](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-request-handling).
 * Provide a concrete [CefClient](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefclient) implementation to handle [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) callbacks.
      * Uses the [minimal target](../minimal) implementation.
 * Windows resource loading implementation in [resource_util_win_impl.cc](resource_util_win_impl.cc) and [resource.rc](resources/win/resource.rc).
     * Implements the [shared::GetResourceId](../shared/resource_util.h) method to map resource paths to BINARY ID values.
     * Defines a BINARY resource to include [logo.png](resources/logo.png) and [scheme_handler.html](resources/scheme_handler.html) in the executable.

## Configuration

See the [shared library](../shared) target for configuration details.

## Setup and Build

See the [shared library](../shared) target for setup and build instructions.
