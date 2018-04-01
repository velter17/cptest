cmake_minimum_required (VERSION 3.5)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build_tools)
include(InstallRules)
include(Libraries)

project (cptest)

add_subdirectory(src)
add_subdirectory(external_libs)
add_subdirectory(test)
