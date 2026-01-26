
#include "DOEngine_SDL_includes.h"

#include "FPSManager.h"

namespace doengine
{

void FpsManager::setFPS(long fps)
{
    this->fps = fps;
}

uint32_t FpsManager::getDeltaTime()
{
    return (uint32_t)(elapsed - start);
}

float FpsManager::getElapsedTime()
{
    return (float)(elapsed - start);
}

void FpsManager::Start()
{
    start = SDL_GetTicks();
    frequency = SDL_GetPerformanceFrequency();
    lastCounter = SDL_GetPerformanceCounter();
}

void FpsManager::Handle()
{
    const uint32_t frameDelay = 1000 / fps;

    uint32_t frameTime = SDL_GetTicks() - start;

    if (frameTime < frameDelay)
    {
        SDL_Delay(frameDelay - frameTime);
    }

    start = SDL_GetTicks();
}

void FpsManager::beginFrame()
{
    lastCounter = SDL_GetPerformanceCounter();
}

double FpsManager::endFrame()
{
    uint64_t now = SDL_GetPerformanceCounter();
    double deltaTime =
        static_cast<double>(now - lastCounter) / frequency;

    const double targetFrameTime = 1.0 / fps;

    if (deltaTime < targetFrameTime)
    {
        SDL_Delay(
            static_cast<Uint32>((targetFrameTime - deltaTime) * 1000.0)
        );

        now = SDL_GetPerformanceCounter();
        deltaTime =
            static_cast<double>(now - lastCounter) / frequency;
    }

    return deltaTime;
}

double FpsManager::getTicks()
{
    return SDL_GetTicks();
}

Timer::Timer(float durationSeconds, Callback cb, bool repeat)
    : m_duration(durationSeconds),
      m_elapsed(0.0f),
      m_repeat(repeat),
      m_active(true),
      m_callback(std::move(cb)) {}

void Timer::update(float deltaSeconds) {
    if (!m_active) return;

    m_elapsed += deltaSeconds;
    if (m_elapsed >= m_duration) {
        if (m_callback) {
            m_callback();
        }

        if (m_repeat) {
            m_elapsed = 0.0f;
        } else {
            m_active = false;
        }
    }
}

void Timer::reset() {
    m_elapsed = 0.0f;
    m_active = true;
}

void Timer::stop() {
    m_active = false;
}

bool Timer::isActive() const {
    return m_active;
}

Timer& TimerManager::addTimer(float seconds, Timer::Callback cb, bool repeat) {
    m_timers.push_back(
        std::make_unique<Timer>(seconds, std::move(cb), repeat)
    );
    return *m_timers.back();
}

void TimerManager::update(float deltaSeconds) {
    for (auto& timer : m_timers) {
        timer->update(deltaSeconds);
    }

    // Optional cleanup of inactive timers
    m_timers.erase(
        std::remove_if(
            m_timers.begin(),
            m_timers.end(),
            [](const std::unique_ptr<Timer>& t) {
                return !t->isActive();
            }),
        m_timers.end()
    );
}

void TimerManager::clear() {
    m_timers.clear();
}

} // namespace doengine