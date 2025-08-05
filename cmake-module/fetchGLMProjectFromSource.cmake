
include(FetchContent)
message("Fecthing glm Source code")
# flm
# SET(SDL_SHARED FALSE)
FetchContent_Declare(
    glm_lib
    GIT_REPOSITORY https://github.com/aneury1/glm
    # GIT_TAG release-3.2.20 
)

FetchContent_MakeAvailable(glm_lib)


message("END Fecthing GLM Source code")

