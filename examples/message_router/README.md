# Message Router Example Application

This directory contains the "message_router" target which demonstrates how to create JavaScript bindings using [CefMessageRouter](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-generic-message-router).

See the [shared library](../shared) target for details common to all executable targets.

## Implementation Overview

The "message_router" target is implemented as follows:

 * Define the target-specific [CMake](https://cmake.org/) build configuration in the [CMakeLists.txt](CMakeLists.txt) file.
 * Call the shared [entry point functions](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-entry-point-function) that initialize, run and shut down CEF.
     * Uses the [minimal target](../minimal) implementation.
 * Implement the [shared::Create*ProcessApp](../shared/app_factory.h) functions to create a [CefApp](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefapp) instance appropriate to the [process type](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-processes).
     * Browser process: [app_browser_impl.cc](app_browser_impl.cc) implements the `shared::CreateBrowserProcessApp` method to return a `CefApp` instance.
         * The `OnContextInitialized` method creates the initial [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) instance using the [shared::CreateBrowser](../shared/browser_util.h) helper function.
     * Renderer process: [app_renderer_impl.cc](app_renderer_impl.cc) implements the `shared::CreateRendererProcessApp` method to return a `CefApp` instance.
         * Creates a `CefMessageRouterRendererSide` instance to handle the renderer side of message routing.
     * Other sub-processes: Uses the [minimal target](../minimal) implementation.
 * Provide a concrete [CefClient](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefclient) implementation in [client_impl.cc](client_impl.cc) and [client_impl.h](client_impl.h) to handle [CefBrowser](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-cefbrowser-and-cefframe) callbacks.
      * Creates a `CefMessageRouterBrowserSide` instance to handle the browser side of message routing.
      * Creates a `CefMessageRouterBrowserSide::Handler` instance to handle messages specific to the test code in [message_router.html](resources/message_router.html).
      * Implements the `GetResourceHandler` method to support loading of [message_router.html](resources/message_router.html) via https://example.com/message_router.html.
 * Windows resource loading implementation in [resource_util_win_impl.cc](resource_util_win_impl.cc) and [resource.rc](resources/win/resource.rc).
     * Implements the [shared::GetResourceId](../shared/resource_util.h) method to map resource paths to BINARY ID values.
     * Defines a BINARY resource to include [message_router.html](resources/message_router.html) in the executable.

## Configuration

See the [shared library](../shared) target for configuration details.

## Setup and Build

See the [shared library](../shared) target for setup and build instructions.
