# Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from glob import iglob
import sys


def read_file(name, normalize=True):
  """ Read a file. """
  try:
    f = open(name, 'r')
    # read the data
    data = f.read()
    if normalize:
      # normalize line endings
      data = data.replace("\r\n", "\n")
    return data
  except IOError, (errno, strerror):
    sys.stderr.write('Failed to read file ' + name + ': ' + strerror)
    raise
  else:
    f.close()


def write_file(name, data):
  """ Write a file. """
  try:
    f = open(name, 'w')
    # write the data
    f.write(data)
  except IOError, (errno, strerror):
    sys.stderr.write('Failed to write file ' + name + ': ' + strerror)
    raise
  else:
    f.close()


def get_files(search_glob):
  """ Returns all files matching the search glob. """
  # Sort the result for consistency across platforms.
  return sorted(iglob(search_glob))


def eval_file(src):
  """ Loads and evaluates the contents of the specified file. """
  return eval(read_file(src), {'__builtins__': None}, None)
