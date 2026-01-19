#!/bin/bash

# Android Build Script for LibDoengine
# This script builds the library for multiple Android ABIs

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Configuration
NDK_PATH="${ANDROID_NDK_ROOT:-$ANDROID_NDK}"

# If NDK_PATH points to the ndk directory (not a specific version), find the latest version
if [ -d "$NDK_PATH" ] && [ ! -f "$NDK_PATH/build/cmake/android.toolchain.cmake" ]; then
    echo -e "${YELLOW}NDK path appears to be the base directory, searching for installed versions...${NC}"
    # Find the latest NDK version
    LATEST_NDK=$(ls -1 "$NDK_PATH" | grep -E '^[0-9]+\.' | sort -V | tail -n 1)
    if [ -n "$LATEST_NDK" ]; then
        NDK_PATH="$NDK_PATH/$LATEST_NDK"
        echo -e "${GREEN}Found NDK version: ${NC}$LATEST_NDK"
    fi
fi

MIN_SDK_VERSION=21
TARGET_SDK_VERSION=33
BUILD_TYPE="Release"
LIBRARY_TYPE="SHARED"  # Change to "STATIC" for static library

# Android ABIs to build (uncomment the ones you need)
ABIS=(
    "arm64-v8a"
    "armeabi-v7a"
    # "x86"
    # "x86_64"
)

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="${SCRIPT_DIR}/build"

echo -e "${GREEN}=== LibDoengine Android Build Script ===${NC}"
echo ""

# Check if NDK is set
if [ -z "$NDK_PATH" ]; then
    echo -e "${RED}Error: Android NDK not found!${NC}"
    echo "Please set ANDROID_NDK_ROOT or ANDROID_NDK environment variable"
    echo "Example: export ANDROID_NDK_ROOT=/path/to/android-ndk"
    exit 1
fi

# Verify toolchain file exists
if [ ! -f "$NDK_PATH/build/cmake/android.toolchain.cmake" ]; then
    echo -e "${RED}Error: Android NDK toolchain not found at: $NDK_PATH${NC}"
    echo "The NDK path should point to a complete NDK installation."
    echo "Please check your NDK installation or set the correct path."
    echo ""
    echo "If your NDK is at /home/neonland/Android/Sdk/ndk, try:"
    echo "  export ANDROID_NDK_ROOT=/home/neonland/Android/Sdk/ndk/[version]"
    echo ""
    echo "Available NDK versions:"
    if [ -d "$(dirname "$NDK_PATH")" ]; then
        ls -1 "$(dirname "$NDK_PATH")" 2>/dev/null | grep -E '^[0-9]+\.' || echo "  No NDK versions found"
    fi
    exit 1
fi

echo -e "${GREEN}NDK Path: ${NC}$NDK_PATH"
echo -e "${GREEN}Min SDK: ${NC}$MIN_SDK_VERSION"
echo -e "${GREEN}Target SDK: ${NC}$TARGET_SDK_VERSION"
echo -e "${GREEN}Build Type: ${NC}$BUILD_TYPE"
echo -e "${GREEN}Library Type: ${NC}$LIBRARY_TYPE"
echo ""

# Function to build for a specific ABI
build_abi() {
    local ABI=$1
    echo -e "${YELLOW}Building for $ABI...${NC}"
    
    local ABI_BUILD_DIR="${BUILD_DIR}/${ABI}"
    mkdir -p "$ABI_BUILD_DIR"
    
    cd "$ABI_BUILD_DIR"
    
    # Configure with CMake
    cmake "${SCRIPT_DIR}" \
        -DCMAKE_TOOLCHAIN_FILE="${NDK_PATH}/build/cmake/android.toolchain.cmake" \
        -DANDROID_ABI="${ABI}" \
        -DANDROID_PLATFORM="android-${MIN_SDK_VERSION}" \
        -DANDROID_STL=c++_shared \
        -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
        -DBUILD_SHARED_LIBS=$([ "$LIBRARY_TYPE" = "SHARED" ] && echo "ON" || echo "OFF") \
        -DCMAKE_INSTALL_PREFIX="${BUILD_DIR}/install/${ABI}"
    
    # Build
    cmake --build . --config ${BUILD_TYPE} -- -j$(nproc 2>/dev/null || echo 4)
    
    # Install
    cmake --install .
    
    echo -e "${GREEN}✓ Successfully built for $ABI${NC}"
    echo ""
    
    cd "$SCRIPT_DIR"
}

# Clean build directory if requested
if [ "$1" = "clean" ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf "$BUILD_DIR"
    echo -e "${GREEN}✓ Clean complete${NC}"
    exit 0
fi

# Create output directory
mkdir -p "$BUILD_DIR"

# Build for each ABI
for ABI in "${ABIS[@]}"; do
    build_abi "$ABI"
done

# Create a summary
echo -e "${GREEN}=== Build Summary ===${NC}"
echo ""
echo "Libraries built for:"
for ABI in "${ABIS[@]}"; do
    LIB_PATH="${BUILD_DIR}/install/${ABI}/lib/${ABI}"
    if [ -d "$LIB_PATH" ]; then
        echo -e "  ${GREEN}✓${NC} $ABI"
        ls -lh "$LIB_PATH"/*.so 2>/dev/null || ls -lh "$LIB_PATH"/*.a 2>/dev/null || true
    fi
done

echo ""
echo -e "${GREEN}=== Build Complete ===${NC}"
echo "Output directory: ${BUILD_DIR}/install"
echo ""
echo "To clean build files, run: $0 clean"