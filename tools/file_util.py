# Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from __future__ import absolute_import
from glob import iglob
from io import open
import sys


def read_file(name, normalize=True):
  """ Read a file. """
  try:
    with open(name, 'r', encoding='utf-8') as f:
      # read the data
      data = f.read()
      if normalize:
        # normalize line endings
        data = data.replace("\r\n", "\n")
      return data
  except IOError as e:
    (errno, strerror) = e.args
    sys.stderr.write('Failed to read file ' + name + ': ' + strerror)
    raise


def write_file(name, data):
  """ Write a file. """
  try:
    with open(name, 'w', encoding='utf-8') as f:
      # write the data
      if sys.version_info.major == 2:
        f.write(data.decode('utf-8'))
      else:
        f.write(data)
  except IOError as e:
    (errno, strerror) = e.args
    sys.stderr.write('Failed to write file ' + name + ': ' + strerror)
    raise


def get_files(search_glob):
  """ Returns all files matching the search glob. """
  # Sort the result for consistency across platforms.
  return sorted(iglob(search_glob))


def eval_file(src):
  """ Loads and evaluates the contents of the specified file. """
  return eval(read_file(src), {'__builtins__': None}, None)
