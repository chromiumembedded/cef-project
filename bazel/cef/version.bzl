# Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

#
# THIS FILE IS AUTO-GENERATED. DO NOT EDIT BY HAND.
#
# Use the following command to update version information:
# % python3 ./tools/bazel/version_updater.py --version=<version> [--url=<url>]
#
# Specify a fully-qualified CEF version. Optionally override the default
# download URL.
#
# CEF binary distribution file names are expected to take the form
# "cef_binary_<version>_<platform>.tar.bz2". These files must exist for each
# supported platform at the download URL location. Sha256 hashes must also
# exist for each file at "<file_name>.sha256".
#

CEF_DOWNLOAD_URL = "https://cef-builds.spotifycdn.com/"

CEF_VERSION = "127.3.1+g6cbb30e+chromium-127.0.6533.100"

# Map of supported platform to sha256 for binary distribution download.
CEF_FILE_SHA256 = {
    "windows32": "4793287bc00d6f6b0d6ae290c6151d38731db50d9c19f92fd0bb0e0fa01e9ffe",
    "windows64": "65e3fa3e1f029f9cb18fb7ac3127c969c3d5a909af42d238135c1124d6dc5dc2",
    "windowsarm64": "db99ce8414b72436dd4134895a9c3bc21e9cc008abdc1fdff4505f356df8c3f0",
    "macosx64": "a20928b74bf90e07eedd5f675c060f988b20ee33faa0446d2d885997688de32a",
    "macosarm64": "e5e2d9f7dcc0958200cc1513682aee0b8c5a7c26d3d7eb9a3386f1a729b082f7",
    "linux64": "81e905a94bdf911ad1c45255fbae02ce4e05c7d6645cac4e3f64731380ecc430",
    "linuxarm64": "1983c5e37c98eaadefcc34fd47af4ce9ed1848eb98c0367f7cd404a2baaa381a",
    "linuxarm": "99c6cc78b7029557398820bca93577dba9d947e19103542f8dbcc8d9a342143a",
}
