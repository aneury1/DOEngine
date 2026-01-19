#!/bin/bash

# Complete Android Project Generator for DoEngine
# This script creates all necessary files and project structure

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# Banner
echo -e "${CYAN}"
echo "╔════════════════════════════════════════════════════════════╗"
echo "║                                                            ║"
echo "║        DoEngine Android Project Generator                 ║"
echo "║        Complete Boilerplate Creator                       ║"
echo "║                                                            ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo -e "${NC}"
echo ""

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Default values
DEFAULT_DOENGINE_PATH="$(dirname "$SCRIPT_DIR")"
DEFAULT_PROJECT_NAME="DoEngineGame"
DEFAULT_PACKAGE_NAME="com.yourgame.doengine"
DEFAULT_APP_NAME="DoEngine Game"

# Prompt for configuration
echo -e "${BLUE}=== Project Configuration ===${NC}"
echo ""

# DoEngine path
read -p "Enter DoEngine root path [${DEFAULT_DOENGINE_PATH}]: " DOENGINE_ROOT
DOENGINE_ROOT=${DOENGINE_ROOT:-$DEFAULT_DOENGINE_PATH}

# Validate DoEngine path
if [ ! -d "$DOENGINE_ROOT" ]; then
    echo -e "${RED}Error: DoEngine path does not exist: ${DOENGINE_ROOT}${NC}"
    exit 1
fi

if [ ! -d "$DOENGINE_ROOT/includes" ] || [ ! -d "$DOENGINE_ROOT/src" ]; then
    echo -e "${YELLOW}Warning: DoEngine path doesn't contain 'includes' and 'src' directories${NC}"
    read -p "Continue anyway? (y/n): " CONTINUE
    if [ "$CONTINUE" != "y" ]; then
        exit 1
    fi
fi

# Project name
read -p "Enter project name [${DEFAULT_PROJECT_NAME}]: " PROJECT_NAME
PROJECT_NAME=${PROJECT_NAME:-$DEFAULT_PROJECT_NAME}

# Package name
read -p "Enter package name (e.g., com.company.game) [${DEFAULT_PACKAGE_NAME}]: " PACKAGE_NAME
PACKAGE_NAME=${PACKAGE_NAME:-$DEFAULT_PACKAGE_NAME}

# Validate package name
if ! [[ $PACKAGE_NAME =~ ^[a-z][a-z0-9_]*(\.[a-z][a-z0-9_]*)+$ ]]; then
    echo -e "${RED}Error: Invalid package name format. Use lowercase letters and dots (e.g., com.company.game)${NC}"
    exit 1
fi

# App display name
read -p "Enter app display name [${DEFAULT_APP_NAME}]: " APP_NAME
APP_NAME=${APP_NAME:-$DEFAULT_APP_NAME}

# Output directory
read -p "Enter output directory for Android project [${DOENGINE_ROOT}/AndroidGame]: " ANDROID_PROJECT
ANDROID_PROJECT=${ANDROID_PROJECT:-${DOENGINE_ROOT}/AndroidGame}

# Convert package name to path
PACKAGE_PATH=$(echo $PACKAGE_NAME | tr '.' '/')

echo ""
echo -e "${GREEN}=== Configuration Summary ===${NC}"
echo -e "${CYAN}DoEngine Path:${NC}     $DOENGINE_ROOT"
echo -e "${CYAN}Project Name:${NC}      $PROJECT_NAME"
echo -e "${CYAN}Package Name:${NC}      $PACKAGE_NAME"
echo -e "${CYAN}App Name:${NC}          $APP_NAME"
echo -e "${CYAN}Output Directory:${NC}  $ANDROID_PROJECT"
echo ""
read -p "Continue with this configuration? (y/n): " CONFIRM
if [ "$CONFIRM" != "y" ]; then
    echo "Cancelled."
    exit 0
fi

echo ""
echo -e "${YELLOW}Creating project structure...${NC}"

