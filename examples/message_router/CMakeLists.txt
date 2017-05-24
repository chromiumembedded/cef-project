# Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

#
# Source files.
#

# Main executable sources.
set(EXAMPLE_SRCS
  ../minimal/main_minimal.cc
  app_browser_impl.cc
  client_impl.cc
  client_impl.h
  )
set(EXAMPLE_SRCS_WINDOWS
  resource_util_win_impl.cc
  )
APPEND_PLATFORM_SOURCES(EXAMPLE_SRCS)

if(OS_LINUX OR OS_WINDOWS)
  # On Windows and Linux the same executable is used for all processes.
  set(EXAMPLE_SRCS
    ${EXAMPLE_SRCS}
    ../minimal/app_other_minimal.cc
    app_renderer_impl.cc
    )
elseif(OS_MACOSX)
  # On macOS a separate helper executable is used for subprocesses.
  set(EXAMPLE_HELPER_SRCS
    ../minimal/app_other_minimal.cc
    ../minimal/process_helper_mac_minimal.cc
    app_renderer_impl.cc
    )
endif()

# Main executable resources.
set(EXAMPLE_RESOURCES_SRCS
  resources/message_router.html
  )
set(EXAMPLE_RESOURCES_SRCS_WINDOWS
  # Resources that embed "message_router.html" in the executable.
  resources/win/resource.h
  resources/win/resource.rc
  )
APPEND_PLATFORM_SOURCES(EXAMPLE_RESOURCES_SRCS)

if(OS_MACOSX OR OS_WINDOWS)
  # On macOS and Windows include the message_router and shared resources.
  set(EXAMPLE_RESOURCES_SRCS
    ${EXAMPLE_RESOURCES_SRCS}
    ${SHARED_RESOURCES_SRCS}
    )
endif()


#
# Shared configuration.
#

# Target executable names.
set(EXAMPLE_TARGET "message_router")
if(OS_MACOSX)
  set(EXAMPLE_HELPER_TARGET "message_router Helper")
endif()


#
# Linux configuration.
#

if(OS_LINUX)
  # Executable target.
  add_executable(${EXAMPLE_TARGET} ${EXAMPLE_SRCS})
  SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES(${EXAMPLE_TARGET})
  add_dependencies(${EXAMPLE_TARGET} shared)
  target_link_libraries(${EXAMPLE_TARGET} shared)

  # Copy resource files to the target output directory.
  COPY_FILES("${EXAMPLE_TARGET}" "${EXAMPLE_RESOURCES_SRCS}" "${CMAKE_CURRENT_SOURCE_DIR}" "${EXAMPLE_TARGET_OUT_DIR}/${EXAMPLE_TARGET}_files")
endif()


#
# Mac OS X configuration.
#

if(OS_MACOSX)
  # Create source groups for Xcode.
  SET_EXAMPLE_SOURCE_GROUPS("${EXAMPLE_SRCS}")
  SET_EXAMPLE_SOURCE_GROUPS("${EXAMPLE_HELPER_SRCS}")

  # Output paths for the app bundles.
  set(EXAMPLE_APP "${EXAMPLE_TARGET_OUT_DIR}/${EXAMPLE_TARGET}.app")
  set(EXAMPLE_HELPER_APP "${EXAMPLE_TARGET_OUT_DIR}/${EXAMPLE_HELPER_TARGET}.app")

  # Variable referenced from Info.plist files.
  set(PRODUCT_NAME "${EXAMPLE_TARGET}")

  # Helper executable target.
  add_executable(${EXAMPLE_HELPER_TARGET} MACOSX_BUNDLE ${EXAMPLE_HELPER_SRCS})
  SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES(${EXAMPLE_HELPER_TARGET})
  add_dependencies(${EXAMPLE_HELPER_TARGET} shared_helper)
  target_link_libraries(${EXAMPLE_HELPER_TARGET} shared_helper)
  set_target_properties(${EXAMPLE_HELPER_TARGET} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/${SHARED_HELPER_INFO_PLIST}"
    )

  # Fix the framework rpath in the helper executable.
  FIX_MACOSX_HELPER_FRAMEWORK_RPATH(${EXAMPLE_HELPER_TARGET})

  # Main executable target.
  add_executable(${EXAMPLE_TARGET} MACOSX_BUNDLE ${EXAMPLE_SRCS} ${EXAMPLE_RESOURCES_SRCS})
  SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES(${EXAMPLE_TARGET})
  add_dependencies(${EXAMPLE_TARGET} shared "${EXAMPLE_HELPER_TARGET}")
  target_link_libraries(${EXAMPLE_TARGET} shared)
  set_target_properties(${EXAMPLE_TARGET} PROPERTIES
    RESOURCE "${EXAMPLE_RESOURCES_SRCS}"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/${SHARED_INFO_PLIST}"
    )

  # Copy files into the main app bundle.
  add_custom_command(
    TARGET ${EXAMPLE_TARGET}
    POST_BUILD
    # Copy the helper app bundle into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${EXAMPLE_HELPER_APP}"
            "${EXAMPLE_APP}/Contents/Frameworks/${EXAMPLE_HELPER_TARGET}.app"
    # Copy the CEF framework into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CEF_BINARY_DIR}/Chromium Embedded Framework.framework"
            "${EXAMPLE_APP}/Contents/Frameworks/Chromium Embedded Framework.framework"
    VERBATIM
    )

  # Fix the framework rpath in the main executable.
  FIX_MACOSX_MAIN_FRAMEWORK_RPATH(${EXAMPLE_TARGET})

  if(NOT ${CMAKE_GENERATOR} STREQUAL "Xcode")
    # Manually process and copy over resource files.
    # The Xcode generator handles this via the set_target_properties RESOURCE directive.
    # Remove these prefixes from input file paths.
    set(PREFIXES
      "../shared/resources/mac/"
      "resources/"
      )
    COPY_MACOSX_RESOURCES("${EXAMPLE_RESOURCES_SRCS}" "${PREFIXES}" "${EXAMPLE_TARGET}" "${CMAKE_CURRENT_SOURCE_DIR}" "${EXAMPLE_APP}")
  endif()
endif()


#
# Windows configuration.
#

if(OS_WINDOWS)
    # Add resources to the sources variable for convenience.
  set(EXAMPLE_SRCS
    ${EXAMPLE_SRCS}
    ${EXAMPLE_RESOURCES_SRCS}
    )

  # Create source groups for Visual Studio.
  SET_EXAMPLE_SOURCE_GROUPS("${EXAMPLE_SRCS}")

  # Executable target.
  add_executable(${EXAMPLE_TARGET} WIN32 ${EXAMPLE_SRCS})
  SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES(${EXAMPLE_TARGET})
  add_dependencies(${EXAMPLE_TARGET} shared)
  target_link_libraries(${EXAMPLE_TARGET} shared)
endif()
