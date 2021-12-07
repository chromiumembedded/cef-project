// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/resource_manager/client_impl.h"

#include <sstream>

#include "include/wrapper/cef_helpers.h"
#include "include/wrapper/cef_stream_resource_handler.h"

#include "examples/shared/client_util.h"
#include "examples/shared/resource_util.h"

namespace resource_manager {

namespace {

// Demonstrate a custom Provider implementation by dumping the request contents.
class RequestDumpResourceProvider : public CefResourceManager::Provider {
 public:
  explicit RequestDumpResourceProvider(const std::string& url) : url_(url) {
    DCHECK(!url.empty());
  }

  bool OnRequest(scoped_refptr<CefResourceManager::Request> request) override {
    CEF_REQUIRE_IO_THREAD();

    const std::string& url = request->url();
    if (url != url_) {
      // Not handled by this provider.
      return false;
    }

    const std::string& dump = shared::DumpRequestContents(request->request());
    std::string str =
        "<html><body bgcolor=\"white\"><pre>" + dump + "</pre></body></html>";
    CefRefPtr<CefStreamReader> stream = CefStreamReader::CreateForData(
        static_cast<void*>(const_cast<char*>(str.c_str())), str.size());
    DCHECK(stream.get());
    request->Continue(new CefStreamResourceHandler("text/html", stream));
    return true;
  }

 private:
  std::string url_;

  DISALLOW_COPY_AND_ASSIGN(RequestDumpResourceProvider);
};

// Add example Providers to the CefResourceManager.
void SetupResourceManager(CefRefPtr<CefResourceManager> resource_manager) {
  if (!CefCurrentlyOn(TID_IO)) {
    // Execute on the browser IO thread.
    CefPostTask(TID_IO, base::BindOnce(SetupResourceManager, resource_manager));
    return;
  }

  const std::string& test_origin = shared::kTestOrigin;

  // Add the Provider for dumping request contents.
  resource_manager->AddProvider(
      new RequestDumpResourceProvider(test_origin + "request.html"), 0,
      std::string());

// Add the Provider for bundled resource files.
#if defined(OS_WIN)
  // Read BINARY resources from the executable.
  resource_manager->AddProvider(
      shared::CreateBinaryResourceProvider(test_origin), 100, std::string());
#elif defined(OS_POSIX)
  // Read individual resource files from a directory on disk.
  std::string resource_dir;
  if (shared::GetResourceDir(resource_dir)) {
    resource_manager->AddDirectoryProvider(test_origin, resource_dir, 100,
                                           std::string());
  }
#endif
}

}  // namespace

Client::Client() {
  resource_manager_ = new CefResourceManager();
  SetupResourceManager(resource_manager_);
}

void Client::OnTitleChange(CefRefPtr<CefBrowser> browser,
                           const CefString& title) {
  // Call the default shared implementation.
  shared::OnTitleChange(browser, title);
}

void Client::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  // Call the default shared implementation.
  shared::OnAfterCreated(browser);
}

bool Client::DoClose(CefRefPtr<CefBrowser> browser) {
  // Call the default shared implementation.
  return shared::DoClose(browser);
}

void Client::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  // Call the default shared implementation.
  return shared::OnBeforeClose(browser);
}

CefRefPtr<CefResourceRequestHandler> Client::GetResourceRequestHandler(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefRequest> request,
    bool is_navigation,
    bool is_download,
    const CefString& request_initiator,
    bool& disable_default_handling) {
  CEF_REQUIRE_IO_THREAD();
  return this;
}

cef_return_value_t Client::OnBeforeResourceLoad(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefRequest> request,
    CefRefPtr<CefCallback> callback) {
  CEF_REQUIRE_IO_THREAD();

  return resource_manager_->OnBeforeResourceLoad(browser, frame, request,
                                                 callback);
}

CefRefPtr<CefResourceHandler> Client::GetResourceHandler(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefRequest> request) {
  CEF_REQUIRE_IO_THREAD();

  return resource_manager_->GetResourceHandler(browser, frame, request);
}

}  // namespace resource_manager
