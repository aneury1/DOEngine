#pragma once

#include <algorithm>
#include <limits>
#include <random>
namespace doengine
{
template <typename V1, typename V2>
struct Optional
{
    V1 v1;
    V2 v2;
};

template <typename T = long>
inline T getRandomInt(const T startRange, const T endRange)
{
    std::random_device rd;
    std::uniform_int_distribution<T> dist(startRange, endRange);
    return dist(rd);
}

template <typename T = double>
inline T getRandomReal(const T startRange, const T endRange)
{
    std::random_device rd;
    std::uniform_real_distribution<T> dist(startRange, endRange);
    return dist(rd);
}

template <typename T>
constexpr T getPercentageFrom(const T percentage, const T currentValue)
{
    auto result = (percentage / 100.0) * currentValue;

    if (percentage == std::numeric_limits<T>::max())
        result = std::numeric_limits<T>::max();
    else if (percentage == std::numeric_limits<T>::min())
        result = std::numeric_limits<T>::min();

    return result;
}

template <typename T>
constexpr T clamp(const T v, const T min, const T max)
{
    return std::min(max, std::max(v, min));
}

double DegreesToRadians(double degree)
{
    return (degree * (M_PI/180.0));
}

#include <string>

#if defined(_WIN32)
    #include <direct.h>
    #define getcwd _getcwd
    #define PATH_MAX _MAX_PATH
#else
    #include <unistd.h>
    #include <limits.h>
#endif

static inline std::string getCurrentPath()
{
    char buffer[PATH_MAX];
    return getcwd(buffer, sizeof(buffer)) ? buffer : "";
}


template<class T>
bool isItemInGroup(const T type, std::vector<T> f)
{
    for(auto i : f)
        if( i == type)
            return true;
    return false;
}

Rect CenterRect(const Rect& outer, const Rect& inner)
{
    Rect result = inner;

    result.x = outer.x + (outer.w - inner.w) / 2;
    result.y = outer.y + (outer.h - inner.h) / 2;

    return result;
}

Rect RectSizeFromPercentage(const Rect& reference,
                                float percentW,
                                float percentH)
{
    Rect result;

    result.x = 0;
    result.y = 0;
    result.w = static_cast<int>(reference.w * (percentW / 100.0f));
    result.h = static_cast<int>(reference.h * (percentH / 100.0f));

    return result;
}
Rect RectSizeFromPercentageUniform(const Rect& reference,
                                       float percent)
{
    Rect result;
    int size = static_cast<int>(
        std::min(reference.w, reference.h) * (percent / 100.0f));

    result = { 0, 0, size, size };
    return result;
}

} // namespace doengine