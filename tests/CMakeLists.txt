cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(simplejson_test VERSION 1.0 LANGUAGES C)

# DOWNLOAD CMOCKA AND MAKE AVAILABLE
#
include(FetchContent)
FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

FetchContent_MakeAvailable(cmocka)

# BUILD TEST EXE
#
include_directories(.)
add_executable(simplejson_test run_cmocka_tests.c)
add_dependencies(simplejson_test cmocka)
target_compile_features(simplejson_test PRIVATE c_std_11)
target_link_libraries(simplejson_test PRIVATE cmocka-static simplejson)

# ADD TO TESTS
#
enable_testing()
add_test(NAME simplejson_test COMMAND simplejson_test)