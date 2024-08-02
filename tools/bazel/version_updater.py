#!/usr/bin/env python3
# Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from bazel_util import bazel_substitute, bazel_last_error
from optparse import OptionParser
import os
import re
import sys
from urllib.error import HTTPError, URLError
import urllib.request

# Script directory.
script_dir = os.path.dirname(__file__)
root_script_dir = os.path.realpath(os.path.join(script_dir, os.pardir))
root_dir = os.path.realpath(os.path.join(root_script_dir, os.pardir))

sys.path.append(root_script_dir)

from file_util import read_file, write_file_if_changed

CEF_DOWNLOAD_URL = "https://cef-builds.spotifycdn.com/"

CEF_PLATFORMS = ("windows32", "windows64", "windowsarm64", "macosx64",
                 "macosarm64", "linux64", "linuxarm64", "linuxarm")

description = """
Use the following command to update version information:
% python3 ./tools/bazel/version_updater.py --version=<version> [--url=<url>]

Specify a fully-qualified CEF version. Optionally override the default
download URL.

CEF binary distribution file names are expected to take the form
"cef_binary_<version>_<platform>.tar.bz2". These files must exist for each
supported platform at the download URL location. Sha256 hashes must also
exist for each file at "<file_name>.sha256".
"""


def get_description():
  lines = [
      "",
      "THIS FILE IS AUTO-GENERATED. DO NOT EDIT BY HAND.",
  ] + description.split("\n")
  return "\n".join([("# " + l).strip() for l in lines])


def exit_with_error(error):
  sys.stderr.write("ERROR: %s\n" % error)
  sys.stderr.write(description + "\n")
  sys.exit(1)


# Check if the CEF version number format is valid. The format is documented at
# https://bitbucket.org/chromiumembedded/cef/wiki/BranchesAndBuilding.md#markdown-header-version-number-format
# Code from https://bitbucket.org/chromiumembedded/cef/src/master/tools/cefbuilds/cef_json_builder.py
def is_valid_version(version):
  _chromium_version_regex = r'[1-9]{1}[0-9]{1,2}\.0\.[1-9]{1}[0-9]{2,4}\.(0|[1-9]{1}[0-9]{0,2})'
  _cef_hash_regex = r'g[0-9a-f]{7}'
  _cef_number_regex = r'[0-9]{1,5}\.[0-9]{1,5}\.[0-9]{1,5}'

  # Example: 3.2704.1414.g185cd6c
  _cef_old_version_regex = _cef_number_regex + r'\.' + _cef_hash_regex
  # Example: 74.0.1+g62d140e+chromium-74.0.3729.6
  _cef_version_release_regex = _cef_number_regex + r'\+' + _cef_hash_regex + \
                              r'\+chromium\-' + _chromium_version_regex
  # Example: 74.0.0-master.1920+g725ed88+chromium-74.0.3729.0
  _cef_version_dev_regex = _cef_number_regex + r'\-\w+\.[0-9]{1,7}\+' + _cef_hash_regex + \
                           r'\+chromium\-' + _chromium_version_regex

  return bool(re.compile(r'^' + _cef_old_version_regex + r'$').match(version)) \
      or bool(re.compile(r'^' + _cef_version_release_regex + r'$').match(version)) \
      or bool(re.compile(r'^' + _cef_version_dev_regex + r'$').match(version))


def is_valid_sha256(sha256):
  if sha256 is None:
    return False
  return bool(re.compile(r'^[0-9a-f]{64}$').match(sha256))


def download_url(url):
  # Attempt to download a URL.
  try:
    with urllib.request.urlopen(url) as f:
      return f.read().decode('utf-8')
  except HTTPError as e:
    exit_with_error("Download of %s failed with error code %d" % (url, e.code))
  except URLError as e:
    exit_with_error("Download of %s failed with reason %s" % (url, e.reason))
  return None


# Cannot be loaded as a module.
if __name__ != "__main__":
  exit_with_error('This file cannot be loaded as a module!')

# Parse command-line options.
parser = OptionParser()
parser.add_option(
    '--version', dest='version', help='CEF version to download [required].')
parser.add_option('--url', dest='url',
                  help='CEF download URL. If not specified the default URL '+\
                       'will be used.',
                  default=CEF_DOWNLOAD_URL)
(options, args) = parser.parse_args()

version = options.version
if version is None:
  exit_with_error('Version parameter is required.')
if not is_valid_version(version):
  exit_with_error('Invalid version format.')

out_file = os.path.join(root_dir, 'bazel', 'cef', 'version.bzl')
in_file = out_file + '.in'
if not os.path.isfile(in_file):
  exit_with_error('Missing input file %s' % in_file)

variables = {
    'description': get_description(),
    'version': version,
    'url': options.url,
}

print("Downloading sha256 values...")
for platform in CEF_PLATFORMS:
  url = "%scef_binary_%s_%s.tar.bz2.sha256" % (options.url, version, platform)
  sha256 = download_url(url)
  if not is_valid_sha256(sha256):
    exit_with_error('Missing or invalid sha256 from %s' % url)
  variables["%s_sha256" % platform] = sha256

changed = False
output = bazel_substitute(read_file(in_file), variables, label=in_file)
if bazel_last_error() is None and len(output) > 0:
  changed = write_file_if_changed(out_file, output)
else:
  exit_with_error('Failed to parse template file %s' % in_file)

if changed:
  print("Successfully updated: %s" % out_file)
else:
  print("Already up to date: %s" % out_file)

print("\nConfigured version: %s\n" % version)
