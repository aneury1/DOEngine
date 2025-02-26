#include "OpenglLoader.h"
#include <GL/gl.h>
#include <GL/glx.h> 
OpenGLLoader::OpenGLLoader() {
#if defined(_WIN32)
    openglLib = LoadLibraryA("opengl32.dll");
    if (!openglLib) {
        std::cerr << "Failed to load opengl32.dll\n";
    }
#elif defined(__linux__)
    openglLib = dlopen("libGL.so.1", RTLD_LAZY);
    if (!openglLib) {
        std::cerr << "Failed to load libGL.so.1: " << dlerror() << "\n";
    }
#elif defined(__APPLE__)
    openglLib = dlopen("/System/Library/Frameworks/OpenGL.framework/OpenGL", RTLD_LAZY);
    if (!openglLib) {
        std::cerr << "Failed to load OpenGL framework\n";
    }
#endif
}

OpenGLLoader::~OpenGLLoader() {
#if defined(_WIN32)
    if (openglLib) FreeLibrary(openglLib);
#elif defined(__linux__) || defined(__APPLE__)
    if (openglLib) dlclose(openglLib);
#endif
}

void* OpenGLLoader::loadFunction(const char* name) {
    if (!openglLib) return nullptr;

#if defined(_WIN32)
    void* func = (void*)GetProcAddress(openglLib, name);
    if (!func) {
        func = (void*)wglGetProcAddress(name);
    }
#elif defined(__linux__) || defined(__APPLE__)
    void* func = dlsym(openglLib, name);
    if (!func) {
        func = (void*)glXGetProcAddress((GLubyte*)name);
    }
#endif

    if (!func) {
        std::cerr << "Failed to load OpenGL function: " << name << "\n";
    }

    return func;
}