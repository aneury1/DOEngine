#!/usr/bin/env bash

# =========================
# Configuration
# remember install  inotify-tools
# =========================

# Folders to watch (add as many as needed)
WATCH_DIRS=(
    "./src"
    "./includes"
   # "./third_party"
)

BUILD_CMD="cmake --build ./build"          # or: cmake --build build
EXECUTABLE="./build/DOENGINE-BattleSpawn"        # path to your executable
PID_FILE="/tmp/app.pid"

# =========================
# Functions
# =========================

stop_app() {
    if [[ -f "$PID_FILE" ]]; then
        PID=$(cat "$PID_FILE")
        if kill -0 "$PID" 2>/dev/null; then
            echo "Stopping app (PID $PID)..."
            kill "$PID"
            wait "$PID" 2>/dev/null
        fi
        rm -f "$PID_FILE"
    fi
}

build_and_run() {
    echo "Building..."
    if $BUILD_CMD; then
        echo "Build successful. Starting app..."
        $EXECUTABLE &
        echo $! > "$PID_FILE"
    else
        echo "Build failed."
    fi
}

cleanup() {
    echo "Shutting down..."
    stop_app
    exit 0
}

trap cleanup SIGINT SIGTERM

# =========================
# Initial run
# =========================
build_and_run

# =========================
# Watch loop
# =========================
echo "Watching directories:"
printf '  %s\n' "${WATCH_DIRS[@]}"

inotifywait -m -r \
    -e modify,create,delete,move \
    --format '%w%f' \
    "${WATCH_DIRS[@]}" | while read file; do

    if [[ "$file" =~ \.(c|cpp|h|hpp)$ ]]; then
        echo "Change detected: $file"
        stop_app
        build_and_run
    fi
done
