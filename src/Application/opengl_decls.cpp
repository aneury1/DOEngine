#include "opengl_decls.h"
#include <iostream>
#include "DOEngine_SDL_includes.h"
#include "Application.h"
#include "Renderer.h"
namespace doengine
{
#if 0
// Shader sources (OpenGL 4.5 Core Profile)
static const char* VERTEX_SHADER = R"(
#version 450 core

layout (location = 0) in vec2 aPos;

uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
}
)";

static const char* FRAGMENT_SHADER = R"(
#version 450 core

uniform vec4 uColor;
out vec4 FragColor;

void main()
{
    FragColor = uColor;
}
)";

// Rectangle renderer state
struct RectRenderer
{
    GLuint VAO;
    GLuint VBO;
    GLuint shaderProgram;
    GLint projectionLoc;
    GLint colorLoc;
    bool initialized;
};

static RectRenderer g_rectRenderer = {0, 0, 0, -1, -1, false};

// Load OpenGL functions
bool LoadMinimalGL()
{
#define LOAD_GL_FUNC(name)                                                     \
    name = (decltype(name))SDL_GL_GetProcAddress(#name);                       \
    if (!name)                                                                 \
    {                                                                          \
        std::cerr << "Failed to load " << #name << std::endl;                  \
        return false;                                                          \
    }

    LOAD_GL_FUNC(glGenVertexArrays);
    LOAD_GL_FUNC(glBindVertexArray);
    LOAD_GL_FUNC(glDeleteVertexArrays);
    LOAD_GL_FUNC(glGenBuffers);
    LOAD_GL_FUNC(glBindBuffer);
    LOAD_GL_FUNC(glDeleteBuffers);
    LOAD_GL_FUNC(glBufferData);
    LOAD_GL_FUNC(glBufferSubData);
    LOAD_GL_FUNC(glVertexAttribPointer);
    LOAD_GL_FUNC(glEnableVertexAttribArray);
    LOAD_GL_FUNC(glCreateShader);
    LOAD_GL_FUNC(glShaderSource);
    LOAD_GL_FUNC(glCompileShader);
    LOAD_GL_FUNC(glCreateProgram);
    LOAD_GL_FUNC(glAttachShader);
    LOAD_GL_FUNC(glLinkProgram);
    LOAD_GL_FUNC(glUseProgram);
    LOAD_GL_FUNC(glDeleteProgram);
    LOAD_GL_FUNC(glGetUniformLocation);
    LOAD_GL_FUNC(glUniform4f);
    LOAD_GL_FUNC(glUniformMatrix4fv);
    LOAD_GL_FUNC(glDeleteShader);
    LOAD_GL_FUNC(glGetShaderiv);
    LOAD_GL_FUNC(glGetShaderInfoLog);
    LOAD_GL_FUNC(glGetProgramiv);
    LOAD_GL_FUNC(glGetProgramInfoLog);

#undef LOAD_GL_FUNC
    return true;
}

// Compile shader
GLuint CompileShader(GLenum type, const char* source)
{
    GLuint shader =0;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Check compilation status
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

// Create shader program
GLuint CreateShaderProgram()
{
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);

    if (!vertexShader || !fragmentShader)
    {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check linking status
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;


}

// Initialize rectangle renderer
bool InitRectRenderer()
{
    if (g_rectRenderer.initialized)
    {
        return true;
    }

    // Create shader program
    g_rectRenderer.shaderProgram = CreateShaderProgram();
    if (!g_rectRenderer.shaderProgram)
    {
        std::cerr << "Failed to create shader program" << std::endl;
        return false;
    }

    // Get uniform locations
    g_rectRenderer.projectionLoc =
        glGetUniformLocation(g_rectRenderer.shaderProgram, "uProjection");
    g_rectRenderer.colorLoc =
        glGetUniformLocation(g_rectRenderer.shaderProgram, "uColor");

    // Create VAO and VBO
    glGenVertexArrays(1, &g_rectRenderer.VAO);
    glGenBuffers(1, &g_rectRenderer.VBO);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);

    // Allocate buffer for 6 vertices (2 triangles) with 2 floats each
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);

    // Set vertex attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    g_rectRenderer.initialized = true;
    std::cout << "Rectangle renderer initialized successfully" << std::endl;
    return true;
}

