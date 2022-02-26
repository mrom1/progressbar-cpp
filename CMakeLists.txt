###########################################################################
## This file is part of the progressbar-cpp distribution 
## (https://github.com/mrom1/progressbar-cpp).
## Copyright (c) 2022 mrom1.
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, version 3.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program. If not, see <http://www.gnu.org/licenses/>.
###########################################################################



###########################################################################
## Project - progressbar-cpp 
###########################################################################
cmake_minimum_required(VERSION 3.16)
set(VCPKG_VERSION edge)
include(cmake/vcpkg.cmake)
project(progressbar-cpp VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)


###########################################################################
## Set local CMake Modules Path
###########################################################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


###########################################################################
## Build Options
###########################################################################
option(BUILD_UNITTESTS "Build unit tests" ON)
option(BUILD_EXAMPLE "Build unit tests" ON)


###########################################################################
## CMake variables
###########################################################################
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" 
  CACHE PATH "install in same directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/install")


###########################################################################
## Set Progressbar Header
###########################################################################
set(PROGRESSBAR_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/source/")


###########################################################################
## add subdirectories
###########################################################################
add_subdirectory(source)


###########################################################################
## Testcases
###########################################################################
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_UNITTESTS)
  enable_testing()
  add_subdirectory(tests)
endif()


###########################################################################
## Examples
###########################################################################
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_UNITTESTS)
  enable_testing()
  add_subdirectory(example)
endif()

