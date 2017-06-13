# Examples

This directory contains example applications that demonstrate specific aspects of CEF functionality.

 * [message_router](message_router) demonstrates how to create JavaScript bindings using [CefMessageRouter](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-generic-message-router).
 * [minimal](minimal) demonstrates the minimal functionality required to build an executable using the [shared library](shared).
 * [resource_manager](resource_manager) demonstrates how to handle resource requests using [CefResourceManager](https://bitbucket.org/chromiumembedded/cef/src/master/include/wrapper/cef_resource_manager.h?at=master&fileviewer=file-view-default).
 * [scheme_handler](scheme_handler) demonstrates how to handle resource requests using [CefSchemeHandlerFactory](https://bitbucket.org/chromiumembedded/cef/wiki/GeneralUsage.md#markdown-header-scheme-handler).
 * [shared](shared) is a static library that implements functionality common to all example executable targets.

## Implementation Overview

Each target directory contains a README.md file that provides an implementation overview.

## Configuration

See the [shared library](shared) target for configuration details.

## Setup and Build

See the [shared library](shared) target for setup and build instructions.
