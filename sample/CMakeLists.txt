cmake_minimum_required(VERSION 3.22.1)

project(DOSAMPLE)

include_directories(DOSAMPLE PRIVATE ../includes)
include_directories(MUSIC_SAMPLE PRIVATE ../includes)

set(ASSETS_DIR_OUTPUT_DIR "")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Linux")
	set(ASSETS_DIR_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Windows")
	set(ASSETS_DIR_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif ()

file(COPY ${ASSETS_DIR}
     DESTINATION "${ASSETS_DIR_OUTPUT_DIR}")

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

target_link_libraries(DoSample PRIVATE
    DOENGINE
	${DOENGINE_LIBRARIES}
)

target_link_libraries(Music PRIVATE
    DOENGINE
	${DOENGINE_LIBRARIES}
)

target_link_libraries(Sound PRIVATE
    DOENGINE
	${DOENGINE_LIBRARIES}
)

target_link_libraries(Particles PRIVATE
    DOENGINE
	${DOENGINE_LIBRARIES}
)

if(NOT FETCH_SDL_FROM_GIT)
	add_executable(VideoPlayer
		VideoPlayer/VideoPlayer.cpp
	)
	# sudo apt install libsdl2-dev libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
	target_link_libraries(VideoPlayer PRIVATE
		DOENGINE
		${DOENGINE_LIBRARIES}
		avformat 
		avcodec 
		avutil 
		swscale
	)
endif()

#add_executable(${PROJECT_NAME}-sample
#   sample/ignored_main.cpp 
#)
add_executable(SimplePong
   pong/SimplePong.cpp 
)

add_executable(SpaceInvader
   SpaceInvader/SpaceInvader.cpp
)

add_executable(Tetris
   tetris/Tetris.cpp
)

add_executable(MusicPlayer
   MusicPlayer/MusicPlayer.cpp
)
add_executable(BattleSpawn
   BattleSpawn/BattleSpawn.cpp
)
add_executable(PacmanClone
   Pacman/Pacman.cpp
)

add_executable(BattleCityRecreation
   BattleCityRecreation/BattleCityRecreation.cpp
)

# to build sample needs 
# Zip support, ubuntu sudo apt-get install libzip-dev
#target_link_libraries(${PROJECT_NAME}-sample PRIVATE
#    ${PROJECT_NAME}
#    ${DOENGINE_LIBRARIES}
#)

target_link_libraries(SimplePong PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(SpaceInvader PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(Tetris PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(MusicPlayer PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(BattleSpawn PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(PacmanClone PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(BattleCityRecreation PRIVATE
    DOENGINE
    ${DOENGINE_LIBRARIES}
)