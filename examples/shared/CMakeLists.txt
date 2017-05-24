# Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

#
# Source files.
#

# Sources shared by all executables.
set(SHARED_COMMON_SRCS
  app_factory.h
  main_util.cc
  main_util.h
  )

# Main executable sources.
set(SHARED_SRCS
  ${SHARED_COMMON_SRCS}
  client_manager.cc
  client_manager.h
  client_util.cc
  client_util.h
  browser_util.cc
  browser_util.h
  main.h
  resource_util.cc
  resource_util.h
  )
set(SHARED_SRCS_LINUX
  client_util_linux.cc
  main_linux.cc
  resource_util_linux.cc
  resource_util_posix.cc
  )
set(SHARED_SRCS_MACOSX
  client_util_mac.mm
  main_mac.mm
  resource_util_mac.mm
  resource_util_posix.cc
  )
set(SHARED_SRCS_WINDOWS
  client_util_win.cc
  main_win.cc
  resource_util_win.cc
  )
APPEND_PLATFORM_SOURCES(SHARED_SRCS)

if(OS_MACOSX)
  # On macOS a separate helper executable is used for subprocesses.
  set(SHARED_HELPER_SRCS
    ${SHARED_COMMON_SRCS}
    process_helper_mac.cc
    process_helper_mac.h
    )
endif()


#
# Shared configuration.
#

# Target static library names.
set(SHARED_TARGET "shared")
if(OS_MACOSX)
  set(SHARED_HELPER_TARGET "shared_helper")
endif()

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")


#
# Linux configuration.
#

if(OS_LINUX)
  # Static library target.
  add_library(${SHARED_TARGET} STATIC ${SHARED_SRCS})
  SET_EXAMPLE_LIBRARY_TARGET_PROPERTIES(${SHARED_TARGET})
  add_dependencies(${SHARED_TARGET} libcef_dll_wrapper)
  target_link_libraries(${SHARED_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

  # Copy binary and resource files to the target output directory.
  COPY_FILES("${SHARED_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${EXAMPLE_TARGET_OUT_DIR}")
  COPY_FILES("${SHARED_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${EXAMPLE_TARGET_OUT_DIR}")

  # Output a message about setting SUID permissions on the chrome-sandbox target.
  SET_LINUX_SUID_PERMISSIONS("${SHARED_TARGET}" "${EXAMPLE_TARGET_OUT_DIR}/chrome-sandbox")
endif()


#
# Mac OS X configuration.
#

if(OS_MACOSX)
  # Create source groups for Xcode.
  SET_EXAMPLE_SOURCE_GROUPS("${SHARED_SRCS}")
  SET_EXAMPLE_SOURCE_GROUPS("${SHARED_HELPER_SRCS}")

  # Helper static library target.
  add_library(${SHARED_HELPER_TARGET} STATIC ${SHARED_HELPER_SRCS})
  SET_EXAMPLE_LIBRARY_TARGET_PROPERTIES(${SHARED_HELPER_TARGET})
  add_dependencies(${SHARED_HELPER_TARGET} libcef_dll_wrapper)
  target_link_libraries(${SHARED_HELPER_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

  # Main static library target.
  add_library(${SHARED_TARGET} STATIC ${SHARED_SRCS})
  SET_EXAMPLE_LIBRARY_TARGET_PROPERTIES(${SHARED_TARGET})
  add_dependencies(${SHARED_TARGET} libcef_dll_wrapper "${SHARED_HELPER_TARGET}")
  target_link_libraries(${SHARED_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})
endif()


#
# Windows configuration.
#

if(OS_WINDOWS)
  # Create source groups for Visual Studio.
  SET_EXAMPLE_SOURCE_GROUPS("${SHARED_SRCS}")

  # Executable target.
  add_library(${SHARED_TARGET} STATIC ${SHARED_SRCS})
  SET_EXAMPLE_LIBRARY_TARGET_PROPERTIES(${SHARED_TARGET})
  add_dependencies(${SHARED_TARGET} libcef_dll_wrapper)
  target_link_libraries(${SHARED_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

  if(USE_SANDBOX)
    # Logical target used to link the cef_sandbox library.
    ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")
    target_link_libraries(${SHARED_TARGET} cef_sandbox_lib ${CEF_SANDBOX_STANDARD_LIBS})
  endif()

  # Copy binary and resource files to the target output directory.
  COPY_FILES("${SHARED_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${EXAMPLE_TARGET_OUT_DIR}")
  COPY_FILES("${SHARED_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${EXAMPLE_TARGET_OUT_DIR}")
endif()