# Create directory structure
mkdir -p "${ANDROID_PROJECT}"
mkdir -p "${ANDROID_PROJECT}/app/src/main/java/${PACKAGE_PATH}"
mkdir -p "${ANDROID_PROJECT}/app/src/main/java/org/libsdl/app"
mkdir -p "${ANDROID_PROJECT}/app/src/main/cpp"
mkdir -p "${ANDROID_PROJECT}/app/src/main/res/values"
mkdir -p "${ANDROID_PROJECT}/app/src/main/res/mipmap-hdpi"
mkdir -p "${ANDROID_PROJECT}/app/src/main/res/mipmap-mdpi"
mkdir -p "${ANDROID_PROJECT}/app/src/main/res/mipmap-xhdpi"
mkdir -p "${ANDROID_PROJECT}/app/src/main/res/mipmap-xxhdpi"
mkdir -p "${ANDROID_PROJECT}/app/src/main/res/mipmap-xxxhdpi"
mkdir -p "${ANDROID_PROJECT}/app/libs/arm64-v8a"
mkdir -p "${ANDROID_PROJECT}/app/libs/armeabi-v7a"

echo -e "${GREEN}✓${NC} Directory structure created"

# Create AndroidManifest.xml
echo -e "${YELLOW}Generating AndroidManifest.xml...${NC}"
cat > "${ANDROID_PROJECT}/app/src/main/AndroidManifest.xml" << EOF
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools">

    <!-- Permissions -->
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.VIBRATE" />
    
    <!-- OpenGL ES 2.0 -->
    <uses-feature android:glEsVersion="0x00020000" android:required="true" />
    
    <!-- Game controllers and input devices -->
    <uses-feature android:name="android.hardware.gamepad" android:required="false"/>
    <uses-feature android:name="android.hardware.touchscreen" android:required="false"/>

    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:theme="@style/Theme.AppCompat.NoActionBar"
        android:hardwareAccelerated="true"
        tools:targetApi="31">
        
        <!-- SDL Activity -->
        <activity
            android:name=".MainActivity"
            android:label="@string/app_name"
            android:screenOrientation="landscape"
            android:configChanges="keyboard|keyboardHidden|orientation|screenSize|uiMode|screenLayout|smallestScreenSize"
            android:exported="true"
            android:launchMode="singleTask">
            
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>

</manifest>
EOF
echo -e "${GREEN}✓${NC} AndroidManifest.xml created"

# Create MainActivity.java
echo -e "${YELLOW}Generating MainActivity.java...${NC}"
cat > "${ANDROID_PROJECT}/app/src/main/java/${PACKAGE_PATH}/MainActivity.java" << EOF
package ${PACKAGE_NAME};

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {
    
    /**
     * This method is called by SDL before loading the native shared libraries.
     * It can be overridden to provide names of shared libraries to be loaded.
     * The default implementation returns the defaults. It never returns null.
     * An array returned by a new implementation must at least contain "SDL2".
     * Also keep in mind that the order the libraries are loaded may matter.
     * @return names of shared libraries to be loaded (e.g. "SDL2", "main").
     */
    @Override
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            "SDL2_image",
            "SDL2_mixer",
            "SDL2_ttf",
            "SDL2_net",
            "LibDoengine",
            "${PROJECT_NAME}"
        };
    }

    /**
     * This method is called by SDL using JNI.
     * @return the name of the main function to call from the native library
     */
    @Override
    protected String getMainFunction() {
        return "SDL_main";
    }
}
EOF
echo -e "${GREEN}✓${NC} MainActivity.java created"

# Create SDLActivity.java
echo -e "${YELLOW}Generating SDLActivity.java...${NC}"
cat > "${ANDROID_PROJECT}/app/src/main/java/org/libsdl/app/SDLActivity.java" << 'EOF'
package org.libsdl.app;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * SDL Activity - Base class for SDL applications on Android
 * This is a minimal implementation. For production, use the full SDLActivity from SDL2.
 */
public class SDLActivity extends Activity {
    private static final String TAG = "SDL";
    
    // Main SDL surface
    protected static SDLActivity mSingleton;
    protected static SDLSurface mSurface;

    // Load the .so files
    public static void loadLibraries() {
        for (String lib : mSingleton.getLibraries()) {
            System.loadLibrary(lib);
        }
    }

