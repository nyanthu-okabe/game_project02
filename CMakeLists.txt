cmake_minimum_required(VERSION 3.16)
project(nyanthu_game)

add_compile_options(-Wno-error=incompatible-pointer-types)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=incompatible-pointer-types")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=incompatible-pointer-types")
set(CMAKE_OBJCXX_FLAGS "${CMAKE_OBJCXX_FLAGS} -Wno-error=incompatible-pointer-types")

add_subdirectory(nyanchu_engine)
add_subdirectory(application)
