/*
 * ============================================================================
 * DOEngine
 * Copyright (c) 2026 Victor D. Montero, Aneury Perez
 * All Rights Reserved.
 *
 * Licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice, this license notice, and this disclaimer
 *    MUST be included in all copies or substantial portions of the Software.
 *
 * 2. This notice may not be removed from the original source files distributed
 *    as part of this project.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ============================================================================
 */

#pragma once
#include <stdint.h>
#include <functional>
#include <memory>
#include <vector>
#include <atomic>

namespace doengine
{
class FpsManager
{
    std::atomic<uint32_t> start, elapsed, wait, fps, last_elapsed;
    std::atomic<uint64_t> lastCounter;
    std::atomic<uint64_t> frequency;
  public:
    FpsManager() : start(0L), elapsed(0L), fps(60L), last_elapsed(0.0f)
    {
    }

    virtual ~FpsManager()
    {
    }

    virtual void setFPS(long fps = 60);
    virtual void Start();
    virtual void Handle();
    virtual uint32_t getDeltaTime();
    virtual float getElapsedTime();
    virtual float getLastElapsedTime();
    void beginFrame();
    double endFrame();
    static double getTicks();
};



 
/*
class TimerManager {
public:
    void update(float deltaSeconds);

    Timer& addTimer(float seconds, Timer::Callback cb, bool repeat = false);
    void clear();

private:
    std::vector<std::unique_ptr<Timer>> m_timers;
};

*/


} // namespace doengine