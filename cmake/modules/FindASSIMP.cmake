# FindASSIMP - try to find Assimp
#
# Origin: https://github.com/JoeyDeVries/LearnOpenGL/blob/master/cmake/modules/FindASSIMP.cmake
#
# Once done, this will define:
#
# ASSIMP_FOUND - system has Assimp
# ASSIMP_INCLUDE_DIRS - the Assimp include directories
# ASSIMP_LIBRARY - link these to use Assimp

find_path(ASSIMP_INCLUDE_DIRS
    NAMES assimp/mesh.h
    PATHS /usr/include /usr/local/include /opt/local/include ${CMAKE_SOURCE_DIR}/includes)

find_library(ASSIMP_LIBRARY
    NAMES assimp
    PATHS /usr/lib64 /usr/lib /usr/local/lib /opt/local/lib ${CMAKE_SOURCE_DIR}/lib)

if (ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARY)
    set(ASSIMP_FOUND TRUE)
endif ()

# You can use find_package_handle_standard_args
if (ASSIMP_FOUND)
    if (NOT ASSIMP_FIND_QUIETLY)
        #        message(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
    endif ()
ELSE ()
    if (ASSIMP_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find lib Assimp")
    endif ()
endif ()


