
cmake_minimum_required(VERSION 2.13)
project(Doengine_tests)

include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(${CMAKE_SOURCE_DIR}/src/test/)
include_directories(${sdl_ttf_SOURCE_DIR})
include_directories(${sdl_image_SOURCE_DIR}/include)
include_directories(${sdl_mixer_SOURCE_DIR}/include)

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
    units/utUtils.cpp
    units/utLinkList.cpp
    # units/utGameStateManager.cpp
    units/utFPSManager.cpp
    #units/utEventHandler.cpp
    units/utSDLKeyboard.cpp
    units/utSDLMouse.cpp
    units/utSDLJoypad.cpp
    units/utSpriteOffset.cpp

    ../GameState/GameStateManager.cpp
    ../Network/UDPPacket.cpp
    ../Timer/FPSManager.cpp
    #../Event/Event.cpp
    ../Event/SDLKeyboard.cpp
    ../Event/SDLMouse.cpp
    ../Event/SDLJoypad.cpp
)

add_compile_definitions(DOENGINE_TESTING)

add_library(SDL2_MOCK
    mocks/SDLMock.h
    mocks/SDLMock.cpp
)

target_include_directories(SDL2_MOCK PUBLIC mocks/include)
target_include_directories(SDL2_MOCK PUBLIC ${sdl_lib_BINARY_DIR}/include)
target_include_directories(SDL2_MOCK PUBLIC ${sdl_lib_BINARY_DIR}/include/SDL2)
target_include_directories(SDL2_MOCK PUBLIC ${sdl_lib_BINARY_DIR}/include-config-debug/SDL2)

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

add_test(NAME testapp_gtest
    COMMAND ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

if(DOENGINE_COVERAGE)
    message("Compiling with coverage flags")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    # set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    # set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0")
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_cov
        BASE_DIRECTORY ../
        EXCLUDE "test/" "build/"
    )
endif()
