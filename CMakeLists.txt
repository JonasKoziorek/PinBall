cmake_minimum_required(VERSION 3.4)

project(pinball)

# Parametr -pthread je nutný při použítí této knihovny
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

add_subdirectory(src)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
