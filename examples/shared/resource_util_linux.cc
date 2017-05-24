// Copyright (c) 2017 The Chromium Embedded Framework Authors.
// Portions copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "examples/shared/resource_util.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

namespace shared {

bool GetResourceDir(std::string& dir) {
  char buff[1024];

  // Retrieve the executable path.
  ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff) - 1);
  if (len == -1)
    return false;

  buff[len] = 0;

  // Add "_files" to the path.
  strcpy(buff + len, "_files");
  dir = std::string(buff);
  return true;
}

}  // namespace shared
