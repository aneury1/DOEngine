
include(FetchContent)
message("Fecthing GLM Source code")
# SDL2
# SET(SDL_SHARED FALSE)
FetchContent_Declare(
    glm_lib
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm_lib)
 
 

 
message("END Fecthing GLM Source code")

