// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_SHARED_RESOURCE_UTIL_H_
#define CEF_EXAMPLES_SHARED_RESOURCE_UTIL_H_

#include <string>

#include "include/cef_resource_handler.h"
#include "include/cef_stream.h"

#if defined(OS_WIN)
#include "include/wrapper/cef_resource_manager.h"
#endif

namespace shared {

// This file provides functionality for resource loading. On Linux amd macOS
// resource files are loaded from a directory on the filesystem
// ("<target>_files" sub-directory on Linux, app bundle Resources directory on
// macOS). On Windows resource files are loaded from BINARY resources built into
// the executable (see GetResourceId comments for details).

// Origin for loading local test resources.
extern const char kTestOrigin[];

#if defined(OS_POSIX)
// Retrieve the directory containing resource files on Linux and macOS.
bool GetResourceDir(std::string& dir);
#endif

// Returns the resource path for |url|. Removes fragment and/or query component
// if it exists. The URL must start with kTestOrigin.
std::string GetResourcePath(const std::string& url);

// Determine the mime type based on |resource_path|'s file extension.
std::string GetMimeType(const std::string& resource_path);

#if defined(OS_WIN)
// Returns the BINARY id value associated with |resource_path| on Windows.
// Implemented for individual executable targets as follows:
// 1. Add the ID value in */resources/win/resource.h
// 2. Add the ID to file path mapping in */resources/win/resource.rc
// 2. Add the |resource_path| to ID mapping in */resource_util_win_impl.cc.
int GetResourceId(const std::string& resource_path);

// Create a new provider for loading BINARY resources on Windows. Only URLs
// beginning with |root_url| will be handled by this provider. See the
// "resource_manager" target for example usage.
CefResourceManager::Provider* CreateBinaryResourceProvider(
    const std::string& root_url);
#endif  // defined(OS_WIN)

// Retrieve |resource_path| contents as a std::string. Returns false if the
// resource is not found.
bool GetResourceString(const std::string& resource_path, std::string& out_data);

// Retrieve |resource_path| contents as a CefStreamReader. Returns NULL if the
// resource is not found.
CefRefPtr<CefStreamReader> GetResourceReader(const std::string& resource_path);

// Retrieve |resource_path| contents as a CefResourceHandler. Returns NULL if
// the resource is not found.
CefRefPtr<CefResourceHandler> GetResourceHandler(
    const std::string& resource_path);

}  // namespace shared

#endif  // CEF_EXAMPLES_SHARED_RESOURCE_UTIL_H_