// Create orthographic projection matrix
void CreateOrthoMatrix(float left, float right, float bottom, float top,
                       float* matrix)
{
    // Initialize to identity
    for (int i = 0; i < 16; i++)
    {
        matrix[i] = 0.0f;
    }

    // Orthographic projection
    matrix[0] = 2.0f / (right - left);
    matrix[5] = 2.0f / (top - bottom);
    matrix[10] = -1.0f;
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[15] = 1.0f;
}

// Draw filled rectangle using OpenGL 4.x
void GL_DrawFillRect(SDL_Window* window, const Rect& rect, const Color& color)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    // Get window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Create orthographic projection matrix (pixel coordinates)
    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f,
                      projMatrix);

    // Calculate vertex positions (two triangles forming a rectangle)
    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = rect.x + rect.w;
    float y2 = rect.y + rect.h;

    float vertices[] = {
        // First triangle
        x1, y1, // Top-left
        x2, y1, // Top-right
        x2, y2, // Bottom-right

        // Second triangle
        x1, y1, // Top-left
        x2, y2, // Bottom-right
        x1, y2  // Bottom-left
    };

    // Use shader program
    glUseProgram(g_rectRenderer.shaderProgram);

    // Set projection matrix
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);

    // Set color (convert from 0-255 to 0.0-1.0 range)
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    // Bind VAO and update VBO
    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Draw the rectangle
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind
    glBindVertexArray(0);
    glUseProgram(0);
}

void GL_DrawPoint(SDL_Window* window,const Point& point, const Color& color)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }
}


void GL_DrawRect(SDL_Window* window, const Rect& rect, const Color& color, float thickness = 1.0f)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, projMatrix);

    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = rect.x + rect.w;
    float y2 = rect.y + rect.h;

    // Four rectangles for each border
    float vertices[4][12] = {
        // Top border
        {x1, y1, x2, y1, x2, y1 + thickness, x1, y1, x2, y1 + thickness, x1, y1 + thickness},
        // Right border
        {x2 - thickness, y1, x2, y1, x2, y2, x2 - thickness, y1, x2, y2, x2 - thickness, y2},
        // Bottom border
        {x1, y2 - thickness, x2, y2 - thickness, x2, y2, x1, y2 - thickness, x2, y2, x1, y2},
        // Left border
        {x1, y1, x1 + thickness, y1, x1 + thickness, y2, x1, y1, x1 + thickness, y2, x1, y2}
    };

    glUseProgram(g_rectRenderer.shaderProgram);
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);

    for (int i = 0; i < 4; i++)
    {
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[i]), vertices[i]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

// Draw filled circle
void GL_DrawFilledCircle(SDL_Window* window, float centerX, float centerY, float radius, const Color& color, int segments = 32)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, projMatrix);

    // Create triangle fan vertices
    std::vector<float> vertices;
    vertices.reserve((segments + 2) * 2);

    // Center point
    vertices.push_back(centerX);
    vertices.push_back(centerY);

    // Circle points
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * M_PI * i / segments;
        vertices.push_back(centerX + radius * cosf(angle));
        vertices.push_back(centerY + radius * sinf(angle));
    }

    glUseProgram(g_rectRenderer.shaderProgram);
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);

    // Restore buffer size
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glUseProgram(0);
}

