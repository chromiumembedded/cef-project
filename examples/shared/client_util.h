// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_SHARED_CLIENT_BASE_H_
#define CEF_EXAMPLES_SHARED_CLIENT_BASE_H_

#include "include/cef_client.h"

namespace shared {

// This file provides functionality common to all CefClient example
// implementations.

// Called from CefDisplayHandler methods:
void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);

// Called from CefLifeSpanHandler methods:
void OnAfterCreated(CefRefPtr<CefBrowser> browser);
bool DoClose(CefRefPtr<CefBrowser> browser);
void OnBeforeClose(CefRefPtr<CefBrowser> browser);

// Platform-specific implementation.
void PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);

// Returns the contents of |request| as a string.
std::string DumpRequestContents(CefRefPtr<CefRequest> request);

// Returns true if use of the Views framework is enabled.
bool IsViewsEnabled();

// Returns true if use of the Chrome runtime is enabled.
bool IsChromeRuntimeEnabled();

}  // namespace shared

#endif  // CEF_EXAMPLES_SHARED_CLIENT_BASE_H_
