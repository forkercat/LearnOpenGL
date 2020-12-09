# FindFREETYPE - try to find FreeType
#
# Once done, this will define:
#
# FREETYPE_FOUND - system has FreeType
# FREETYPE_INCLUDE_DIRS - the FreeType include directories
# FREETYPE_LIBRARY - link these to use FreeType

find_path(FREETYPE_INCLUDE_DIRS
    NAMES ft2build.h
    PATHS /usr/include /usr/local/include /opt/local/include ${CMAKE_SOURCE_DIR}/includes)

find_library(FREETYPE_LIBRARY
    NAMES freetype
    PATHS /usr/lib64 /usr/lib /usr/local/lib /opt/local/lib ${CMAKE_SOURCE_DIR}/lib)

if (FREETYPE_INCLUDE_DIRS AND FREETYPE_LIBRARY)
    set(FREETYPE_FOUND TRUE)
endif ()

# You can also use find_package_handle_standard_args
if (FREETYPE_FOUND)
    if (NOT FREETYPE_FIND_QUIETLY)
        #        message(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
    endif ()
ELSE ()
    if (FREETYPE_FIND_REQUIRED)
        message(STATUS "-> ${FREETYPE_INCLUDE_DIRS}")
        message(STATUS "-> ${FREETYPE_LIBRARY}")
        message(FATAL_ERROR "Could not find lib FreeType")
    endif ()
endif ()


