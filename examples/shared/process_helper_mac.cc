// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "examples/shared/process_helper_mac.h"

#include "include/cef_app.h"

#include "examples/shared/app_factory.h"
#include "examples/shared/main_util.h"

namespace shared {

// Entry point function for sub-processes.
int main(int argc, char* argv[]) {
  // Provide CEF with command-line arguments.
  CefMainArgs main_args(argc, argv);

  // Create a temporary CommandLine object.
  CefRefPtr<CefCommandLine> command_line = CreateCommandLine(main_args);

  // Create a CefApp of the correct process type. The browser process is handled
  // by main_mac.mm.
  CefRefPtr<CefApp> app;
  switch (GetProcessType(command_line)) {
    case PROCESS_TYPE_RENDERER:
      app = CreateRendererProcessApp();
      break;
    case PROCESS_TYPE_OTHER:
      app = CreateOtherProcessApp();
      break;
    default:
      break;
  }

  // Execute the sub-process.
  return CefExecuteProcess(main_args, app, NULL);
}

}  // namespace shared