    /**
     * This method returns the name of the shared library to be loaded
     */
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            "main"
        };
    }

    /**
     * This method returns the name of the main function
     */
    protected String getMainFunction() {
        return "SDL_main";
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Keep singleton
        mSingleton = this;
        
        // Load libraries
        loadLibraries();
        
        // Set up the surface
        mSurface = new SDLSurface(getApplication());
        setContentView(mSurface);
        
        // Keep screen on
        mSurface.setKeepScreenOn(true);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Cleanup
        nativeQuit();
    }

    // Native methods
    public static native int nativeInit(Object arguments);
    public static native void nativeQuit();
    public static native void onNativeResize();
    public static native void onNativeSurfaceChanged();
    public static native void onNativeSurfaceDestroyed();

    /**
     * SDLSurface - Surface view for rendering
     */
    static class SDLSurface extends SurfaceView implements SurfaceHolder.Callback {
        
        public SDLSurface(Context context) {
            super(context);
            getHolder().addCallback(this);
            setFocusable(true);
            setFocusableInTouchMode(true);
            requestFocus();
        }

        @Override
        public void surfaceCreated(SurfaceHolder holder) {
            // Start native thread
            new Thread(new Runnable() {
                @Override
                public void run() {
                    nativeInit(null);
                }
            }).start();
        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            onNativeResize();
        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {
            onNativeSurfaceDestroyed();
        }
    }
}
EOF
echo -e "${GREEN}✓${NC} SDLActivity.java created"

# Create main.cpp
echo -e "${YELLOW}Generating main.cpp...${NC}"
cat > "${ANDROID_PROJECT}/app/src/main/cpp/main.cpp" << 'EOF'
#include <SDL.h>
#include <SDL_image.h>
#include <android/log.h>

#define LOG_TAG "DoEngineGame"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Game class using DoEngine (you'll implement this with your DoEngine)
class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

public:
    Game() : window(nullptr), renderer(nullptr), isRunning(false) {}

    bool initialize() {
        LOGI("Initializing game...");

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
            LOGE("SDL initialization failed: %s", SDL_GetError());
            return false;
        }

        // Initialize SDL_image
        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            LOGE("SDL_image initialization failed: %s", IMG_GetError());
            return false;
        }

        // Create window
        window = SDL_CreateWindow(
            "DoEngine Game",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
        );

        if (!window) {
            LOGE("Window creation failed: %s", SDL_GetError());
            return false;
        }

        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            LOGE("Renderer creation failed: %s", SDL_GetError());
            return false;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

        LOGI("Game initialized successfully!");
        isRunning = true;
        return true;
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                
                case SDL_FINGERDOWN:
                    LOGI("Touch down at: %f, %f", event.tfinger.x, event.tfinger.y);
                    break;
                
                case SDL_FINGERUP:
                    LOGI("Touch up at: %f, %f", event.tfinger.x, event.tfinger.y);
                    break;
                
                case SDL_APP_TERMINATING:
                    LOGI("App terminating");
                    isRunning = false;
                    break;
                
                case SDL_APP_LOWMEMORY:
                    LOGI("Low memory warning");
                    break;
                
                case SDL_APP_WILLENTERBACKGROUND:
                    LOGI("App will enter background");
                    break;
                
                case SDL_APP_DIDENTERBACKGROUND:
                    LOGI("App entered background");
                    break;
                
                case SDL_APP_WILLENTERFOREGROUND:
                    LOGI("App will enter foreground");
                    break;
                
                case SDL_APP_DIDENTERFOREGROUND:
                    LOGI("App entered foreground");
                    break;
            }
        }
    }

    void update() {
        // TODO: Update game logic using DoEngine
        // This is where you'll use your DoEngine API
    }

    void render() {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x30, 0xFF);
        SDL_RenderClear(renderer);

        // TODO: Render game using DoEngine
        // This is where you'll use your DoEngine rendering

        // Example: Draw a colored rectangle
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 
                              SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &fillRect);

        // Present
        SDL_RenderPresent(renderer);
    }

    void run() {
        LOGI("Starting game loop...");
        
        const float targetFPS = 60.0f;
        const float frameDelay = 1000.0f / targetFPS;

        while (isRunning) {
            Uint32 frameStart = SDL_GetTicks();

            handleEvents();
            update();
            render();

            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }

            // Calculate FPS (optional logging)
            static int frameCount = 0;
            static Uint32 fpsTimer = SDL_GetTicks();
            frameCount++;
            if (SDL_GetTicks() - fpsTimer > 1000) {
                LOGI("FPS: %d", frameCount);
                frameCount = 0;
                fpsTimer = SDL_GetTicks();
            }
        }

        LOGI("Game loop ended");
    }

    void cleanup() {
        LOGI("Cleaning up...");

        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        IMG_Quit();
        SDL_Quit();

        LOGI("Cleanup complete");
    }

    ~Game() {
        cleanup();
    }
};

