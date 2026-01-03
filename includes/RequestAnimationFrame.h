#pragma once


#include <chrono>
#include <thread>
#include <functional>
#include <atomic>

class RequestAnimationFrame {
public:
    using Callback = std::function<void(double)>;

    explicit RequestAnimationFrame(double fps = 60.0)
        : frameDuration(std::chrono::duration<double>(1.0 / fps)),
          running(false) {}

    void start(Callback cb) {
        running = true;
        auto startTime = std::chrono::steady_clock::now();

        while (running) {
            auto now = std::chrono::steady_clock::now();
            double timestamp =
                std::chrono::duration<double, std::milli>(now - startTime).count();

            cb(timestamp);

            auto nextFrame = now + frameDuration;
            std::this_thread::sleep_until(nextFrame);
        }
    }

    void stop() {
        running = false;
    }

private:
    std::chrono::duration<double> frameDuration;
    std::atomic<bool> running;
};