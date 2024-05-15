#include "StringUtils.h"
#include <fstream>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

void readMapFile(const char *filename, std::vector<std::string>&ret){
    std::fstream file(filename , std::ios::in);
    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line)) {
            ret.emplace_back(line);
            line ="";
        }
    } 
  
}

std::vector<std::string> splitString(std::string original, char ch){
    std::vector<std::string>ret;
    std::string testEmplace;
    for(auto it : original){
        if(it == ch){
           if(testEmplace.size()>0){
               ret.emplace_back(testEmplace);
               testEmplace = "";
           }
        }else{
          testEmplace += it;
        }
    }
    if(testEmplace.size()>0){
        ret.emplace_back(testEmplace);
    }
    return ret;
}
std::vector<char> splitChar(std::string original, std::string ignoredChars){
    std::vector<char> ret;
    for(auto it : original){
        if(ignoredChars.find(it)==std::string::npos){
            ret.emplace_back(it);
        }
    }
    return ret;
}


std::string vectorOfCharToString(std::vector<char> chars){
    std::string str;
    for(auto it : chars)
    { 
        SDL_Log("%c", it);
        str+= it;
    }
    return str;
}


int StringAsInt(std::string str){
    return std::stoi(str);
}