#include "opengl_decls.h"

namespace doengine
{
bool LoadMinimalGL()
{
#define LOAD_GL(fn)                                                            \
    fn = (decltype(fn))SDL_GL_GetProcAddress(#fn);                             \
    if (!fn)                                                                   \
        return false;
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
    /// LOAD_GL(glDrawArrays)
    LOAD_GL(glDeleteShader)

#undef LOAD_GL
    return true;
}

const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        uniform mat4 projection;
        uniform vec4 color;
        out vec4 fragColor;
        
        void main() {
            gl_Position = projection * vec4(aPos, 0.0, 1.0);
            fragColor = color;
        }
    )";

const char* fragmentShaderSource = R"(
        #version 330 core
        in vec4 fragColor;
        out vec4 FragColor;
        
        void main() {
            FragColor = fragColor;
        }
    )";

PrimitiveGLRenderer::PrimitiveGLRenderer()
{
    init();
}

void PrimitiveGLRenderer::init()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}
void PrimitiveGLRenderer::quit()
{
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteProgram(program);
}

void PrimitiveGLRenderer::setProjection(const Mat4& projection)
{
    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.m);
}

void PrimitiveGLRenderer::drawPoint(const Point& point, const Color& color,
                                    float size)
{

}

void PrimitiveGLRenderer::drawLine(const Point& start, const Point& end,
                                   const Color& color, float width )
{
 
}

void PrimitiveGLRenderer::drawRect(const Rect& rect, const Color& color,
                                   bool filled )
{
 
 
}

void PrimitiveGLRenderer::drawCircle(const Point& center, float radius,
                                     const Color& color, int segments,
                                     bool filled)
{
 
}

} // namespace doengine