# FindGLM - attempts to locate the glm matrix/vector library.
#
# Origin: https://github.com/JoeyDeVries/LearnOpenGL/blob/master/cmake/modules/FindGLM.cmake
#
# This module defines the following variables (on success):
# GLM_INCLUDE_DIRS - where to find glm/glm.hpp
# GLM_FOUND - if the library was successfully located
#
# It is trying a few standard installation locations, but can be customized
# with the following variables:
# GLM_ROOT_DIR - root directory of a glm installation
#
# Headers are expected to be found in either:
# <GLM_ROOT_DIR>/glm/glm.hpp
# <GLM_ROOT_DIR>/include/glm/glm.hpp
#
# This variable can either be a cmake or environment variable.
# Note however that changing the value of the environment
# variable will NOT result in re-running the header search
# and therefore NOT adjust the variables set by this module.

set(_glm_HEADER_SEARCH_DIRS
    /usr/include
    /usr/local/include
    ${CMAKE_SOURCE_DIR}/includes
    "C:/Program Files (x86)/glm")

# Check environment variable
set(_glm_ENV_ROOT_DIR $ENV{GLM_ROOT_DIR})

if (NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)
    set(GLM_ROOT_DIR "${_glm_ENV_ROOT_DIR}")
endif ()

# Put user-specified location at beginning of search
if (GLM_ROOT_DIR)
    set(_glm_HEADER_SEARCH_DIRS
        ${GLM_ROOT_DIR}
        ${GLM_ROOT_DIR}/include
        ${_glm_HEADER_SEARCH_DIRS})
endif ()

# Locate header
find_path(GLM_INCLUDE_DIRS
    NAMES glm/glm.hpp
    PATHS ${_glm_HEADER_SEARCH_DIRS})

# Everything after DEFAULT_MSG is treated as required variable.
# This will automatically set GLM_FOUND as TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    GLM
    DEFAULT_MSG GLM_INCLUDE_DIRS)  # output message in console




