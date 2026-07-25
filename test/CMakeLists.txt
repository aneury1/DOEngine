
cmake_minimum_required(VERSION 3.22.1)

project(Doengine_tests)

include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(${CMAKE_SOURCE_DIR}/test/)

message("include dirs: ${CMAKE_SOURCE_DIR}")

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

target_link_libraries(GTest::GTest INTERFACE gtest_main gmock_main)

add_executable(${PROJECT_NAME}
    fixtures/DoEngineFixture.h
    units/utApplication.cpp
    units/utUtils.cpp
    units/utLinkList.cpp
    # units/utCircularArray.cpp
    units/utGameStateManager.cpp
    units/utFPSManager.cpp
    units/utEventHandler.cpp
    units/utSDLKeyboard.cpp
    units/utSDLMouse.cpp
    units/utSDLJoypad.cpp
    units/utSprite.cpp

    ../src/GameState/GameStateManager.cpp
    ../src/Network/UDPPacket.cpp
    ../src/Timer/FPSManager.cpp
    ../src/Event/Event.cpp
    ../src/Event/SDLKeyboard.cpp
    ../src/Event/SDLMouse.cpp
    ../src/Event/SDLJoypad.cpp
    ../src/Event/EventHandler.cpp

    ../src/Texture/Texture.cpp
    ../src/Texture/Sprite.cpp
    ../src/Font/TTFText.cpp
    ../src/Application/GameState.cpp
    ../src/Application/Application.cpp
    ../src/Application/Logger.cpp
    ../src/Application/WindowManager.cpp
    ../src/Application/SDLWindowManager.cpp
    ../src/Application/SDLRenderer.cpp
    ../src/Application/SDLTTFText.cpp
    ../src/Application/SDLTexture.cpp
    ../src/Window/Window.cpp
)

add_compile_definitions(DOENGINE_TESTING)

add_library(SDL2_MOCK
    mocks/SDLMock.h
    mocks/SDLMock.cpp
)

target_include_directories(SDL2_MOCK PUBLIC mocks/include)
# target_include_directories(SDL2_MOCK PUBLIC ${sdl_lib_BINARY_DIR}/include)
target_include_directories(SDL2_MOCK PUBLIC ${CMAKE_SOURCE_DIR}/external/doengine-shared/SDL2/SDL/include)
target_include_directories(SDL2_MOCK PUBLIC ${CMAKE_SOURCE_DIR}/external/doengine-shared/SDL2/SDL/src/joystick)
target_include_directories(SDL2_MOCK PUBLIC ${CMAKE_SOURCE_DIR}/external/doengine-shared/SDL2/SDL_image/include)
target_include_directories(SDL2_MOCK PUBLIC ${CMAKE_SOURCE_DIR}/external/doengine-shared/SDL2/SDL_mixer/include)
target_include_directories(SDL2_MOCK PUBLIC ${CMAKE_SOURCE_DIR}/external/doengine-shared/SDL2/SDL_ttf)
# target_include_directories(SDL2_MOCK PUBLIC ${sdl_lib_BINARY_DIR}/include-config-debug/SDL2)

add_library(DOENGINE_MOCKS
    mocks/GameStateMock.h
    mocks/FPSManagerMock.h
    mocks/CameraMock.h
    mocks/MusicHandlerMock.h
    mocks/ParticleMock.h
    mocks/RendererMock.h
    mocks/FontMock.h
    mocks/EventHandlerMock.h
    mocks/GameObjectMock.h
    mocks/GameStateManagerMock.h
    mocks/UDPPacketMock.h
    mocks/MouseMock.h
    mocks/JoypadMock.h
    mocks/NativeStructsMock.h
)

target_link_libraries(DOENGINE_MOCKS PUBLIC
  SDL2_MOCK
)

target_link_libraries(SDL2_MOCK PRIVATE
    GTest::gmock
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    DOENGINE_MOCKS
    GTest::GTest
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

target_compile_features(Doengine_tests PUBLIC cxx_std_20)

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME})

# if(DOENGINE_COVERAGE)
#   message("Compiling with coverage flags")
#   # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
#   # set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#   # set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#   set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0")
#   append_coverage_compiler_flags()
#   setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_cov
#         BASE_DIRECTORY ../
#         EXCLUDE "test/" "build/"
#     )
# endif()