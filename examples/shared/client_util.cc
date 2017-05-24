// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/client_util.h"

#include <sstream>
#include <string>

#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

#include "examples/shared/client_manager.h"

namespace shared {

void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {
  CEF_REQUIRE_UI_THREAD();

#if defined(OS_WIN) || defined(OS_LINUX)
  // The Views framework is currently only supported on Windows and Linux.
  CefRefPtr<CefBrowserView> browser_view =
      CefBrowserView::GetForBrowser(browser);
  if (browser_view) {
    // Set the title of the window using the Views framework.
    CefRefPtr<CefWindow> window = browser_view->GetWindow();
    if (window)
      window->SetTitle(title);
  } else
#endif
  {
    // Set the title of the window using platform APIs.
    PlatformTitleChange(browser, title);
  }
}

void OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Add to the list of existing browsers.
  ClientManager::GetInstance()->OnAfterCreated(browser);
}

bool DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Closing the main window requires special handling. See the DoClose()
  // documentation in the CEF header for a detailed destription of this
  // process.
  ClientManager::GetInstance()->DoClose(browser);

  // Allow the close. For windowed browsers this will result in the OS close
  // event being sent.
  return false;
}

void OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Remove from the list of existing browsers.
  ClientManager::GetInstance()->OnBeforeClose(browser);
}

}  // namespace shared
