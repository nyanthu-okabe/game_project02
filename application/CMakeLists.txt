cmake_minimum_required(VERSION 3.16)

project(game_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

add_subdirectory(../nyanchu_engine nyanchu_engine_build)

add_executable(game
    src/main.cpp
    src/application.cpp
    src/application.h
)

target_include_directories(game PRIVATE
    ../nyanchu_engine/engine/include
    src
)

target_link_libraries(game
    PRIVATE
        nyanthu_engine
)

add_dependencies(game compile_shaders)

if(APPLE)
    target_compile_definitions(game PRIVATE
      GLFW_INCLUDE_NONE
      GLFW_EXPOSE_NATIVE_COCOA
    )
endif()

# This assumes the shaders are copied to the build output directory of the game
# We might need to adjust the main CMakeLists.txt to handle this better
# For now, let's add a command to copy the shaders from the engine's build dir
add_custom_command(
    TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/nyanchu_engine/shaders
    $<TARGET_FILE_DIR:game>/shaders
)
