#if 0 

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


#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

static PFNGLGENVERTEXARRAYSPROC        glGenVertexArrays;
static PFNGLBINDVERTEXARRAYPROC        glBindVertexArray;
static PFNGLGENBUFFERSPROC             glGenBuffers;
static PFNGLBINDBUFFERPROC             glBindBuffer;
static PFNGLBUFFERDATAPROC             glBufferData;
static PFNGLBUFFERSUBDATAPROC          glBufferSubData;
static PFNGLVERTEXATTRIBPOINTERPROC    glVertexAttribPointer;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
static PFNGLCREATESHADERPROC           glCreateShader;
static PFNGLSHADERSOURCEPROC           glShaderSource;
static PFNGLCOMPILESHADERPROC          glCompileShader;
static PFNGLCREATEPROGRAMPROC          glCreateProgram;
static PFNGLATTACHSHADERPROC           glAttachShader;
static PFNGLLINKPROGRAMPROC            glLinkProgram;
static PFNGLUSEPROGRAMPROC             glUseProgram;
static PFNGLGETUNIFORMLOCATIONPROC     glGetUniformLocation;
static PFNGLUNIFORM4FPROC              glUniform4f;
static PFNGLUNIFORM2FPROC              glUniform2f;
///static PFNGLDRAWARRAYSEXTPROC          glDrawArrays;
static PFNGLDELETESHADERPROC           glDeleteShader;

bool LoadMinimalGL()
{
#define LOAD_GL(fn) \
    fn = (decltype(fn))SDL_GL_GetProcAddress(#fn); \
    if (!fn) return false;

    LOAD_GL(glGenVertexArrays)
    LOAD_GL(glBindVertexArray)
    LOAD_GL(glGenBuffers)
    LOAD_GL(glBindBuffer)
    LOAD_GL(glBufferData)
    LOAD_GL(glBufferSubData)
    LOAD_GL(glVertexAttribPointer)
    LOAD_GL(glEnableVertexAttribArray)
    LOAD_GL(glCreateShader)
    LOAD_GL(glShaderSource)
    LOAD_GL(glCompileShader)
    LOAD_GL(glCreateProgram)
    LOAD_GL(glAttachShader)
    LOAD_GL(glLinkProgram)
    LOAD_GL(glUseProgram)
    LOAD_GL(glGetUniformLocation)
    LOAD_GL(glUniform4f)
    LOAD_GL(glUniform2f)
    ///OAD_GL(glDrawArrays)
    LOAD_GL(glDeleteShader)

#undef LOAD_GL
    return true;
}