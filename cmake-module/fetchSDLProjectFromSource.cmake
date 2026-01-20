
include(FetchContent)

SET(SDL2IMAGE_INSTALL OFF)
SET(BUILD_SHARED_LIBS FALSE)
SET(SDL2_DISABLE_INSTALL OFF)
SET(SDL2TTF_VENDORED ON)

SET(SDL2IMAGE_SAMPLES OFF)
SET(SDL2IMAGE_TESTS OFF)
SET(SDL2IMAGE_AVIF OFF)
SET(SDL2IMAGE_VENDORED ON)

message("Fecthing SDL Source code")
# SDL2
# SET(SDL_SHARED FALSE)
FetchContent_Declare(
    sdl_lib
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.32.4 
)

FetchContent_MakeAvailable(sdl_lib)

# SDL2_image
FetchContent_Declare(
    sdl_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_SUBMODULES external/
    GIT_TAG release-2.8.8
)

FetchContent_MakeAvailable(sdl_image)

# SDL2_ttf
FetchContent_Declare(
    sdl_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.20.2
)

FetchContent_MakeAvailable(sdl_ttf)

# SDL2_mixer
SET(SDL2MIXER_VENDORED TRUE)
FetchContent_Declare(
    sdl_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.6.3
)

FetchContent_MakeAvailable(sdl_mixer)

message("END Fecthing SDL Source code")

