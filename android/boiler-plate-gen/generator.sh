#!/bin/bash

# Setup Android Project for DoEngine Game
# This script creates the complete Android project structure

set -e

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${GREEN}=== DoEngine Android Project Setup ===${NC}"
echo ""

# Get script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DOENGINE_ROOT="$(dirname "$SCRIPT_DIR")"
ANDROID_PROJECT="${DOENGINE_ROOT}/AndroidGame"

# Configuration
APP_NAME="DoEngineGame"
PACKAGE_NAME="com.yourgame.doengine"

echo -e "${BLUE}Project will be created at:${NC} ${ANDROID_PROJECT}"
echo -e "${BLUE}DoEngine root:${NC} ${DOENGINE_ROOT}"
echo ""

# Create directory structure
echo -e "${YELLOW}Creating project structure...${NC}"

mkdir -p "${ANDROID_PROJECT}"
mkdir -p "${ANDROID_PROJECT}/app/src/main/java/com/yourgame/doengine"
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

# Create strings.xml
cat > "${ANDROID_PROJECT}/app/src/main/res/values/strings.xml" << 'EOF'
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <string name="app_name">DoEngine Game</string>
</resources>
EOF

echo -e "${GREEN}✓${NC} Created strings.xml"

# Create settings.gradle
cat > "${ANDROID_PROJECT}/settings.gradle" << 'EOF'
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

rootProject.name = "DoEngineGame"
include ':app'
EOF

echo -e "${GREEN}✓${NC} Created settings.gradle"

# Create gradle.properties
cat > "${ANDROID_PROJECT}/gradle.properties" << 'EOF'
org.gradle.jvmargs=-Xmx2048m -Dfile.encoding=UTF-8
android.useAndroidX=true
android.enableJetifier=true
android.nonTransitiveRClass=false
EOF

echo -e "${GREEN}✓${NC} Created gradle.properties"

# Create local.properties with SDK path
if [ -n "$ANDROID_HOME" ]; then
    cat > "${ANDROID_PROJECT}/local.properties" << EOF
sdk.dir=${ANDROID_HOME}
EOF
    echo -e "${GREEN}✓${NC} Created local.properties with SDK path"
else
    echo -e "${YELLOW}⚠${NC} ANDROID_HOME not set, you'll need to set sdk.dir in local.properties manually"
fi

# Create .gitignore
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
EOF

echo -e "${GREEN}✓${NC} Created .gitignore"

# Create proguard-rules.pro
cat > "${ANDROID_PROJECT}/app/proguard-rules.pro" << 'EOF'
# Add project specific ProGuard rules here.
-keep class org.libsdl.app.** { *; }
EOF

echo -e "${GREEN}✓${NC} Created proguard-rules.pro"

echo ""
echo -e "${GREEN}=== Project Structure Created ===${NC}"
echo ""
echo "Next steps:"
echo "1. Copy the generated artifacts to the appropriate locations:"
echo "   - AndroidManifest.xml → ${ANDROID_PROJECT}/app/src/main/"
echo "   - build.gradle (app) → ${ANDROID_PROJECT}/app/"
echo "   - build.gradle (project) → ${ANDROID_PROJECT}/"
echo "   - MainActivity.java → ${ANDROID_PROJECT}/app/src/main/java/com/yourgame/doengine/"
echo "   - SDLActivity.java → ${ANDROID_PROJECT}/app/src/main/java/org/libsdl/app/"
echo "   - main.cpp → ${ANDROID_PROJECT}/app/src/main/cpp/"
echo "   - CMakeLists.txt (app) → ${ANDROID_PROJECT}/app/src/main/cpp/"
echo ""
echo "2. Build DoEngine libraries:"
echo "   cd ${DOENGINE_ROOT}/Android"
echo "   ./build-android.sh"
echo ""
echo "3. Copy DoEngine libraries to the Android project:"
echo "   cp ${DOENGINE_ROOT}/Android/build/libs/*/*.so ${ANDROID_PROJECT}/app/libs/"
echo ""
echo "4. Open project in Android Studio:"
echo "   studio ${ANDROID_PROJECT}"
echo ""
echo -e "${GREEN}Setup complete!${NC}"