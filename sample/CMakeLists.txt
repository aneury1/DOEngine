cmake_minimum_required(VERSION 3.22.1)

project(DOSAMPLE)

include_directories(DOSAMPLE PRIVATE ../includes)
include_directories(MUSIC_SAMPLE PRIVATE ../includes)

add_executable(DoSample
    main.cpp
)

add_executable(Music
    Music.cpp
)

add_executable(Sound
    Sound.cpp
)

# add_subdirectory(SpriteSelectorRect SpriteSelectorRect/build)
add_subdirectory(Collector Collector/build)
add_subdirectory(Sprites Sprites/build)
add_subdirectory(SnakeGame SnakeGame/build)
add_subdirectory(Particles Particles/build)
add_subdirectory(VideoPlayer VideoPlayer/build)

file(COPY ${ASSETS_DIR}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


target_link_libraries(DoSample PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)

target_link_libraries(Music PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer    
)

target_link_libraries(Sound PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer    
)
