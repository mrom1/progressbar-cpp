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
## Find fmt
###########################################################################
find_package(fmt CONFIG REQUIRED)
find_package (Threads)


###########################################################################
## Build Example
###########################################################################
add_executable(example example.cpp)
target_link_libraries(example PRIVATE fmt::fmt Threads::Threads)
target_include_directories(example PRIVATE ${PROGRESSBAR_INCLUDES})
