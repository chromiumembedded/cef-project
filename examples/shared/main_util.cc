// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/main_util.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace shared {

namespace {

// These flags must match the Chromium values.
const char kProcessType[] = "type";
const char kRendererProcess[] = "renderer";
#if defined(OS_LINUX)
const char kZygoteProcess[] = "zygote";
#endif

}  // namespace

CefRefPtr<CefCommandLine> CreateCommandLine(const CefMainArgs& main_args) {
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
#if defined(OS_WIN)
  command_line->InitFromString(::GetCommandLineW());
#else
  command_line->InitFromArgv(main_args.argc, main_args.argv);
#endif
  return command_line;
}

ProcessType GetProcessType(const CefRefPtr<CefCommandLine>& command_line) {
  // The command-line flag won't be specified for the browser process.
  if (!command_line->HasSwitch(kProcessType))
    return PROCESS_TYPE_BROWSER;

  const std::string& process_type = command_line->GetSwitchValue(kProcessType);
  if (process_type == kRendererProcess)
    return PROCESS_TYPE_RENDERER;

#if defined(OS_LINUX)
  // On Linux the zygote process is used to spawn other process types. Since we
  // don't know what type of process it will be we give it the renderer app.
  if (process_type == kZygoteProcess)
    return PROCESS_TYPE_RENDERER;
#endif

  return PROCESS_TYPE_OTHER;
}

}  // namespace shared
