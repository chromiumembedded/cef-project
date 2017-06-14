// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/minimal/client_minimal.h"
#include "examples/shared/app_factory.h"
#include "examples/shared/browser_util.h"

namespace minimal {

namespace {

const char kStartupURL[] = "https://www.google.com";

}  // namespace

// Minimal implementation of CefApp for the browser process.
class BrowserApp : public CefApp, public CefBrowserProcessHandler {
 public:
  BrowserApp() {}

  // CefApp methods:
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
    return this;
  }

  // CefBrowserProcessHandler methods:
  void OnContextInitialized() OVERRIDE {
    // Create the browser window.
    shared::CreateBrowser(new Client(), kStartupURL, CefBrowserSettings());
  }

 private:
  IMPLEMENT_REFCOUNTING(BrowserApp);
  DISALLOW_COPY_AND_ASSIGN(BrowserApp);
};

}  // namespace minimal

namespace shared {

CefRefPtr<CefApp> CreateBrowserProcessApp() {
  return new minimal::BrowserApp();
}

}  // namespace shared
