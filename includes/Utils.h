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


// Template function to handle any data type (int, float, double)
template <typename T>
T map_value(T value, T in_min, T in_max, T out_min, T out_max) {
    
    // Check for division by zero to avoid crashes
    if (in_min == in_max) {
        return out_min; // or handle error as needed
    }

    // The Standard Formula
    // We cast to double for the calculation to preserve precision, 
    // then cast back to T (the original type) for the return value.
    return static_cast<T>(
        out_min + (static_cast<double>(value) - in_min) * (out_max - out_min) / (in_max - in_min)
    );
}

 


#if 0
template <typename T>
T map_constrained(T value, T in_min, T in_max, T out_min, T out_max) {
    
    // 1. Handle division by zero
    if (in_min == in_max) {
        return out_min; 
    }

    // 2. Perform the standard map calculation
    // We cast to double for precision, then back to T
    T result = static_cast<T>(
        out_min + (static_cast<double>(value) - in_min) * (out_max - out_min) / (in_max - in_min)
    );

    // 3. Determine the true lower and upper bounds of the output range
    // We do this because out_min might be larger than out_max (inverted range)
    T lower_bound = std::min(out_min, out_max);
    T upper_bound = std::max(out_min, out_max);

    // 4. Clamp the result
    // If you are using C++17 or newer, you can use: return std::clamp(result, lower_bound, upper_bound);
    
    if (result < lower_bound) return lower_bound;
    if (result > upper_bound) return upper_bound;
    return result;
}
#endif
template<typename T>
T Distance(T t1, T t2)
{
    return sqrt(t1-t2);
}

} // namespace doengine