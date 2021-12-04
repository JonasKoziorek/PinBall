# Vložení složky Chipmunk
add_subdirectory(Chipmunk)

add_executable(pinball main.c Ball.c Frame.c BallArr.c Map.c Flipper.c Box.c Game.c Curve.c Slingshot.c)


target_include_directories(pinball PRIVATE Chipmunk/include/chipmunk)
target_link_libraries(pinball chipmunk ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m)
