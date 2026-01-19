cmake_minimum_required(VERSION 3.18.1)

project(Doengine)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths relative to the Android folder
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(INCLUDES_DIR "${PROJECT_ROOT}/includes")
set(SRC_DIR "${PROJECT_ROOT}/src")
set(TEST_DIR "${SRC_DIR}/test")

# Option to build as shared or static library
option(BUILD_SHARED_LIBS "Build shared library instead of static" ON)
option(BUILD_TESTS "Build test executable" FALSE)

# Include FetchContent module for downloading dependencies
include(FetchContent)

# Set SDL2 build options - force shared libraries for all SDL components
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

# SDL2_image options
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)

# SDL2_mixer options
set(SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE)

# SDL2_ttf options
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)

# SDL2_net options
set(SDL2NET_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2NET_SAMPLES OFF CACHE BOOL "" FORCE)

# Fetch SDL2 from GitHub
message(STATUS "Fetching SDL2 from GitHub...")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Fetch SDL2_image from GitHub
message(STATUS "Fetching SDL2_image from GitHub...")
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.4
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Fetch SDL2_mixer from GitHub
message(STATUS "Fetching SDL2_mixer from GitHub...")
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.8.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Fetch SDL2_ttf from GitHub
message(STATUS "Fetching SDL2_ttf from GitHub...")
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Fetch SDL2_net from GitHub
message(STATUS "Fetching SDL2_net from GitHub...")
FetchContent_Declare(
    SDL2_net
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_net.git
    GIT_TAG release-2.2.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Fetch Google Test from GitHub
message(STATUS "Fetching Google Test from GitHub...")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# Disable Google Test installation and samples
set(INSTALL_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make SDL2 and family available
message(STATUS "Making SDL2 libraries available...")
FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net googletest)

# Collect all source files (excluding test directory)
file(GLOB_RECURSE DOENGINE_SOURCES 
    "${SRC_DIR}/*.c"
    "${SRC_DIR}/*.cpp"
)

# Remove test files from main library sources
list(FILTER DOENGINE_SOURCES EXCLUDE REGEX "${TEST_DIR}/.*")

# Collect all header files
file(GLOB_RECURSE DOENGINE_HEADERS 
    "${INCLUDES_DIR}/*.h"
    "${INCLUDES_DIR}/*.hpp"
)

# Collect test sources
if(BUILD_TESTS)
    file(GLOB_RECURSE TEST_SOURCES
        "${TEST_DIR}/fixtures/*.c"
        "${TEST_DIR}/fixtures/*.cpp"
        "${TEST_DIR}/mocks/*.c"
        "${TEST_DIR}/mocks/*.cpp"
        "${TEST_DIR}/units/*.c"
        "${TEST_DIR}/units/*.cpp"
    )
endif()

# Create the library target
if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${DOENGINE_SOURCES})
    message(STATUS "Building LibDoengine as SHARED library")
else()
    add_library(${PROJECT_NAME} STATIC ${DOENGINE_SOURCES})
    message(STATUS "Building LibDoengine as STATIC library")
endif()

# Include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${INCLUDES_DIR}
    PRIVATE
        ${SRC_DIR}
)

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
        SDL2_net::SDL2_net
)

# Link standard Android libraries
find_library(LOG_LIBRARY log)
find_library(ANDROID_LIBRARY android)
find_library(GLESV2_LIBRARY GLESv2)
find_library(EGL_LIBRARY EGL)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        ${LOG_LIBRARY}
        ${ANDROID_LIBRARY}
        ${GLESV2_LIBRARY}
        ${EGL_LIBRARY}
)

# Set compiler flags for Android
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -fPIC
)

# Define Android-specific macros
target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
        ANDROID
        __ANDROID__
)

