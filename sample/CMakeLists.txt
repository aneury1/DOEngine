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

add_executable(SnakeGame
    SnakeGame/SnakeGame.cpp
)

add_executable(Collector
    Collector/main.cpp
)


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

target_link_libraries(Particles PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    )


target_link_libraries(SnakeGame PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    )
target_link_libraries(Collector PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    
    )
# sudo apt install libsdl2-dev libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
target_link_libraries(VideoPlayer PRIVATE
    doengine
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    avformat 
    avcodec 
    avutil 
    swscale
    )
