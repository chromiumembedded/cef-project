// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/resource_manager/client_impl.h"
#include "examples/shared/app_factory.h"
#include "examples/shared/browser_util.h"
#include "examples/shared/resource_util.h"

namespace resource_manager {

namespace {

std::string GetStartupURL() {
  return shared::kTestOrigin + std::string("resource_manager.html");
}

}  // namespace

// Implementation of CefApp for the browser process.
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
    shared::CreateBrowser(new Client(), GetStartupURL(), CefBrowserSettings());
  }

 private:
  IMPLEMENT_REFCOUNTING(BrowserApp);
  DISALLOW_COPY_AND_ASSIGN(BrowserApp);
};

}  // namespace resource_manager

namespace shared {

CefRefPtr<CefApp> CreateBrowserProcessApp() {
  return new resource_manager::BrowserApp();
}

}  // namespace shared
