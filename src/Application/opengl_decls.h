#ifndef OPENGL_DECL_H_DEFINED
#define OPENGL_DECL_H_DEFINED
#include <assert.h>
#include <cmath>

#include <vector>
#include "Renderer.h"
#include "Color.h"
#include "Geometric.h"
///#define DESKTOP_DEV 
namespace doengine
{
#ifdef DESKTOP_DEV
// OpenGL 4.x function pointers
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
static PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
static PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
static PFNGLBUFFERDATAPROC glBufferData = nullptr;
static PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
static PFNGLCREATESHADERPROC glCreateShader = nullptr;
static PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
static PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
static PFNGLUNIFORM4FPROC glUniform4f = nullptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
static PFNGLDELETESHADERPROC glDeleteShader = nullptr;
static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
#endif
struct BaseGLRenderer
{
    virtual ~BaseGLRenderer() = default;

    virtual void init() = 0;
    virtual void quit() = 0;
};

bool LoadMinimalGL();

struct PrimitiveGLRenderer : public BaseGLRenderer
{

 
    PrimitiveGLRenderer();
    virtual void init();
    virtual void quit();
    void setProjection(const Mat4& projection);
    void drawPoint(const Point& point, const Color& color, float size = 5.0f);
        void drawLine(const Point& start, const Point& end, const Color& color,
                  float width = 1.0f);
    void drawCircle(const Point& center, float radius, const Color& color,
                    int segments = 32, bool filled = true);

     void drawRect(const Rect& rect, const Color& color, bool filled = true);
};

}


#endif ///OPENGL_DECL_H_DEFINED