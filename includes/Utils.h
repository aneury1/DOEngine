#pragma once
#include <vector>
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

std::vector<std::string> extractValueFromXML(std::string mainBuffer, std::string tagtitle)
{
    std::vector<std::string> ret;
    auto fndbeg = mainBuffer.find_first_of(tagtitle+">");
    auto fndend = mainBuffer.find_first_of("</"+tagtitle+">");
    while(fndbeg != std::string::npos)
    {
        
    }
    return ret;
}






} // namespace doengine