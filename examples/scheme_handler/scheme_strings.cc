// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/scheme_handler/scheme_strings.h"

#include "include/internal/cef_types.h"

namespace scheme_handler {

const char kScheme[] = "client";
const char kDomain[] = "tests";
const char kFileName[] = "scheme_handler.html";

const int kSchemeRegistrationOptions =
    CEF_SCHEME_OPTION_STANDARD | CEF_SCHEME_OPTION_SECURE |
    CEF_SCHEME_OPTION_CORS_ENABLED | CEF_SCHEME_OPTION_FETCH_ENABLED;

}  // namespace scheme_handler