# ========================================
# Test Executable Configuration
# ========================================
if(BUILD_TESTS AND TEST_SOURCES)
    message(STATUS "Building test executable...")
    
    # Create test executable
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
    
    # Include directories for tests
    target_include_directories(${PROJECT_NAME}_tests 
        PRIVATE
            ${INCLUDES_DIR}
            ${SRC_DIR}
            ${TEST_DIR}
            ${TEST_DIR}/fixtures
            ${TEST_DIR}/mocks
            ${TEST_DIR}/units
            ${googletest_SOURCE_DIR}/googletest/include
            ${googletest_SOURCE_DIR}/googlemock/include
    )
    
    # Link libraries for tests
    target_link_libraries(${PROJECT_NAME}_tests 
        PRIVATE
            ${PROJECT_NAME}
            gtest
            gtest_main
            gmock
            gmock_main
    )
    
    # Set compiler flags for tests
    target_compile_options(${PROJECT_NAME}_tests PRIVATE
        -Wall
        -Wextra
    )
    
    # Define Android-specific macros for tests
    target_compile_definitions(${PROJECT_NAME}_tests 
        PRIVATE
            ANDROID
            __ANDROID__
    )
    
    # Set output directory for test executable
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${ANDROID_ABI}"
    )
    
    message(STATUS "Test executable will be built: ${PROJECT_NAME}_tests")
else()
    if(BUILD_TESTS)
        message(STATUS "No test sources found in ${TEST_DIR}")
    else()
        message(STATUS "Test building disabled")
    endif()
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${ANDROID_ABI}"
)

# Set output directories for SDL2 libraries as well
set_target_properties(SDL2 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
)

if(TARGET SDL2_image)
    set_target_properties(SDL2_image PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
    )
endif()

if(TARGET SDL2_mixer)
    set_target_properties(SDL2_mixer PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
    )
endif()

if(TARGET SDL2_ttf)
    set_target_properties(SDL2_ttf PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
    )
endif()

if(TARGET SDL2_net)
    set_target_properties(SDL2_net PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib/${ANDROID_ABI}"
    )
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib/${ANDROID_ABI}
    ARCHIVE DESTINATION lib/${ANDROID_ABI}
)

install(DIRECTORY ${INCLUDES_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# Install SDL2 shared libraries
install(TARGETS SDL2
    LIBRARY DESTINATION lib/${ANDROID_ABI}
    RUNTIME DESTINATION lib/${ANDROID_ABI}
)

if(TARGET SDL2_image)
    install(TARGETS SDL2_image
        LIBRARY DESTINATION lib/${ANDROID_ABI}
        RUNTIME DESTINATION lib/${ANDROID_ABI}
    )
endif()

if(TARGET SDL2_mixer)
    install(TARGETS SDL2_mixer
        LIBRARY DESTINATION lib/${ANDROID_ABI}
        RUNTIME DESTINATION lib/${ANDROID_ABI}
    )
endif()

if(TARGET SDL2_ttf)
    install(TARGETS SDL2_ttf
        LIBRARY DESTINATION lib/${ANDROID_ABI}
        RUNTIME DESTINATION lib/${ANDROID_ABI}
    )
endif()

if(TARGET SDL2_net)
    install(TARGETS SDL2_net
        LIBRARY DESTINATION lib/${ANDROID_ABI}
        RUNTIME DESTINATION lib/${ANDROID_ABI}
    )
endif()

# Print configuration summary
message(STATUS "=== LibDoengine Build Configuration ===")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Android ABI: ${ANDROID_ABI}")
message(STATUS "Android Platform: ${ANDROID_PLATFORM}")
message(STATUS "Library Type: ${BUILD_SHARED_LIBS}")
message(STATUS "Build Tests: ${BUILD_TESTS}")
message(STATUS "Source Directory: ${SRC_DIR}")
message(STATUS "Include Directory: ${INCLUDES_DIR}")
message(STATUS "Test Directory: ${TEST_DIR}")
message(STATUS "SDL2 Libraries: Fetched from GitHub")
message(STATUS "Google Test: Fetched from GitHub (v1.14.0)")
message(STATUS "========================================")