// Draw circle outline
void GL_DrawCircle(SDL_Window* window, float centerX, float centerY, float radius, const Color& color, float thickness = 1.0f, int segments = 32)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, projMatrix);

    std::vector<float> vertices;
    vertices.reserve(segments * 12);

    for (int i = 0; i < segments; i++)
    {
        float angle1 = 2.0f * M_PI * i / segments;
        float angle2 = 2.0f * M_PI * (i + 1) / segments;

        float x1_outer = centerX + radius * cosf(angle1);
        float y1_outer = centerY + radius * sinf(angle1);
        float x1_inner = centerX + (radius - thickness) * cosf(angle1);
        float y1_inner = centerY + (radius - thickness) * sinf(angle1);

        float x2_outer = centerX + radius * cosf(angle2);
        float y2_outer = centerY + radius * sinf(angle2);
        float x2_inner = centerX + (radius - thickness) * cosf(angle2);
        float y2_inner = centerY + (radius - thickness) * sinf(angle2);

        // First triangle
        vertices.push_back(x1_outer); vertices.push_back(y1_outer);
        vertices.push_back(x2_outer); vertices.push_back(y2_outer);
        vertices.push_back(x1_inner); vertices.push_back(y1_inner);

        // Second triangle
        vertices.push_back(x2_outer); vertices.push_back(y2_outer);
        vertices.push_back(x2_inner); vertices.push_back(y2_inner);
        vertices.push_back(x1_inner); vertices.push_back(y1_inner);
    }

    glUseProgram(g_rectRenderer.shaderProgram);
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glUseProgram(0);
}

// Draw line
void GL_DrawLine(SDL_Window* window, float x1, float y1, float x2, float y2, const Color& color, float thickness = 1.0f)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, projMatrix);

    // Calculate perpendicular vector for thickness
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrtf(dx * dx + dy * dy);
    if (len < 0.0001f) return;

    float nx = -dy / len * thickness * 0.5f;
    float ny = dx / len * thickness * 0.5f;

    float vertices[] = {
        x1 + nx, y1 + ny,
        x2 + nx, y2 + ny,
        x2 - nx, y2 - ny,
        x1 + nx, y1 + ny,
        x2 - nx, y2 - ny,
        x1 - nx, y1 - ny
    };

    glUseProgram(g_rectRenderer.shaderProgram);
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glUseProgram(0);
}

// Draw filled triangle
void GL_DrawTriangle(SDL_Window* window, float x1, float y1, float x2, float y2, float x3, float y3, const Color& color)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, projMatrix);

    float vertices[] = {x1, y1, x2, y2, x3, y3};

    glUseProgram(g_rectRenderer.shaderProgram);
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);
}

// Draw rectangle with thick border
void GL_DrawRectWithThickBorder(SDL_Window* window, const Rect& rect, const Color& fillColor, const Color& borderColor, float borderThickness)
{
    // Draw filled rectangle first
    GL_DrawFillRect(window, rect, fillColor);
    
    // Draw border on top
    GL_DrawRect(window, rect, borderColor, borderThickness);
}

