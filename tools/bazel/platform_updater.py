#!/usr/bin/env python3
# Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from bazel_util import bazel_substitute, bazel_last_error
from optparse import OptionParser
import os
import platform as python_platform
import sys

# Script directory.
script_dir = os.path.dirname(__file__)
root_script_dir = os.path.realpath(os.path.join(script_dir, os.pardir))
root_dir = os.path.realpath(os.path.join(root_script_dir, os.pardir))

sys.path.append(root_script_dir)

from file_util import read_file, write_file_if_changed

description = """
Use the following command to update platform information:
% python3 ./tools/bazel/platform_updater.py [--arch=x86|x64|arm64|arm]

This must be configured before running Bazel for the first time, or when a
new target architecture is desired.

By default (with no `--arch` argument), the host platform and architecture
will be selected. Optionally specify a different architecture for cross-
compilation. See the list of available architecture values below.
"""


def get_description():
  lines = [
      "",
      "THIS FILE IS AUTO-GENERATED. DO NOT EDIT BY HAND.",
  ] + description.split("\n") + get_config_desc().split("\n")
  return "\n".join([("# " + l).strip() for l in lines])


def get_config_desc(selected=None):
  str = "Host platform:      %s\nHost architecture:  %s\n\n" % (get_host_os(),
                                                                get_host_arch())
  str += "CEF architectures and platforms available to build on this host:\n"
  default = get_host_platform()
  for arch, platform in get_available_platforms().items():
    tags = []
    if platform == default:
      tags.append('default')
    if platform == selected:
      tags.append('selected')
    tag_str = '' if len(tags) == 0 else ("[%s]" % ', '.join(tags))
    str += "  %7s = %-12s %s\n" % (arch, platform, tag_str)
  return str


def get_cmds(selected):
  cmds = []
  if selected != get_host_platform():
    # Commands related to cross-compilation.
    cmd_map = {
        "windows32": "--cpu=x64_x86_windows",
        "windows64": "--cpu=x64_windows",
        "windowsarm64": "--cpu=arm64_windows",
        "macosx64": "--cpu=darwin_x86_64",
        "macosarm64": "--cpu=darwin_arm64",
        "linux64": "--cpu=x86_64",
        "linuxarm64": "--cpu=aarch64",
        "linuxarm": "--cpu=armv7",
    }
    if selected in cmd_map:
      cmds.append(cmd_map[selected])
  return cmds


def get_warnings(selected):
  warnings = []
  if selected != get_host_platform():
    # Warnings related to cross-compilation.
    if selected.startswith('windows'):
      warnings.append("Windows cross-compile builds using Bazel may be broken, see\n" \
                      "https://github.com/bazelbuild/bazel/issues/22164")
    elif selected.startswith('linux'):
      warnings.append("Linux cross-compile builds using Bazel may be broken, see\n" \
                      "https://github.com/bazelbuild/examples/issues/173")
  return warnings


def exit_with_error(error):
  sys.stderr.write("ERROR: %s\n" % error)
  sys.stderr.write(description)
  sys.stderr.write("\n" + get_config_desc() + "\n")
  sys.exit(1)


# Overrides for testing.
TEST_HOST_OS = None
TEST_HOST_ARCH = None


def get_host_os():
  if not TEST_HOST_OS is None:
    return TEST_HOST_OS

  if sys.platform == 'win32':
    return 'windows'
  if sys.platform == 'darwin':
    return 'macos'
  if sys.platform.startswith('linux'):
    return 'linux'
  return ''


def get_host_arch():
  if not TEST_HOST_ARCH is None:
    return TEST_HOST_ARCH

  # Windows: i386, AMD64, ARM64
  # MacOS:   x86_64, arm64
  # Linux:   i386, x86_64, aarch64, armv7l
  mach = python_platform.machine()
  if mach in ('AMD64', 'x86_64'):
    return 'x64'
  if mach == 'i386':
    return 'x86'
  if mach in ('ARM64', 'arm64', 'aarch64'):
    return 'arm64'
  if mach == 'armv7l':
    return 'arm'
  return ''


def get_available_platforms():
  # Map of available host architecture to CEF platform.
  os = get_host_os()
  if os == 'windows':
    return {
        'x86': 'windows32',
        'x64': 'windows64',
        'arm64': 'windowsarm64',
    }
  if os == 'macos':
    return {
        'x64': 'macosx64',
        'arm64': 'macosarm64',
    }
  if os == 'linux':
    return {
        'x64': 'linux64',
        'arm64': 'linuxarm64',
        'arm': 'linuxarm',
    }
  return {}


def get_host_platform():
  # Returns None for unknown platform.
  return get_available_platforms().get(get_host_arch(), None)


def is_available_arch(arch):
  return arch in get_available_platforms()


def get_platform(arch):
  return get_available_platforms()[arch]


# Cannot be loaded as a module.
if __name__ != "__main__":
  exit_with_error('This file cannot be loaded as a module!')

# Parse command-line options.
parser = OptionParser()
parser.add_option(
    '--arch',
    dest='arch',
    help='CEF target architecture.',
    default=get_host_arch())
parser.add_option(
    '--test-host-os',
    dest='testhostos',
    help='Override the host OS for testing.')
parser.add_option(
    '--test-host-arch',
    dest='testhostarch',
    help='Override the host architecture for testing.')
(options, args) = parser.parse_args()

# Overrides for testing.
if not options.testhostos is None:
  TEST_HOST_OS = options.testhostos
if not options.testhostarch is None:
  TEST_HOST_ARCH = options.testhostarch

arch = options.arch
if not is_available_arch(arch):
  exit_with_error('Invalid arch value.')

platform = get_platform(arch)
if platform is None:
  exit_with_error('Platform could not be determined.')

out_file = os.path.join(root_dir, 'bazel', 'cef', 'platform.bzl')
in_file = out_file + '.in'
if not os.path.isfile(in_file):
  exit_with_error('Missing input file %s' % in_file)

variables = {
    'description': get_description(),
    'platform': platform,
}

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

print("\n" + get_config_desc(selected=platform))

cmds = get_cmds(selected=platform)
print("NOW RUN:\n%% bazel build %s%s[target]\n" % (" ".join(cmds), ' '
                                                   if len(cmds) > 0 else ''))

warnings = get_warnings(selected=platform)
if len(warnings) > 0:
  print("WARNING:\n" + "\n".join(warnings) + "\n")