// Main entry point
int main(int argc, char* argv[]) {
    LOGI("DoEngine Game starting...");

    Game game;
    
    if (!game.initialize()) {
        LOGE("Failed to initialize game!");
        return 1;
    }

    game.run();
    
    LOGI("DoEngine Game exiting normally");
    return 0;
}
EOF
echo -e "${GREEN}✓${NC} main.cpp created"

# Create CMakeLists.txt
echo -e "${YELLOW}Generating CMakeLists.txt...${NC}"
cat > "${ANDROID_PROJECT}/app/src/main/cpp/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.18.1)

project(${PROJECT_NAME})

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths
set(DOENGINE_ROOT "${DOENGINE_ROOT}")
set(DOENGINE_ANDROID "\${DOENGINE_ROOT}/Android")
set(GAME_SRC_DIR "\${CMAKE_CURRENT_SOURCE_DIR}")

# Add DoEngine library build
add_subdirectory(\${DOENGINE_ANDROID} \${CMAKE_CURRENT_BINARY_DIR}/doengine)

# Collect game source files
file(GLOB_RECURSE GAME_SOURCES 
    "\${GAME_SRC_DIR}/*.c"
    "\${GAME_SRC_DIR}/*.cpp"
)

# Create shared library for Android (required by SDL2)
add_library(\${PROJECT_NAME} SHARED \${GAME_SOURCES})

# Include directories
target_include_directories(\${PROJECT_NAME} 
    PRIVATE
        \${GAME_SRC_DIR}
        \${DOENGINE_ROOT}/includes
)

# Link libraries
target_link_libraries(\${PROJECT_NAME} 
    PRIVATE
        LibDoengine
        SDL2::SDL2main
)

# Set compiler flags
target_compile_options(\${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

# Android-specific macros
target_compile_definitions(\${PROJECT_NAME} 
    PRIVATE
        ANDROID
        __ANDROID__
)

# Export SDL_main for Android
set_target_properties(\${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-u Java_org_libsdl_app_SDLActivity_nativeInit"
)

message(STATUS "=== DoEngine Game Configuration ===")
message(STATUS "Game Sources: \${GAME_SRC_DIR}")
message(STATUS "DoEngine Path: \${DOENGINE_ROOT}")
message(STATUS "==================================")
EOF
echo -e "${GREEN}✓${NC} CMakeLists.txt created"

# Create build.gradle (app)
echo -e "${YELLOW}Generating build.gradle (app)...${NC}"
cat > "${ANDROID_PROJECT}/app/build.gradle" << EOF
plugins {
    id 'com.android.application'
}

android {
    namespace '${PACKAGE_NAME}'
    compileSdk 34

    defaultConfig {
        applicationId "${PACKAGE_NAME}"
        minSdk 21
        targetSdk 34
        versionCode 1
        versionName "1.0"

        ndk {
            abiFilters 'arm64-v8a', 'armeabi-v7a'
        }

        externalNativeBuild {
            cmake {
                arguments "-DANDROID_STL=c++_shared"
                cppFlags "-std=c++17 -Wall -Wextra"
            }
        }
    }

    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android-optimize.txt'), 'proguard-rules.pro'
        }
        debug {
            debuggable true
        }
    }

    externalNativeBuild {
        cmake {
            path file('src/main/cpp/CMakeLists.txt')
            version '3.18.1'
        }
    }

    compileOptions {
        sourceCompatibility JavaVersion.VERSION_1_8
        targetCompatibility JavaVersion.VERSION_1_8
    }

    sourceSets {
        main {
            jniLibs.srcDirs = ['libs']
        }
    }
}

dependencies {
    implementation 'androidx.appcompat:appcompat:1.6.1'
    implementation 'com.google.android.material:material:1.11.0'
}
EOF
echo -e "${GREEN}✓${NC} build.gradle (app) created"

# Create build.gradle (project)
echo -e "${YELLOW}Generating build.gradle (project)...${NC}"
cat > "${ANDROID_PROJECT}/build.gradle" << 'EOF'
// Top-level build file where you can add configuration options common to all sub-projects/modules.
plugins {
    id 'com.android.application' version '8.2.0' apply false
}
EOF
echo -e "${GREEN}✓${NC} build.gradle (project) created"

# Create settings.gradle
echo -e "${YELLOW}Generating settings.gradle...${NC}"
cat > "${ANDROID_PROJECT}/settings.gradle" << EOF
pluginManagement {
    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
}
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        google()
        mavenCentral()
    }
}

