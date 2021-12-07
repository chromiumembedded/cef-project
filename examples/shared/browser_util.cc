// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/browser_util.h"

#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

namespace shared {

namespace {

// When using the Views framework this object provides the delegate
// implementation for the CefWindow that hosts the Views-based browser.
class WindowDelegate : public CefWindowDelegate {
 public:
  explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view)
      : browser_view_(browser_view) {}

  void OnWindowCreated(CefRefPtr<CefWindow> window) override {
    // Add the browser view and show the window.
    window->AddChildView(browser_view_);
    window->Show();

    // Give keyboard focus to the browser view.
    browser_view_->RequestFocus();
  }

  void OnWindowDestroyed(CefRefPtr<CefWindow> window) override {
    browser_view_ = nullptr;
  }

  bool CanClose(CefRefPtr<CefWindow> window) override {
    // Allow the window to close if the browser says it's OK.
    CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
    if (browser)
      return browser->GetHost()->TryCloseBrowser();
    return true;
  }

  CefSize GetPreferredSize(CefRefPtr<CefView> view) override {
    // Preferred window size.
    return CefSize(800, 600);
  }

  CefSize GetMinimumSize(CefRefPtr<CefView> view) override {
    // Minimum window size.
    return CefSize(200, 100);
  }

 private:
  CefRefPtr<CefBrowserView> browser_view_;

  IMPLEMENT_REFCOUNTING(WindowDelegate);
  DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
};

}  // namespace

void CreateBrowser(CefRefPtr<CefClient> client,
                   const CefString& startup_url,
                   const CefBrowserSettings& settings) {
  CEF_REQUIRE_UI_THREAD();

#if defined(OS_WIN) || defined(OS_LINUX)
  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();

  // Create the browser using the Views framework if "--use-views" is specified
  // via the command-line. Otherwise, create the browser using the native
  // platform framework. The Views framework is currently only supported on
  // Windows and Linux.
  const bool use_views = command_line->HasSwitch("use-views");
#else
  const bool use_views = false;
#endif

  if (use_views) {
    // Create the BrowserView.
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
        client, startup_url, settings, nullptr, nullptr, nullptr);

    // Create the Window. It will show itself after creation.
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browser_view));
  } else {
    // Information used when creating the native window.
    CefWindowInfo window_info;

#if defined(OS_WIN)
    // On Windows we need to specify certain flags that will be passed to
    // CreateWindowEx().
    window_info.SetAsPopup(nullptr, "examples");
#endif

    // Create the browser window.
    CefBrowserHost::CreateBrowser(window_info, client, startup_url, settings,
                                  nullptr, nullptr);
  }
}

}  // namespace shared
