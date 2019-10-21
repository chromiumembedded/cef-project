// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_SCHEME_HANDLER_SCHEME_STRINGS_H_
#define CEF_EXAMPLES_SCHEME_HANDLER_SCHEME_STRINGS_H_

namespace scheme_handler {

extern const char kScheme[];
extern const char kDomain[];
extern const char kFileName[];

// Used to register a custom scheme as standard and secure.
extern const int kSchemeRegistrationOptions;

}  // namespace scheme_handler

#endif  // CEF_EXAMPLES_SCHEME_HANDLER_SCHEME_STRINGS_H_
