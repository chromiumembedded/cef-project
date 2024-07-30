// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/browser_util.h"

#include "examples/shared/client_util.h"

#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

namespace shared {

namespace {

// When using the Views framework this object provides the delegate
// implementation for the CefWindow that hosts the Views-based browser.
class WindowDelegate : public CefWindowDelegate {
 public:
  WindowDelegate(CefRefPtr<CefBrowserView> browser_view,
                 cef_runtime_style_t runtime_style)
      : browser_view_(browser_view), runtime_style_(runtime_style) {}

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

  cef_runtime_style_t GetWindowRuntimeStyle() override {
    return runtime_style_;
  }

 private:
  CefRefPtr<CefBrowserView> browser_view_;
  const cef_runtime_style_t runtime_style_;

  IMPLEMENT_REFCOUNTING(WindowDelegate);
  DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
};

class BrowserViewDelegate : public CefBrowserViewDelegate {
 public:
  explicit BrowserViewDelegate(cef_runtime_style_t runtime_style)
      : runtime_style_(runtime_style) {}

  bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view,
                                 CefRefPtr<CefBrowserView> popup_browser_view,
                                 bool is_devtools) override {
    // Create a new top-level Window for the popup. It will show itself after
    // creation.
    CefWindow::CreateTopLevelWindow(
        new WindowDelegate(popup_browser_view, runtime_style_));

    // We created the Window.
    return true;
  }

  cef_runtime_style_t GetBrowserRuntimeStyle() override {
    return runtime_style_;
  }

 private:
  const cef_runtime_style_t runtime_style_;

  IMPLEMENT_REFCOUNTING(BrowserViewDelegate);
  DISALLOW_COPY_AND_ASSIGN(BrowserViewDelegate);
};

}  // namespace

void CreateBrowser(CefRefPtr<CefClient> client,
                   const CefString& startup_url,
                   const CefBrowserSettings& settings) {
  CEF_REQUIRE_UI_THREAD();

  const auto runtime_style = IsAlloyStyleEnabled() ? CEF_RUNTIME_STYLE_ALLOY
                                                   : CEF_RUNTIME_STYLE_DEFAULT;

  // Create the browser using the Views framework if "--use-views"  or
  // "--enable-chrome-runtime" is specified via the command-line. Otherwise,
  // create the browser using the native platform framework.
  if (IsViewsEnabled()) {
    // Create the BrowserView.
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
        client, startup_url, settings, nullptr, nullptr,
        new BrowserViewDelegate(runtime_style));

    // Create the Window. It will show itself after creation.
    CefWindow::CreateTopLevelWindow(
        new WindowDelegate(browser_view, runtime_style));
  } else {
    // Information used when creating the native window.
    CefWindowInfo window_info;

#if defined(OS_WIN)
    // On Windows we need to specify certain flags that will be passed to
    // CreateWindowEx().
    window_info.SetAsPopup(nullptr, "examples");
#endif

    // Alloy style will create a basic native window. Chrome style will create a
    // fully styled Chrome UI window.
    window_info.runtime_style = runtime_style;

    // Create the browser window.
    CefBrowserHost::CreateBrowser(window_info, client, startup_url, settings,
                                  nullptr, nullptr);
  }
}

}  // namespace shared
