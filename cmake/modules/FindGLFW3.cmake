# FindGLFW3 - locate the glfw3 library
#
# Origin: https://github.com/JoeyDeVries/LearnOpenGL/blob/master/cmake/modules/FindGLFW3.cmake
#
# This module defines the following variables:
#
# GLFW3_FOUND - true if both the above variables are found.
# GLFW3_LIBRARY - the name of the library
# GLFW3_INCLUDE_DIRS - where to find glfw include files
#
# To help locate the library and include files, you can define a
# variable called GLFW3_ROOT which points to the root of glfw
# library installation.

set(_glfw3_HEADER_SEARCH_DIRS
    /usr/include
    /usr/local/include
    ${CMAKE_SOURCE_DIR}/includes
    "C:/Program Files (x86)/glfw/include")
set(_glfw3_LIBRARY_SEARCH_DIRS
    /usr/lib
    /usr/local/lib
    ${CMAKE_SOURCE_DIR}/lib
    "C:/Program Files (x86)/glfw/lib-msvc110")

# Check environment variable for root search directory
set(_glfw3_ENV_ROOT $ENV{GLFW3_ROOT})
if (NOT GLFW3_ROOT AND _glfw3_ENV_ROOT)
    set(GLFW3_ROOT ${_glfw3_ENV_ROOT})
endif ()

# Put user specified location at beginning of search
if (GLFW3_ROOT)
    LIST(INSERT _glfw3_HEADER_SEARCH_DIRS 0 "${GLFW3_ROOT}/include")
    LIST(INSERT _glfw3_LIBRARY_SEARCH_DIRS 0 "${GLFW3_ROOT}/lib")
endif ()

# Search for the header
find_path(GLFW3_INCLUDE_DIRS
    NAMES GLFW/glfw3.h
    PATH ${_glfw3_HEADER_SEARCH_DIRS})

# Search for the library
find_library(GLFW3_LIBRARY
    NAMES glfw3 glfw
    PATH ${_glfw3_LIBRARY_SEARCH_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW3
    DEFAULT_MSG GLFW3_LIBRARY GLFW3_INCLUDE_DIRS)