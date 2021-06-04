cmake_minimum_required(VERSION 3.6)
project(simplejson VERSION 1.1)

set(PROJECTNAME simplejson)
set(CMAKE_C_STANDARD 11)

include_directories(
  ${PROJECT_SOURCE_DIR}/src/headerFiles
)

file(GLOB all_SRCs
  "${PROJECT_SOURCE_DIR}/src/sourceFiles/*.c"
)

add_library(${PROJECTNAME} STATIC ${all_SRCs})
