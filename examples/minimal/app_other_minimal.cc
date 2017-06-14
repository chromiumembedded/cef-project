// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/app_factory.h"

namespace shared {

// No CefApp for other subprocesses.
CefRefPtr<CefApp> CreateOtherProcessApp() {
  return NULL;
}

}  // namespace shared
