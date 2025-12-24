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

add_executable(Particles
    Particles/Particles.cpp
)
add_executable(VideoPlayer
    VideoPlayer/VideoPlayer.cpp
)

add_executable(AnnetteWorld
    AnnetteWorld/AnnetteWorld.cpp
)




file(COPY ${ASSETS_DIR}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


target_link_libraries(DoSample PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

target_link_libraries(Music PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

target_link_libraries(Sound PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

target_link_libraries(Particles PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

target_link_libraries(AnnetteWorld PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

# sudo apt install libsdl2-dev libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
target_link_libraries(VideoPlayer PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf 
    SDL2_image
    SDL2_mixer
    avformat 
    avcodec 
    avutil 
    swscale
    )