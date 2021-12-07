// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_MESSAGE_ROUTER_CLIENT_IMPL_H_
#define CEF_EXAMPLES_MESSAGE_ROUTER_CLIENT_IMPL_H_

#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"

namespace message_router {

// Implementation of client handlers.
class Client : public CefClient,
               public CefDisplayHandler,
               public CefLifeSpanHandler,
               public CefRequestHandler,
               public CefResourceRequestHandler {
 public:
  explicit Client(const CefString& startup_url);

  // CefClient methods:
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
  bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) override;

  // CefDisplayHandler methods:
  void OnTitleChange(CefRefPtr<CefBrowser> browser,
                     const CefString& title) override;

  // CefLifeSpanHandler methods:
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  bool DoClose(CefRefPtr<CefBrowser> browser) override;
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  // CefRequestHandler methods:
  bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                      CefRefPtr<CefFrame> frame,
                      CefRefPtr<CefRequest> request,
                      bool user_gesture,
                      bool is_redirect) override;
  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request,
      bool is_navigation,
      bool is_download,
      const CefString& request_initiator,
      bool& disable_default_handling) override;
  void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                 TerminationStatus status) override;

  // CefResourceRequestHandler methods:
  CefRefPtr<CefResourceHandler> GetResourceHandler(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request) override;

 private:
  // Handles the browser side of query routing.
  CefRefPtr<CefMessageRouterBrowserSide> message_router_;
  std::unique_ptr<CefMessageRouterBrowserSide::Handler> message_handler_;

  const CefString startup_url_;

  // Track the number of browsers using this Client.
  int browser_ct_;

  IMPLEMENT_REFCOUNTING(Client);
  DISALLOW_COPY_AND_ASSIGN(Client);
};

}  // namespace message_router

#endif  // CEF_EXAMPLES_MESSAGE_ROUTER_CLIENT_IMPL_H_
