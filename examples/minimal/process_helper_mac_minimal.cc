// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "examples/shared/process_helper_mac.h"

// Helper sub-process program entry point function.
int main(int argc, char* argv[]) {
  return shared::main(argc, argv);
}
