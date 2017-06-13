// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/browser_util.h"

#include <cstring>

#include "examples/scheme_handler/resources/win/resource.h"

namespace shared {

int GetResourceId(const std::string& resource_path) {
  if (resource_path == "logo.png")
    return IDS_LOGO_PNG;
  if (resource_path == "scheme_handler.html")
    return IDS_SCHEME_HANDLER_HTML;
  return 0;
}

}  // namespace shared
