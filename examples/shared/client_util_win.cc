// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/client_util.h"

#include <windows.h>
#include <string>

#include "include/cef_browser.h"

namespace shared {

void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                         const CefString& title) {
  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
  SetWindowText(hwnd, std::wstring(title).c_str());
}

}  // namespace shared