rootProject.name = "${PROJECT_NAME}"
include ':app'
EOF
echo -e "${GREEN}✓${NC} settings.gradle created"

# Create gradle.properties
echo -e "${YELLOW}Generating gradle.properties...${NC}"
cat > "${ANDROID_PROJECT}/gradle.properties" << 'EOF'
org.gradle.jvmargs=-Xmx2048m -Dfile.encoding=UTF-8
android.useAndroidX=true
android.enableJetifier=true
android.nonTransitiveRClass=false
EOF
echo -e "${GREEN}✓${NC} gradle.properties created"

# Create local.properties
if [ -n "$ANDROID_HOME" ]; then
    echo -e "${YELLOW}Generating local.properties...${NC}"
    cat > "${ANDROID_PROJECT}/local.properties" << EOF
sdk.dir=${ANDROID_HOME}
EOF
    echo -e "${GREEN}✓${NC} local.properties created with SDK path"
else
    echo -e "${YELLOW}⚠${NC} ANDROID_HOME not set, skipping local.properties"
fi

# Create strings.xml
echo -e "${YELLOW}Generating strings.xml...${NC}"
cat > "${ANDROID_PROJECT}/app/src/main/res/values/strings.xml" << EOF
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <string name="app_name">${APP_NAME}</string>
</resources>
EOF
echo -e "${GREEN}✓${NC} strings.xml created"

# Create proguard-rules.pro
echo -e "${YELLOW}Generating proguard-rules.pro...${NC}"
cat > "${ANDROID_PROJECT}/app/proguard-rules.pro" << 'EOF'
# Add project specific ProGuard rules here.
-keep class org.libsdl.app.** { *; }
EOF
echo -e "${GREEN}✓${NC} proguard-rules.pro created"

# Create .gitignore
echo -e "${YELLOW}Generating .gitignore...${NC}"
cat > "${ANDROID_PROJECT}/.gitignore" << 'EOF'
*.iml
.gradle
/local.properties
/.idea
.DS_Store
/build
/captures
.externalNativeBuild
.cxx
*.apk
*.ap_
*.dex
*.class
bin/
gen/
out/
app/libs/
EOF
echo -e "${GREEN}✓${NC} .gitignore created"

# Create README
echo -e "${YELLOW}Generating README.md...${NC}"
cat > "${ANDROID_PROJECT}/README.md" << EOF
# ${APP_NAME}

Android game project using DoEngine and SDL2.

## Project Information

- **Package Name**: ${PACKAGE_NAME}
- **Project Name**: ${PROJECT_NAME}
- **DoEngine Path**: ${DOENGINE_ROOT}

## Build Instructions

### 1. Build DoEngine Libraries

