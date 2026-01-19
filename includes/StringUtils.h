#pragma once
#include "StringUtils.h"
#include "DOEngine_SDL_includes.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace doengine
{
void readMapFile(const char* filename, std::vector<std::string>& ret);
std::vector<std::string> splitString(const std::string& original, char ch);
std::vector<char> splitChar(const std::string& original,
                            const std::string& ignoredChars);
std::string vectorOfCharToString(const std::vector<char>& chars);
int StringAsInt(const std::string& str);
template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

bool isCharInGroup(char ch, const std::string group);

} // namespace doengine
