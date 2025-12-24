#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//// g++ ./SDL2O.cpp -lSDL2 -lGL
 
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
//// static PFNGLDRAARRAYSPROC              glDrawArrays;
static PFNGLDELETESHADERPROC            glDeleteShader;

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
    /// LOAD_GL(glDrawArrays)
    LOAD_GL(glDeleteShader)

#undef LOAD_GL
    return true;
}

struct RectRenderer
{
    GLuint vao;
    GLuint vbo;
    GLuint program;
    GLint  uColor;
    GLint  uScreen;
};

void InitRectRenderer(RectRenderer& r)
{
    const char* vs = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        uniform vec2 uScreen;
        void main()
        {
            vec2 ndc = vec2(
                (aPos.x / uScreen.x) * 2.0 - 1.0,
                1.0 - (aPos.y / uScreen.y) * 2.0
            );
            gl_Position = vec4(ndc, 0.0, 1.0);
        }
    )";

    const char* fs = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 uColor;
        void main()
        {
            FragColor = uColor;
        }
    )";

    GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsId, 1, &vs, nullptr);
    glCompileShader(vsId);

    GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsId, 1, &fs, nullptr);
    glCompileShader(fsId);

    r.program = glCreateProgram();
    glAttachShader(r.program, vsId);
    glAttachShader(r.program, fsId);
    glLinkProgram(r.program);

    glDeleteShader(vsId);
    glDeleteShader(fsId);

    glGenVertexArrays(1, &r.vao);
    glGenBuffers(1, &r.vbo);

    glBindVertexArray(r.vao);
    glBindBuffer(GL_ARRAY_BUFFER, r.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    r.uColor  = glGetUniformLocation(r.program, "uColor");
    r.uScreen = glGetUniformLocation(r.program, "uScreen");
}


void BeginRectRender(const RectRenderer& r, int w, int h)
{
    glUseProgram(r.program);
    glBindVertexArray(r.vao);

    glUniform2f(r.uScreen, (float)w, (float)h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void renderFillRect(const RectRenderer& r, SDL_Rect rect, SDL_Color color)
{
    float v[12] = {
        (float)rect.x,                 (float)rect.y,
        (float)(rect.x + rect.w),      (float)rect.y,
        (float)(rect.x + rect.w),      (float)(rect.y + rect.h),
        (float)rect.x,                 (float)rect.y,
        (float)(rect.x + rect.w),      (float)(rect.y + rect.h),
        (float)rect.x,                 (float)(rect.y + rect.h)
    };

    glBindBuffer(GL_ARRAY_BUFFER, r.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v), v);

    glUniform4f(
        r.uColor,
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
    );

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "Minimal Rect Renderer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL
    );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    LoadMinimalGL();

    RectRenderer renderer;
    InitRectRenderer(renderer);

    bool running = true;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = false;

        int w, h;
        SDL_GL_GetDrawableSize(window, &w, &h);
        BeginRectRender(renderer, w, h);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderFillRect(renderer, {50,50,200,100}, {255,0,0,255});
        renderFillRect(renderer, {300,200,150,150}, {0,255,128,200});

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
