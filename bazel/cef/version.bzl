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

CEF_VERSION = "127.3.4+ge9e2e14+chromium-127.0.6533.100"

# Map of supported platform to sha256 for binary distribution download.
CEF_FILE_SHA256 = {
    "windows32": "2d3b10a1004283807acb8550aec5c84991f996eead39590fe7a1fc606b3b5b3e",
    "windows64": "a8c892800b0f1836a377d69a5ca8053ce3a3401940bb1f2010e7a057a9a429b8",
    "windowsarm64": "8a242e0e8fc402ea6f6a0a67777268f90a78297df13cd177714bd9b4e3b68ad8",
    "macosx64": "04f5a0a98d5ed3ab14dfbd04b940b5bf2b8d437287d3dbcfe8d0732289940202",
    "macosarm64": "f471d262a77537b26256425e18d4f814373387a5a4e655789a98ae044584b780",
    "linux64": "e310428343510d582aa9a9f115e19cf7675782e8433ec43b71f788cd87f9dc3b",
    "linuxarm64": "394d8d52286d953b6084b7285dffbe59b7a0d81e2f2aa7fb835c4b1a1373d24f",
    "linuxarm": "c8f60a50d3703d17beecb7ff18e24ac35a22ceb8886c9288ee18a77c1d3d098c",
}
