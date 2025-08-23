
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

project(nyanthu_engine LANGUAGES CXX OBJCXX)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v3.2.5
)
FetchContent_MakeAvailable(flecs)


set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

add_subdirectory(external/bgfx.cmake)

# Engine Library
add_library(nyanthu_engine
    engine/src/engine.cpp
    engine/src/ecs_flecs.cpp
    engine/src/audio_miniaudio.cpp
    engine/src/physics_jolt.cpp
)

if (APPLE)
    target_sources(nyanthu_engine PRIVATE
        engine/src/platform/platform_utils_macos.mm
        engine/src/renderer_metal.mm
    )
    target_link_libraries(nyanthu_engine PUBLIC
        "-framework Cocoa"
        "-framework Metal"
        "-framework QuartzCore"
        "-framework MetalKit"
    )
elseif(UNIX AND NOT APPLE)
    target_sources(nyanthu_engine PRIVATE
        engine/src/platform/platform_utils_linux.cpp
        engine/src/renderer_opengl.cpp
    )
else()
    target_sources(nyanthu_engine PRIVATE
        engine/src/renderer_opengl.cpp
    )
endif()

target_include_directories(nyanthu_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake/bgfx/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake/bimg/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake/bx/include
    ${glm_SOURCE_DIR}
    ${flecs_SOURCE_DIR}
)

target_link_libraries(nyanthu_engine
    PRIVATE
        bgfx
        bimg
        bx
        glfw
        flecs
)

if(APPLE)
    target_link_libraries(nyanthu_engine PUBLIC
        "-framework Cocoa"
        "-framework Metal"
        "-framework QuartzCore"
    )
endif()

# Example Application (will be handled by application's CMakeLists.txt)
# add_executable(hello_world
#     examples/hello_world/main.cpp
# )
#
# target_link_libraries(hello_world
#     PRIVATE
#         nyanthu_engine
# )
#
# target_compile_definitions(hello_world PRIVATE GLFW_INCLUDE_NONE GLFW_EXPOSE_NATIVE_COCOA)


# Add a custom target to compile shaders
add_custom_target(compile_shaders ALL)

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_BUILD_DIR ${CMAKE_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADER_BUILD_DIR})

set(SHADER_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/external/bgfx.cmake/bgfx/tools/bin/darwin/shaderc)

file(GLOB SHADERS ${SHADER_DIR}/*.sc)

foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME_WE)
    set(SHADER_TYPE)
    if(SHADER_NAME MATCHES "^vs_")
        set(SHADER_TYPE "vertex")
    elseif(SHADER_NAME MATCHES "^fs_")
        set(SHADER_TYPE "fragment")
    endif()

    set(OUTPUT_SHADER ${SHADER_BUILD_DIR}/${SHADER_NAME}.bin)

    add_custom_command(
        TARGET compile_shaders
        COMMAND ${SHADER_COMPILER} -f ${SHADER} -o ${OUTPUT_SHADER} --type ${SHADER_TYPE} --platform osx -p metal
        DEPENDS ${SHADER}
        COMMENT "Compiling ${SHADER_NAME}"
    )
endforeach()

# add_dependencies(hello_world compile_shaders)

# Copy shaders to the build directory
# add_custom_command(
#     TARGET hello_world
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${SHADER_BUILD_DIR}
#     $<TARGET_FILE_DIR:hello_world>/shaders
# )

# Add a custom target to run the example
# add_custom_target(run_hello_world
#     COMMAND $<TARGET_FILE:hello_world>
#     DEPENDS hello_world
# )
