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

CEF_VERSION = "127.1.5+g35f74cc+chromium-127.0.6533.89"

# Map of supported platform to sha256 for binary distribution download.
CEF_FILE_SHA256 = {
    "windows32": "8f7fc81aad0341ac176964f105d28ea67d5fc70f3281b90e8985901f37f0ce2b",
    "windows64": "83884e6378cabeb761a1a8f0e89e8493dd2f2fe43595f3991d5bcd903fa626a7",
    "windowsarm64": "9dcf3fed173add7eb235a894e0775a107afc21274dc44d2b298788ed9cc69b5f",
    "macosx64": "db730776cb266508e36a7d3e156ef4d80b298673d29e280525cd6151f2097811",
    "macosarm64": "1ef2073b72f9080fe291a1b0ec39ba636fa752703ec67a0be39148e0bb860a07",
    "linux64": "b8d4399b05430d53cd1e3946164bb17c013c19f2ee2ef5d7036f8e3f9573dad5",
    "linuxarm64": "c7a480ea476709f8eb9ffdb6d68fafb9bbbd3e685cb734edf2d3c3038e113d67",
    "linuxarm": "95c7d9bff29d22eb49bedd76041462d41ddcb65efd83133b2c7f7f6b0efe4380",
}
