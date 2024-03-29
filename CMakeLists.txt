cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Configuration
configure_file(
    configuration/root_directory.h.in
    configuration/root_directory.h  # this file will be generated
)

# Macro
#######
macro(makeLink src dest target)
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}
        DEPENDS ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

# Find the required packages
############################
find_package(GLM REQUIRED)
message(STATUS "Found GLM in: ${GLM_INCLUDE_DIRS}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in: ${GLFW3_INCLUDE_DIRS}")

find_package(ASSIMP REQUIRED)
message(STATUS "Found Assimp in: ${ASSIMP_INCLUDE_DIRS}")

find_package(IRRKLANG REQUIRED)
message(STATUS "Found IrrKlang in: ${IRRKLANG_INCLUDE_DIRS}")
message(STATUS "Found IrrKlang Lib in: ${IRRKLANG_LIBRARY}")

find_package(FREETYPE REQUIRED)
message(STATUS "Found FreeType in: ${FREETYPE_INCLUDE_DIRS}")
message(STATUS "Found FreeType Lib in: ${FREETYPE_LIBRARY}")


# Static Libraries
##################
# Creates relevant static libraries (PUBLIC - no need to include the headers in other targets)
add_library(stb_image STATIC src/stb_image.cpp)
add_library(glad STATIC src/glad.c)
add_library(filesystem STATIC src/filesystem.cpp)

target_include_directories(stb_image
    PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_include_directories(glad
    PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_include_directories(filesystem
    PRIVATE ${CMAKE_SOURCE_DIR}/includes ${CMAKE_BINARY_DIR}/configuration)

# Set include directories
#########################
set(INCLUDE_DIRS
    ${INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ${IRRKLANG_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/configuration
    ${CMAKE_SOURCE_DIR}/includes)


# Set libraries
###############
set(LIBS
    ${LIBS}
    ${GLFW3_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${IRRKLANG_LIBRARY}
    ${FREETYPE_LIBRARY}
    stb_image # target name
    glad
    filesystem)

if (APPLE)
    include_directories(/System/Library/Frameworks)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKit_LIBRARY IOKit)
    find_library(CoreVideo_LIBRARY CoreVideo)
    mark_as_advanced(COCOA_LIBRARY OpenGL_LIBRARY)
    set(APPLE_LIBS
        ${COCOA_LIBRARY}
        ${OpenGL_LIBRARY}
        ${IOKit_LIBRARY}
        ${CoreVideo_LIBRARY})
    set(LIBS ${LIBS} ${APPLE_LIBS})
    # https://github.com/JoeyDeVries/LearnOpenGL/blob/master/CMakeLists.txt
endif ()


# Targets
#########

# Test target
add_executable(Test src/test.cpp)
target_include_directories(Test PRIVATE ${INCLUDE_DIRS})
target_link_libraries(Test PRIVATE ${LIBS})

set(
    CHAPTERS
    1_getting_started
    2_lighting
    3_model_loading
    4_advanced_opengl
    5_advanced_lighting
    6_practice
)

set(
    1_getting_started
    1_1_hello_window
    2_1_hello_triangle
    2_2_hello_triangle_indexed
    3_1_shaders_uniform
    3_2_shaders_interpolation
    3_3_shaders_class
    4_1_textures
    4_2_textures_combined
    5_1_transformations
    6_1_coordinate_systems
    6_2_coordinate_systems_depth
    6_3_coordinate_systems_multiple
    7_1_camera_keyboard_dt
    7_2_camera_mouse_zoom
    7_3_camera_class
)

set(
    2_lighting
    1_colors
    2_basic_lighting
    3_materials
    4_lighting_map
    5_1_light_casters_directional
    5_2_light_casters_point
    5_3_light_casters_spot
    5_4_light_casters_spot_soft
    6_multiple_lights
)

set(
    3_model_loading
    1_model_loading
    1_model_loading_original
)

set(
    4_advanced_opengl
    1_1_depth_testing
    2_stencil_testing
    3_1_blending_discard
    3_2_blending_sort
    5_1_framebuffers
    6_1_cubemaps_skybox
    9_1_geometry_shader
    10_1_instancing_quads
    10_1_instancing_quads_via_buffer
    10_2_asteroids
    10_2_asteroids_via_buffer
)

set(
    5_advanced_lighting
    1_advanced_lighting
    3_1_1_shadow_mapping_depth
    3_1_2_shadow_mapping_base
    4_normal_mapping
    5_1_parallax_mapping
    5_2_steep_parallax_mapping
    5_3_parallax_occlusion_mapping
    6_hdr
    7_bloom
    8_1_deferred_shading
    9_ssao
)

set(
    6_practice
    breakout
)

# Other targets
foreach (CHAPTER ${CHAPTERS})
    foreach (DEMO ${${CHAPTER}})
        file(
            GLOB SOURCE
            src/${CHAPTER}/${DEMO}/*.h
            src/${CHAPTER}/${DEMO}/*.cpp
            src/${CHAPTER}/${DEMO}/*.vs
            src/${CHAPTER}/${DEMO}/*.fs
            src/${CHAPTER}/${DEMO}/*.gs
            src/${CHAPTER}/${DEMO}/*.vert
            src/${CHAPTER}/${DEMO}/*.frag
            src/${CHAPTER}/${DEMO}/*.geom
        )
        set(TARGET_NAME ${CHAPTER}__${DEMO})
        add_executable(${TARGET_NAME} ${SOURCE})
        # header
        target_include_directories(${TARGET_NAME}
            PRIVATE ${INCLUDE_DIRS})
        # link
        target_link_libraries(${TARGET_NAME}
            PRIVATE ${LIBS})

        # copy shader files to build directory
        file(
            GLOB SHADERS
            src/${CHAPTER}/${DEMO}/*.vs
            src/${CHAPTER}/${DEMO}/*.fs
            src/${CHAPTER}/${DEMO}/*.gs
            src/${CHAPTER}/${DEMO}/*.vert
            src/${CHAPTER}/${DEMO}/*.frag
            src/${CHAPTER}/${DEMO}/*.geom
        )
        foreach (SHADER ${SHADERS})
            if (APPLE)
                # create symbolic link for those files
                get_filename_component(SHADER_NAME ${SHADER} NAME)
                makeLink(${SHADER}
                    ${CMAKE_SOURCE_DIR}/cmake-build-debug/${SHADER_NAME}
                    ${TARGET_NAME})
            endif ()
        endforeach ()

        # copy breakout shaders
        file(
            GLOB BREAKOUT_SHADERS
            src/${CHAPTER}/${DEMO}/shaders/*
        )
        file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/cmake-build-debug/shaders)
        foreach (SHADER ${BREAKOUT_SHADERS})
            if (APPLE)
                # create symbolic link for those files
                get_filename_component(SHADER_NAME ${SHADER} NAME)
                makeLink(${SHADER}
                    ${CMAKE_SOURCE_DIR}/cmake-build-debug/shaders/${SHADER_NAME}
                    ${TARGET_NAME})
            endif ()
        endforeach ()

        # copy IrrKlang plugin files
        file(
            GLOB PLUGIN_FILES
            dlls/*
        )
        foreach (PLUGIN_PATH ${PLUGIN_FILES})
            if (APPLE)
                # create symbolic link for those files
                get_filename_component(PLUGIN_FILE_NAME ${PLUGIN_PATH} NAME)
                makeLink(${PLUGIN_PATH}
                    ${CMAKE_SOURCE_DIR}/cmake-build-debug/${PLUGIN_FILE_NAME}
                    ${TARGET_NAME})
            endif ()
        endforeach ()

    endforeach ()
endforeach ()
