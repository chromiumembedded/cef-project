// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_EXAMPLES_SHARED_APP_UTIL_H_
#define CEF_EXAMPLES_SHARED_APP_UTIL_H_

#include "include/cef_command_line.h"

namespace shared {

// This file provides functionality common to all program entry point
// implementations.

// Create a new CommandLine object for use before CEF initialization.
CefRefPtr<CefCommandLine> CreateCommandLine(const CefMainArgs& main_args);

// Process types that may have different CefApp instances.
enum ProcessType {
  PROCESS_TYPE_BROWSER,
  PROCESS_TYPE_RENDERER,
  PROCESS_TYPE_OTHER,
};

// Determine the process type based on command-line arguments.
ProcessType GetProcessType(const CefRefPtr<CefCommandLine>& command_line);

}  // namespace shared

#endif  // CEF_EXAMPLES_SHARED_APP_UTIL_H_
