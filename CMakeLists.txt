# Created by Gabriel Barbosa
# This CMakesLists.txt was created to make it easy to compile and cross compile
# any project using SDL2 its sub-packages (image, mixer, net and ttf).
#
# To add or remove any sub-package, you'll need to comment/uncomment
# the lines find_package(<package> REQUIRED), if (<package>_NOT_FOUND) ... endif (),
# ${<package>_INCLUDE_DIR} and ${<package>_LIBRARY}

cmake_minimum_required (VERSION 3.0)

# If SDL2 libraries couldn't be found, setting this var may solve it.
SET(SDL2_INSTALL_SEARCH_PATH "" CACHE PATH "Path to where SDL's bin, lib and include folders are")

# Getting project folder to set as the project name and executable name
get_filename_component (CURR_DIR "${CMAKE_CURRENT_SOURCE_DIR}" NAME)

# Setting and configuring build types
set (CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Build types possible" FORCE)
set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type")
if (DEFINED CMAKE_BUILD_TYPE)
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message ("## Configuring DEBUG version")
    set (Project_isDebug 1)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set (Project_isDebug 0)
    message ("## Configuring RELEASE version")
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set (Project_isDebug 0)
    message ("## Configuring RELEASE WITH DEBUG INFO version")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

set (CMAKE_CXX_FLAGS_DEBUG "-pg -ggdb")

# Setting project name and version
project (${CURR_DIR} VERSION 1.0.0.0)

# Passing some variables to the code
configure_file (
    "${CMAKE_SOURCE_DIR}/include/CMakeVars.hpp.in"
    "${CMAKE_SOURCE_DIR}/include/CMakeVars.hpp"
)

# Some paths where the SDL2 may be installed in windows
if (WIN32)
    set (SDL2_PATH ${SDL2_INSTALL_SEARCH__PATH} "C:/tools/msys64/mingw64/x86_64-w64-mingw32" "C:/tools/msys64/mingw64" "C:/tools/SDL2" "C:/SDL2")
endif()

# Path where the Find<package>.cmake for SDL2
# this is required so find_package() knows what to do
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package (SDL2 REQUIRED)
find_package (SDL2_image REQUIRED)
find_package (SDL2_ttf REQUIRED)
# find_package (SDL2_net REQUIRED)
find_package (SDL2_mixer REQUIRED)

if (SDL2_NOT_FOUND) 
    message("SDL2 is required but was not found!")
endif ()
if (SDL2_image_NOT_FOUND)
    message("SDL2_image is required but was not found!")
endif()
if (SDL2_ttf_NOT_FOUND)
    message("SDL2_ttf is required but was not found!")
endif()
# if (SDL2_net_NOT_FOUND)
#     message("SDL2_net is required but was not found!")
# endif()
if (SDL2_mixer_NOT_FOUND)
    message("SDL2_mixer is required but was not found!")
endif()

# Setting all include directories
include_directories (
    "./include"
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    # ${SDL2_NET_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
)

# Getting all source files
file (GLOB SOURCES "src/*.cpp")

# Adding all necessary flags
list (APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 ${CMAKE_CXX_FLAGS}")

# Creating executable and linker settings
add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    # ${SDL2_NET_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
)

# Install is not used, hiding from the GUI
mark_as_advanced (CMAKE_INSTALL_PREFIX)
