cmake_minimum_required(VERSION 3.4)

project(pinball)

# Parametr -pthread je nutný při použítí této knihovny
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

# Vložení složky Chipmunk
add_subdirectory(Chipmunk)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)


# Vytvoření pinballu
add_executable(pinball main.c Ball.c Frame.c Random.c BallArr.c Map.c Flipper.c Box.c Game.c Curve.c Slingshot.c)

# Přidání knihovny k našemu pinballu
#target_include_directories(chipmunk PRIVATE Chipmunk/include/chipmunk)
target_include_directories(pinball PRIVATE Chipmunk/include/chipmunk)
target_link_libraries(pinball chipmunk ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m)
