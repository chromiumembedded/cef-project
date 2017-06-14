// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_SHARED_BROWSER_UTIL_H_
#define CEF_EXAMPLES_SHARED_BROWSER_UTIL_H_

#include "include/cef_client.h"

namespace shared {

// Helper for creating a new CefBrowser instance. Usually called from the
// CefBrowserProcessHandler::OnContextInitialized method. Respects the
// "--use-views" command-line flag if specified. Must be called on the browser
// process UI thread.
void CreateBrowser(CefRefPtr<CefClient> client,
                   const CefString& startup_url,
                   const CefBrowserSettings& settings);

}  // namespace shared

#endif  // CEF_EXAMPLES_SHARED_BROWSER_UTIL_H_
