cmake_minimum_required(VERSION 3.22.1)

project(BattleCity)
set(CURRENT_SDL_VERSION SDL2)
set(CURRENT_SDL_MAIN_VERSION SDL2main)


include_directories(../../includes)

add_executable(${PROJECT_NAME}
    PlayStateMachine.cpp
    main.cpp
)

file(COPY ${ASSETS_DIR}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
   DOENGINE
   
   ${CURRENT_SDL_VERSION}
   ${CURRENT_SDL_MAIN_VERSION}
   SDL2_ttf
   SDL2_image
   SDL2_mixer
)


