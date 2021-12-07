// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/message_router/client_impl.h"
#include "examples/shared/app_factory.h"
#include "examples/shared/browser_util.h"
#include "examples/shared/resource_util.h"

namespace message_router {

namespace {

std::string GetStartupURL() {
  return shared::kTestOrigin + std::string("message_router.html");
}

}  // namespace

// Implementation of CefApp for the browser process.
class BrowserApp : public CefApp, public CefBrowserProcessHandler {
 public:
  BrowserApp() {}

  // CefApp methods:
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
    return this;
  }

  void OnBeforeCommandLineProcessing(
      const CefString& process_type,
      CefRefPtr<CefCommandLine> command_line) override {
    // Command-line flags can be modified in this callback.
    // |process_type| is empty for the browser process.
    if (process_type.empty()) {
#if defined(OS_MACOSX)
      // Disable the macOS keychain prompt. Cookies will not be encrypted.
      command_line->AppendSwitch("use-mock-keychain");
#endif
    }
  }

  // CefBrowserProcessHandler methods:
  void OnContextInitialized() override {
    // Create the browser window.
    const CefString& startup_url = GetStartupURL();
    shared::CreateBrowser(new Client(startup_url), startup_url,
                          CefBrowserSettings());
  }

 private:
  IMPLEMENT_REFCOUNTING(BrowserApp);
  DISALLOW_COPY_AND_ASSIGN(BrowserApp);
};

}  // namespace message_router

namespace shared {

CefRefPtr<CefApp> CreateBrowserProcessApp() {
  return new message_router::BrowserApp();
}

}  // namespace shared
