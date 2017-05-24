// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/client_manager.h"

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

namespace shared {

namespace {

ClientManager* g_manager = NULL;

}  // namespace

ClientManager::ClientManager() : is_closing_(false) {
  g_manager = this;
}

ClientManager::~ClientManager() {
  DCHECK(thread_checker_.CalledOnValidThread());
  DCHECK(browser_list_.empty());
  g_manager = NULL;
}

// static
ClientManager* ClientManager::GetInstance() {
  CEF_REQUIRE_UI_THREAD();
  DCHECK(g_manager);
  return g_manager;
}

void ClientManager::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  DCHECK(thread_checker_.CalledOnValidThread());

  // Add to the list of existing browsers.
  browser_list_.push_back(browser);
}

void ClientManager::DoClose(CefRefPtr<CefBrowser> browser) {
  DCHECK(thread_checker_.CalledOnValidThread());

  if (browser_list_.size() == 1U) {
    // The last browser window is closing.
    is_closing_ = true;
  }
}

void ClientManager::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  DCHECK(thread_checker_.CalledOnValidThread());

  // Remove from the list of existing browsers.
  BrowserList::iterator bit = browser_list_.begin();
  for (; bit != browser_list_.end(); ++bit) {
    if ((*bit)->IsSame(browser)) {
      browser_list_.erase(bit);
      break;
    }
  }

  if (browser_list_.empty()) {
    // All browser windows have closed. Quit the application message loop.
    CefQuitMessageLoop();
  }
}

void ClientManager::CloseAllBrowsers(bool force_close) {
  DCHECK(thread_checker_.CalledOnValidThread());

  if (browser_list_.empty())
    return;

  BrowserList::const_iterator it = browser_list_.begin();
  for (; it != browser_list_.end(); ++it)
    (*it)->GetHost()->CloseBrowser(force_close);
}

bool ClientManager::IsClosing() const {
  DCHECK(thread_checker_.CalledOnValidThread());
  return is_closing_;
}

}  // namespace shared
