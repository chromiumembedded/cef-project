// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_RESOURCE_MANAGER_CLIENT_IMPL_H_
#define CEF_EXAMPLES_RESOURCE_MANAGER_CLIENT_IMPL_H_

#include "include/cef_client.h"
#include "include/wrapper/cef_resource_manager.h"

namespace resource_manager {

// Implementation of client handlers.
class Client : public CefClient,
               public CefDisplayHandler,
               public CefLifeSpanHandler,
               public CefRequestHandler,
               public CefResourceRequestHandler {
 public:
  Client();

  // CefClient methods:
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }

  // CefDisplayHandler methods:
  void OnTitleChange(CefRefPtr<CefBrowser> browser,
                     const CefString& title) override;

  // CefLifeSpanHandler methods:
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  bool DoClose(CefRefPtr<CefBrowser> browser) override;
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  // CefRequestHandler methods:
  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request,
      bool is_navigation,
      bool is_download,
      const CefString& request_initiator,
      bool& disable_default_handling) override;

  // CefResourceRequestHandler methods:
  cef_return_value_t OnBeforeResourceLoad(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request,
      CefRefPtr<CefCallback> callback) override;
  CefRefPtr<CefResourceHandler> GetResourceHandler(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request) override;

 private:
  // Manages the registration and delivery of resources.
  CefRefPtr<CefResourceManager> resource_manager_;

  IMPLEMENT_REFCOUNTING(Client);
  DISALLOW_COPY_AND_ASSIGN(Client);
};

}  // namespace resource_manager

#endif  // CEF_EXAMPLES_RESOURCE_MANAGER_CLIENT_IMPL_H_
