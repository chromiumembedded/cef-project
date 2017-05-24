// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/resource_util.h"

#include "include/base/cef_logging.h"
#include "include/wrapper/cef_byte_read_handler.h"
#include "include/wrapper/cef_stream_resource_handler.h"

namespace shared {

namespace {

// Retrieve the contents of a BINARY resource from the current executable.
bool LoadBinaryResource(int binaryId, DWORD& dwSize, LPBYTE& pBytes) {
  HINSTANCE hInst = GetModuleHandle(NULL);
  HRSRC hRes =
      FindResource(hInst, MAKEINTRESOURCE(binaryId), MAKEINTRESOURCE(256));
  if (hRes) {
    HGLOBAL hGlob = LoadResource(hInst, hRes);
    if (hGlob) {
      dwSize = SizeofResource(hInst, hRes);
      pBytes = (LPBYTE)LockResource(hGlob);
      if (dwSize > 0 && pBytes)
        return true;
    }
  }

  return false;
}

// Provider implementation for loading BINARY resources from the current
// executable.
class BinaryResourceProvider : public CefResourceManager::Provider {
 public:
  explicit BinaryResourceProvider(const std::string& root_url)
      : root_url_(root_url) {
    DCHECK(!root_url.empty());
  }

  bool OnRequest(scoped_refptr<CefResourceManager::Request> request) OVERRIDE {
    CEF_REQUIRE_IO_THREAD();

    const std::string& url = request->url();
    if (url.find(root_url_) != 0L) {
      // Not handled by this provider.
      return false;
    }

    CefRefPtr<CefResourceHandler> handler;

    const std::string& relative_path = url.substr(root_url_.length());
    if (!relative_path.empty()) {
      CefRefPtr<CefStreamReader> stream =
          GetResourceReader(relative_path.data());
      if (stream.get()) {
        handler = new CefStreamResourceHandler(
            request->mime_type_resolver().Run(url), stream);
      }
    }

    request->Continue(handler);
    return true;
  }

 private:
  std::string root_url_;

  DISALLOW_COPY_AND_ASSIGN(BinaryResourceProvider);
};

}  // namespace

CefResourceManager::Provider* CreateBinaryResourceProvider(
    const std::string& url_path) {
  return new BinaryResourceProvider(url_path);
}

bool GetResourceString(const std::string& resource_path,
                       std::string& out_data) {
  int resource_id = GetResourceId(resource_path);
  if (resource_id == 0)
    return false;

  DWORD dwSize;
  LPBYTE pBytes;

  if (LoadBinaryResource(resource_id, dwSize, pBytes)) {
    out_data = std::string(reinterpret_cast<char*>(pBytes), dwSize);
    return true;
  }

  NOTREACHED();  // The resource should be found.
  return false;
}

CefRefPtr<CefStreamReader> GetResourceReader(const std::string& resource_path) {
  int resource_id = GetResourceId(resource_path);
  if (resource_id == 0)
    return NULL;

  DWORD dwSize;
  LPBYTE pBytes;

  if (LoadBinaryResource(resource_id, dwSize, pBytes)) {
    return CefStreamReader::CreateForHandler(
        new CefByteReadHandler(pBytes, dwSize, NULL));
  }

  NOTREACHED();  // The resource should be found.
  return NULL;
}

}  // namespace shared
