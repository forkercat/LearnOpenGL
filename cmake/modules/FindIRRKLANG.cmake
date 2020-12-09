# FindIRRKLANG - try to find irrKlang
#
# Once done, this will define:
#
# IRRKLANG_FOUND - system has irrKlang
# IRRKLANG_INCLUDE_DIRS - the irrKlang include directories
# IRRKLANG_LIBRARY - link these to use irrKlang

find_path(IRRKLANG_INCLUDE_DIRS
    NAMES irrKlang/irrKlang.h
    PATHS /usr/include /usr/local/include /opt/local/include ${CMAKE_SOURCE_DIR}/includes)

find_library(IRRKLANG_LIBRARY
    NAMES irrklang
    PATHS /usr/lib64 /usr/lib /usr/local/lib /opt/local/lib ${CMAKE_SOURCE_DIR}/lib)

if (IRRKLANG_INCLUDE_DIRS AND IRRKLANG_LIBRARY)
    set(IRRKLANG_FOUND TRUE)
endif ()

# You can also use find_package_handle_standard_args
if (IRRKLANG_FOUND)
    if (NOT IRRKLANG_FIND_QUIETLY)
        #        message(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
    endif ()
ELSE ()
    if (IRRKLANG_FIND_REQUIRED)
        message(STATUS "-> ${IRRKLANG_INCLUDE_DIRS}")
        message(STATUS "-> ${IRRKLANG_LIBRARY}")
        message(FATAL_ERROR "Could not find lib IrrKlang")
    endif ()
endif ()