// Draw rectangle with rounded corners
void GL_DrawRectWithBorderRadius(SDL_Window* window, const Rect& rect, const Color& color, float radius, int segments = 8)
{
    if (!g_rectRenderer.initialized)
    {
        std::cerr << "Rectangle renderer not initialized!" << std::endl;
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    float projMatrix[16];
    CreateOrthoMatrix(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, projMatrix);

    radius = std::min(radius, std::min(rect.w, rect.h) / 2.0f);

    std::vector<float> vertices;
    vertices.reserve(1000);

    // Center rectangle
    float cx = rect.x + rect.w / 2.0f;
    float cy = rect.y + rect.h / 2.0f;

    // Add center triangles (main body)
    float left = rect.x + radius;
    float right = rect.x + rect.w - radius;
    float top = rect.y + radius;
    float bottom = rect.y + rect.h - radius;

    // Center quad
    vertices.insert(vertices.end(), {left, top, right, top, right, bottom});
    vertices.insert(vertices.end(), {left, top, right, bottom, left, bottom});

    // Top rectangle
    vertices.insert(vertices.end(), {left, (float)rect.y, right, (float)rect.y, right, top});
    vertices.insert(vertices.end(), {left, (float)rect.y, right, top, left, top});

    // Bottom rectangle
    vertices.insert(vertices.end(), {left, bottom, right, bottom, right, (float)rect.y + rect.h});
    vertices.insert(vertices.end(), {left, bottom, right, (float)rect.y + rect.h, left, (float)rect.y + rect.h});

    // Left rectangle
    vertices.insert(vertices.end(), {(float)rect.x, top, left, top, left, bottom});
    vertices.insert(vertices.end(), {(float)rect.x, top, left, bottom, (float)rect.x, bottom});

    // Right rectangle
    vertices.insert(vertices.end(), {right, top, (float)rect.x + rect.w, top, (float)rect.x + rect.w, bottom});
    vertices.insert(vertices.end(), {right, top, (float)rect.x + rect.w, bottom, right, bottom});

    // Four corner circles (triangle fans)
    float corners[4][2] = {
        {left, top},           // Top-left
        {right, top},          // Top-right
        {right, bottom},       // Bottom-right
        {left, bottom}         // Bottom-left
    };

    float startAngles[4] = {M_PI, M_PI * 1.5f, 0.0f, M_PI * 0.5f};

    for (int c = 0; c < 4; c++)
    {
        float centerX = corners[c][0];
        float centerY = corners[c][1];
        float startAngle = startAngles[c];

        for (int i = 0; i < segments; i++)
        {
            float angle1 = startAngle + (M_PI * 0.5f) * i / segments;
            float angle2 = startAngle + (M_PI * 0.5f) * (i + 1) / segments;

            vertices.push_back(centerX);
            vertices.push_back(centerY);
            vertices.push_back(centerX + radius * cosf(angle1));
            vertices.push_back(centerY + radius * sinf(angle1));
            vertices.push_back(centerX + radius * cosf(angle2));
            vertices.push_back(centerY + radius * sinf(angle2));
        }
    }

    glUseProgram(g_rectRenderer.shaderProgram);
    glUniformMatrix4fv(g_rectRenderer.projectionLoc, 1, GL_FALSE, projMatrix);
    glUniform4f(g_rectRenderer.colorLoc, color.r / 255.0f, color.g / 255.0f,
                color.b / 255.0f, color.a / 255.0f);

    glBindVertexArray(g_rectRenderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_rectRenderer.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glUseProgram(0);
}

// Cleanup function
void CleanupRectRenderer()
{
    if (g_rectRenderer.initialized)
    {
        glDeleteBuffers(1, &g_rectRenderer.VBO);
        glDeleteVertexArrays(1, &g_rectRenderer.VAO);
        glDeleteProgram(g_rectRenderer.shaderProgram);
        g_rectRenderer.initialized = false;
    }
}
#endif
////// Rect Renderer

PrimitiveGLRenderer::PrimitiveGLRenderer()
{
    init();
}
void PrimitiveGLRenderer::init()
{
   /// InitRectRenderer();
}

void PrimitiveGLRenderer::quit(){}

void PrimitiveGLRenderer::setProjection(const Mat4& projection){}

void PrimitiveGLRenderer::drawPoint(const Point& point, const Color& color, float size)
{
    SDL_Window *window = (SDL_Window *)Application::getApplication()->getWindow()->getNativeWindowFormatBuffer();
    
}
void PrimitiveGLRenderer::drawLine(const Point& start, const Point& end, const Color& color,
              float width )
{
    SDL_Window *window = (SDL_Window *)Application::getApplication()->getWindow()->getNativeWindowFormatBuffer();
    ///GL_DrawLine(window,start.x, start.y, end.x, end.y, color,width);
}
void PrimitiveGLRenderer::drawCircle(const Point& center, float radius, const Color& color,
                int segments, bool filled)
{
    SDL_Window *window = (SDL_Window *)Application::getApplication()->getWindow()->getNativeWindowFormatBuffer();
   /// GL_DrawCircle(window,center.x, center.y, radius,color,2,segments);
}

void PrimitiveGLRenderer::drawRect(const Rect& rect, const Color& color, bool filled)
{
    SDL_Window *window = (SDL_Window *)Application::getApplication()->getWindow()->getNativeWindowFormatBuffer();
   /// GL_DrawRect(window, rect, color);
} // namespace doengine

}