\`\`\`bash
cd ${DOENGINE_ROOT}/Android
./build-android.sh
\`\`\`

### 2. Copy Libraries to Android Project

\`\`\`bash
cp ${DOENGINE_ROOT}/Android/build/libs/arm64-v8a/*.so ${ANDROID_PROJECT}/app/libs/arm64-v8a/
cp ${DOENGINE_ROOT}/Android/build/libs/armeabi-v7a/*.so ${ANDROID_PROJECT}/app/libs/armeabi-v7a/
\`\`\`

### 3. Open in Android Studio

\`\`\`bash
studio ${ANDROID_PROJECT}
\`\`\`

Or open Android Studio and select "Open an Existing Project", then navigate to:
\`${ANDROID_PROJECT}\`

### 4. Build and Run

- Connect an Android device or start an emulator
- Click the "Run" button in Android Studio

## Project Structure

\`\`\`
${ANDROID_PROJECT}/
├── app/
│   ├── src/main/
│   │   ├── java/${PACKAGE_PATH}/
│   │   │   └── MainActivity.java
│   │   ├── cpp/
│   │   │   ├── main.cpp
│   │   │   └── CMakeLists.txt
│   │   ├── res/
│   │   └── AndroidManifest.xml
│   ├── libs/           (SDL2 & DoEngine .so files)
│   └── build.gradle
├── build.gradle
└── settings.gradle
\`\`\`

## Development

The main game code is in \`app/src/main/cpp/main.cpp\`. This is where you'll integrate your DoEngine API calls.

## Troubleshooting

### Libraries not found
Make sure you've built DoEngine and copied the .so files to the \`app/libs/\` directory.

### NDK not found
Set the ANDROID_NDK_ROOT environment variable or update \`local.properties\`.

### Build errors
Clean and rebuild:
\`\`\`bash
./gradlew clean
./gradlew build
\`\`\`
EOF
echo -e "${GREEN}✓${NC} README.md created"

# Create build helper script
echo -e "${YELLOW}Generating build-and-deploy.sh...${NC}"
cat > "${ANDROID_PROJECT}/build-and-deploy.sh" << EOF
#!/bin/bash

# Build and Deploy Script for ${APP_NAME}

set -e

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "\${GREEN}=== Building DoEngine Libraries ===\${NC}"
cd "${DOENGINE_ROOT}/Android"
./build-android.sh

echo ""
echo -e "\${GREEN}=== Copying Libraries to Android Project ===\${NC}"
cp -v "${DOENGINE_ROOT}/Android/build/libs/arm64-v8a/"*.so "${ANDROID_PROJECT}/app/libs/arm64-v8a/"
cp -v "${DOENGINE_ROOT}/Android/build/libs/armeabi-v7a/"*.so "${ANDROID_PROJECT}/app/libs/armeabi-v7a/"

echo ""
echo -e "\${GREEN}=== Libraries Deployed ===\${NC}"
echo "You can now build the Android project in Android Studio"
echo ""
echo "To open in Android Studio:"
echo "  studio ${ANDROID_PROJECT}"
EOF
chmod +x "${ANDROID_PROJECT}/build-and-deploy.sh"
echo -e "${GREEN}✓${NC} build-and-deploy.sh created"

# Summary
echo ""
echo -e "${GREEN}╔════════════════════════════════════════════════════════════╗${NC}"
echo -e "${GREEN}║                                                            ║${NC}"
echo -e "${GREEN}║              Project Created Successfully!                 ║${NC}"
echo -e "${GREEN}║                                                            ║${NC}"
echo -e "${GREEN}╚════════════════════════════════════════════════════════════╝${NC}"
echo ""
echo -e "${CYAN}Project Location:${NC} ${ANDROID_PROJECT}"
echo ""
echo -e "${BLUE}=== Next Steps ===${NC}"
echo ""
echo -e "${YELLOW}1.${NC} Build DoEngine libraries:"
echo -e "   cd ${DOENGINE_ROOT}/Android"
echo -e "   ./build-android.sh"
echo ""
echo -e "${YELLOW}2.${NC} Deploy libraries to Android project:"
echo -e "   cd ${ANDROID_PROJECT}"
echo -e "   ./build-and-deploy.sh"