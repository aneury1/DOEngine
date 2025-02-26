#ifndef __OPENGL_LOADER_H_DEFINED
#define __OPENGL_LOADER_H_DEFINED

#include <iostream>
#include <unordered_map>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <dlfcn.h>
#endif

class OpenGLLoader {
public:
     OpenGLLoader();
    ~OpenGLLoader();

    void* loadFunction(const char* name);

private:
#if defined(_WIN32)
    HMODULE openglLib;
#elif defined(__linux__) || defined(__APPLE__)
    void* openglLib;
#endif
};




#endif  ///__OPENGL_LOADER_H_DEFINED