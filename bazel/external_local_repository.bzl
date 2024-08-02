# Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

def _external_local_repository_impl(repository_ctx):
    # Create a symlink to the external directory in the current workspace.
    absolute_path = repository_ctx.path(Label(repository_ctx.attr.path)).dirname
    repository_ctx.symlink(absolute_path, "")

# Like `local_repository` but referencing a directory in an external repository.
# Based on https://groups.google.com/g/bazel-discuss/c/xpsg3mWQPZg/m/cUY-w7AMBgAJ
external_local_repository = repository_rule(
    implementation = _external_local_repository_impl,
    attrs = {
        "path": attr.string(mandatory = True),
    },
)
