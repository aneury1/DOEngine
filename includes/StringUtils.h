#ifndef STRING_UTILS_H_DEFINED
#define STRING_UTILS_H_DEFINED
#include <vector>
#include <string>


void readMapFile(const char *filename, std::vector<std::string>&ret);

std::vector<std::string> splitString(const std::string& original, const char ch);
std::vector<char> splitChar(const std::string& original, const std::string& ignoredChars);

std::string makeString(const std::vector<char>& chars);

int StringAsInt(const std::string& str);

#endif