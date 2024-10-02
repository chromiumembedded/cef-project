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

CEF_VERSION = "129.0.10+ge52707f+chromium-129.0.6668.71"

# Map of supported platform to sha256 for binary distribution download.
CEF_FILE_SHA256 = {
    "windows32": "2b6cf1b9f16ce2ae57b4b0b5c23744befe4b439dd4a38fd1f9ce2bcf03f068d5",
    "windows64": "3d4d8ddf7d54b966709fd41e1f0091d27e194af4d17d8cf15990cda43e1e9e1d",
    "windowsarm64": "59b20ccc0ed8a23e6ad895c76621fec696b0846a4ad0441fedc99ec16e79d140",
    "macosx64": "0e21d702fd8368537b154569a1f438d4d712e7810479caa20c3b7648746a2077",
    "macosarm64": "adef9d87497ece72e4fc8af8fba4f1fbe3b26edf6c542540a9297c6424a56440",
    "linux64": "914a4aa8fd961b6e1e5e3a48bbd3f62ee53450312f6bcadf9bfd00c61a49aba0",
    "linuxarm64": "3f909cfc66c444ef38ec7e8abb9ba6571e250949f4f92ea490443df89fd00c2b",
    "linuxarm": "03feca3482b8b3734bf9f3f5525ecaf7448fc906f34480e951a16fcd609e3ac2",
}
