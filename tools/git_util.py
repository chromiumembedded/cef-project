# Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file

from exec_util import exec_cmd
import sys

# Git must be in the system PATH.
git_exe = 'git'


def get_changed_files(path, hash):
  """ Retrieves the list of changed files. """
  if hash == 'unstaged':
    cmd = "%s diff --name-only" % git_exe
  elif hash == 'staged':
    cmd = "%s diff --name-only --cached" % git_exe
  else:
    cmd = "%s diff-tree --no-commit-id --name-only -r %s" % (git_exe, hash)
  result = exec_cmd(cmd, path)
  if result['out'] != '':
    files = result['out']
    if sys.platform == 'win32':
      # Convert to Unix line endings.
      files = files.replace('\r\n', '\n')
    return files.strip().split("\n")
  return []
