// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/app_factory.h"

#include "examples/scheme_handler/scheme_strings.h"

namespace scheme_handler {

// Implementation of CefApp for all subprocesses.
class SubprocessApp : public CefApp {
 public:
  SubprocessApp() {}

  // CefApp methods:
  void OnRegisterCustomSchemes(
      CefRawPtr<CefSchemeRegistrar> registrar) override {
    // Register the custom scheme as standard and secure.
    // Must be the same implementation in all processes.
    registrar->AddCustomScheme(kScheme, kSchemeRegistrationOptions);
  }

 private:
  IMPLEMENT_REFCOUNTING(SubprocessApp);
  DISALLOW_COPY_AND_ASSIGN(SubprocessApp);
};

}  // namespace scheme_handler

namespace shared {

CefRefPtr<CefApp> CreateRendererProcessApp() {
  return new scheme_handler::SubprocessApp();
}

CefRefPtr<CefApp> CreateOtherProcessApp() {
  return new scheme_handler::SubprocessApp();
}

}  // namespace shared
