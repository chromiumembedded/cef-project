# Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

#
# Shared resources. These are included by the individual executable targets so
# the paths must be relative to those directories.
#

if(OS_MAC)
  # Shared macOS resources (menus, icons, etc).
  set(SHARED_RESOURCES_SRCS
    ../shared/resources/mac/English.lproj/InfoPlist.strings
    ../shared/resources/mac/English.lproj/MainMenu.xib
    ../shared/resources/mac/Info.plist
    ../shared/resources/mac/shared.icns
    )

  # Info.plist files used for main and helper app bundles.
  set(SHARED_INFO_PLIST ../shared/resources/mac/Info.plist)
  set(SHARED_HELPER_INFO_PLIST ../shared/resources/mac/helper-Info.plist)
elseif(OS_WINDOWS)
  # Shared Windows resources (version information, icons).
  set(SHARED_RESOURCES_SRCS
    ../shared/resources/win/big.ico
    ../shared/resources/win/resource.h
    ../shared/resources/win/shared.rc
    ../shared/resources/win/small.ico
    )

  # Manifest files used for executables.
  set(SHARED_EXE_MANIFEST ../shared/resources/win/shared.exe.manifest)
  set(SHARED_COMPATIBILITY_MANIFEST ../shared/resources/win/compatibility.manifest)
endif()


#
# Shared configuration.
#

# Support nice project/target organization in Visual Studio and Xcode.
if(OS_MACOSX OR OS_WINDOWS)
  # Enable the creation of project folders.
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Group target contents by directory.
  macro(SET_EXAMPLE_SOURCE_GROUPS srcs)
    foreach(FILE ${srcs}) 
      # Get the absolute directory path.
      get_filename_component(ABS_FILE "${FILE}" ABSOLUTE)
      get_filename_component(PARENT_DIR "${ABS_FILE}" DIRECTORY)

      # Remove the common directory prefix. What remains in the group.
      string(REPLACE "${CMAKE_SOURCE_DIR}/examples/" "" GROUP "${PARENT_DIR}")

      # Convert to Windows slashes.
      string(REPLACE "/" "\\" GROUP "${GROUP}")

      source_group("${GROUP}" FILES "${FILE}")
    endforeach()
  endmacro()
endif()

# Set the configuration-specific binary output directory.
if(GEN_NINJA OR GEN_MAKEFILES)
  # Force Ninja and Make to create a subdirectory named after the configuration.
  set(EXAMPLE_TARGET_OUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
else()
  set(EXAMPLE_TARGET_OUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
endif()

# Set properties common to all example targets.
macro(SET_EXAMPLE_PROPERTIES target)
  # Output all binaries to the configuration-specific build directory.
  set_target_properties(${target} PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY "${EXAMPLE_TARGET_OUT_DIR}"
                        RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE_TARGET_OUT_DIR}"
                        LIBRARY_OUTPUT_DIRECTORY "${EXAMPLE_TARGET_OUT_DIR}")

  if(OS_MACOSX OR OS_WINDOWS)
    # Place the target in the "examples" folder in Visual Studio and Xcode.
    set_property(TARGET ${target} PROPERTY FOLDER "examples")
  endif()
endmacro()

# Set properties on an example library target.
macro(SET_EXAMPLE_LIBRARY_TARGET_PROPERTIES target)
  SET_LIBRARY_TARGET_PROPERTIES(${target})
  SET_EXAMPLE_PROPERTIES(${target})
endmacro()

# Set properties on an example executable target.
macro(SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES target)
  SET_EXECUTABLE_TARGET_PROPERTIES(${target})
  SET_EXAMPLE_PROPERTIES(${target})

  if(OS_LINUX)
    # Set rpath so that libraries can be placed next to the executable.
    set_target_properties(${target} PROPERTIES INSTALL_RPATH "$ORIGIN")
    set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
  elseif(OS_WINDOWS)
    # Add the custom Windows manifest files to the executable.
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND "mt.exe" -nologo
              -manifest \"${CMAKE_CURRENT_SOURCE_DIR}/${SHARED_EXE_MANIFEST}\"
                        \"${CMAKE_CURRENT_SOURCE_DIR}/${SHARED_COMPATIBILITY_MANIFEST}\"
              -outputresource:"${EXAMPLE_TARGET_OUT_DIR}/${target}.exe"\;\#1
      COMMENT "Adding manifest..."
      )
  endif()
endmacro()


#
# Target configuration.
#

# Static library shared by all example executable targets.
add_subdirectory(shared)

# Example executable targets.
add_subdirectory(message_router)
add_subdirectory(minimal)
add_subdirectory(resource_manager)
add_subdirectory(scheme_handler)
