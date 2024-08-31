#pragma once
#include "StringUtils.h"
#include <SDL2/SDL.h>
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
} // namespace doengine