cmake_minimum_required(VERSION 3.22.1)

project(DOSAMPLE)


include_directories(DOSAMPLE PRIVATE ../includes)

add_executable(DOSAMPLE
    main.cpp
)



# target_link_options(DOSAMPLE PRIVATE
#     "LINKER:-static" -static-libgcc -static-libstdc++)


target_link_libraries(DOSAMPLE PRIVATE
    DOENGINE
    SDL2
    SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)