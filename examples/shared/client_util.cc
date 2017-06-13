// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/client_util.h"

#include <sstream>
#include <string>

#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

#include "examples/shared/client_manager.h"

namespace shared {

void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {
  CEF_REQUIRE_UI_THREAD();

#if defined(OS_WIN) || defined(OS_LINUX)
  // The Views framework is currently only supported on Windows and Linux.
  CefRefPtr<CefBrowserView> browser_view =
      CefBrowserView::GetForBrowser(browser);
  if (browser_view) {
    // Set the title of the window using the Views framework.
    CefRefPtr<CefWindow> window = browser_view->GetWindow();
    if (window)
      window->SetTitle(title);
  } else
#endif
  {
    // Set the title of the window using platform APIs.
    PlatformTitleChange(browser, title);
  }
}

void OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Add to the list of existing browsers.
  ClientManager::GetInstance()->OnAfterCreated(browser);
}

bool DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Closing the main window requires special handling. See the DoClose()
  // documentation in the CEF header for a detailed destription of this
  // process.
  ClientManager::GetInstance()->DoClose(browser);

  // Allow the close. For windowed browsers this will result in the OS close
  // event being sent.
  return false;
}

void OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Remove from the list of existing browsers.
  ClientManager::GetInstance()->OnBeforeClose(browser);
}

std::string DumpRequestContents(CefRefPtr<CefRequest> request) {
  std::stringstream ss;

  ss << "URL: " << std::string(request->GetURL());
  ss << "\nMethod: " << std::string(request->GetMethod());

  CefRequest::HeaderMap headerMap;
  request->GetHeaderMap(headerMap);
  if (headerMap.size() > 0) {
    ss << "\nHeaders:";
    CefRequest::HeaderMap::const_iterator it = headerMap.begin();
    for (; it != headerMap.end(); ++it) {
      ss << "\n\t" << std::string((*it).first) << ": "
         << std::string((*it).second);
    }
  }

  CefRefPtr<CefPostData> postData = request->GetPostData();
  if (postData.get()) {
    CefPostData::ElementVector elements;
    postData->GetElements(elements);
    if (elements.size() > 0) {
      ss << "\nPost Data:";
      CefRefPtr<CefPostDataElement> element;
      CefPostData::ElementVector::const_iterator it = elements.begin();
      for (; it != elements.end(); ++it) {
        element = (*it);
        if (element->GetType() == PDE_TYPE_BYTES) {
          // the element is composed of bytes
          ss << "\n\tBytes: ";
          if (element->GetBytesCount() == 0) {
            ss << "(empty)";
          } else {
            // retrieve the data.
            size_t size = element->GetBytesCount();
            char* bytes = new char[size];
            element->GetBytes(size, bytes);
            ss << std::string(bytes, size);
            delete[] bytes;
          }
        } else if (element->GetType() == PDE_TYPE_FILE) {
          ss << "\n\tFile: " << std::string(element->GetFile());
        }
      }
    }
  }

  return ss.str();
}

}  // namespace shared
