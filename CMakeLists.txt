cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(simplejson VERSION 1.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED 99)

# LIBRARY TARGET
# 
include_directories(${PROJECT_SOURCE_DIR}/src/headerFiles)
file(GLOB all_SRCs "${PROJECT_SOURCE_DIR}/src/sourceFiles/*.c")
add_library(simplejson STATIC ${all_SRCs})

# TESTS
# 
add_subdirectory(tests)
