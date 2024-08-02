# Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

workspace(name = "cef-project")

#
# Load the CEF binary distribution.
#

# Download, extract and load the distribution.
load("//bazel/cef:loader.bzl", "load_cef_repo")
load_cef_repo()

# To load a locally downloaded/extracted distribution use the following
# lines instead:
# load("//bazel/cef:loader.bzl", "load_local_cef_repo")
# load_local_cef_repo(path = "third_party/cef")

#
# Windows configuration.
#

# Configure windows SDK.
load("@cef//bazel/win:setup_sdk.bzl", "setup_sdk")
setup_sdk(name = "winsdk")

#
# Linux configuration.
#

# Configure Linux using pkg-config.
load("//bazel:external_local_repository.bzl", "external_local_repository")
external_local_repository(
    name="pkg_config",
    path="@cef//bazel/linux/pkg_config"
)
load("@pkg_config//:pkg_config.bzl", "pkg_config")

# Define packages used by @cef//tests/cefclient.

pkg_config(
    name = "gmodule2",
    pkg_name = "gmodule-2.0",
)

pkg_config(
    name = "gtk3",
    pkg_name = "gtk+-3.0",
)

pkg_config(
    name = "gthread2",
    pkg_name = "gthread-2.0",
)

pkg_config(
    name = "gtkprint3",
    pkg_name = "gtk+-unix-print-3.0",
)

pkg_config(
    name = "xi",
)

# Define packages used by @cef//tests/ceftests.

pkg_config(
    name = "glib2",
    pkg_name = "glib-2.0",
)

