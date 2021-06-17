################################################################################
# simplejson-c                                                                 #
# Copyright (C) 2021  Hendrik Boeck <hendrikboeck.dev@protonmail.com>          #
#                                                                              #
# This program is free software: you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation, either version 3 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.        #
################################################################################

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(simplejson VERSION 1.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED 99)

# LIBRARY TARGET
# 
include_directories(${PROJECT_SOURCE_DIR}/src/headerFiles)
file(GLOB ALL_SRCS "${PROJECT_SOURCE_DIR}/src/sourceFiles/*.c")
add_library(simplejson STATIC ${ALL_SRCS})

# TESTS
# 
add_subdirectory(tests)
