// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/browser_util.h"

#include <cstring>

#include "examples/message_router/resources/win/resource.h"

namespace shared {

int GetResourceId(const std::string& resource_path) {
  if (resource_path == "message_router.html")
    return IDS_MESSAGE_ROUTER_HTML;
  return 0;
}

}  // namespace shared
