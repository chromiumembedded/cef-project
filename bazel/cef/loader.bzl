# Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load(":platform.bzl", "CEF_PLATFORM")
load(":version.bzl", "CEF_DOWNLOAD_URL", "CEF_VERSION", "CEF_FILE_SHA256")

def load_cef_repo(name = "cef",
                  version = CEF_VERSION,
                  platform = CEF_PLATFORM,
                  url = CEF_DOWNLOAD_URL):
    """
    Download, extract and load a CEF binary distribution.
    """
    file_name = "cef_binary_{}_{}".format(version, platform)

    http_archive(
        name = name,
        sha256 = CEF_FILE_SHA256[platform],
        strip_prefix = file_name,
        url = "{}{}.tar.bz2".format(url, file_name),
        repo_mapping = {"@cef": "@{}".format(name)}
    )

def load_local_cef_repo(path,
                        name = "cef",
                        version = CEF_VERSION,
                        platform = CEF_PLATFORM):
    """
    Load an already downloaded/extracted CEF binary distribution.
    """
    native.local_repository(
        name = "cef",
        path = "{}/cef_binary_{}_{}".format(path, version, platform),
        repo_mapping = {"@cef": "@{}".format(name)}
    )
