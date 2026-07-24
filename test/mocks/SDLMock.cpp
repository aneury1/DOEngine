#include "SDLMock.h"

using namespace doengine::mocks;

SDLMock* sdlMock = nullptr;

void SetSDLMock(SDLMock* newSdlMock)
{
    sdlMock = newSdlMock;
}

int SDL_Init(Uint32 flags)
{
    return sdlMock->SDL_Init(flags);
}

SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h,
                             Uint32 flags)
{
    return sdlMock->SDL_CreateWindow(title, x, y, w, h, flags);
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags)
{
    return sdlMock->SDL_CreateRenderer(window, index, flags);
}

int SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b,
                           Uint8 a)
{
    return sdlMock->SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDL_RenderPresent(SDL_Renderer* renderer)
{
    sdlMock->SDL_RenderPresent(renderer);
}

int SDL_RenderClear(SDL_Renderer* renderer)
{
    return sdlMock->SDL_RenderClear(renderer);
}

int SDL_SetWindowFullscreen(SDL_Window* window, Uint32 flags)
{
    return sdlMock->SDL_SetWindowFullscreen(window, flags);
}

void SDL_SetWindowSize(SDL_Window* window, int w, int h)
{
}

Uint32 SDL_GetTicks()
{
    return sdlMock->SDL_GetTicks();
}

void SDL_Delay(Uint32 a)
{
    sdlMock->SDL_Delay(a);
}

void SDL_Log(const char* fmt, ...)
{
    sdlMock->SDL_Log(nullptr);
}

int SDL_PollEvent(SDL_Event* event)
{
    return sdlMock->SDL_PollEvent_REAL(event);
}

Uint32 SDL_GetMouseState(int* x, int* y)
{
    return sdlMock->SDL_GetMouseState_REAL(x, y);
}

const Uint8* SDL_GetKeyboardState(int* numkeys)
{
    return sdlMock->SDL_GetKeyboardState(numkeys);
}

SDL_JoystickID SDL_JoystickGetDeviceInstanceID(int index)
{
    return sdlMock->SDL_JoystickGetDeviceInstanceID(index);
}

SDL_JoystickID SDL_JoystickInstanceID(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickInstanceID(joystick);
}

SDL_bool SDL_JoystickHasLED(SDL_Joystick* Joystick)
{
    return sdlMock->SDL_JoystickHasLED(Joystick);
}

SDL_bool SDL_JoystickHasRumble(SDL_Joystick* Joystick)
{
    return sdlMock->SDL_JoystickHasRumble(Joystick);
}

int SDL_JoystickGetPlayerIndex(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickGetPlayerIndex(joystick);
}

Sint16 SDL_JoystickGetAxis(SDL_Joystick* joystick, int axis)
{
    return sdlMock->SDL_JoystickGetAxis(joystick, axis);
}

Uint8 SDL_JoystickGetButton(SDL_Joystick* joystick, int button)
{
    return sdlMock->SDL_JoystickGetButton(joystick, button);
}

int SDL_JoystickNumAxes(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickNumAxes(joystick);
}

int SDL_JoystickNumButtons(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickNumButtons(joystick);
}

SDL_JoystickPowerLevel SDL_JoystickCurrentPowerLevel(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickCurrentPowerLevel(joystick);
}

int SDL_JoystickRumble(SDL_Joystick* joystick, Uint16 left, Uint16 right,
                       Uint32 duration_ms)
{
    return sdlMock->SDL_JoystickRumble(joystick, left, right, duration_ms);
}

void SDL_JoystickSetPlayerIndex(SDL_Joystick* joystick, int player_index)
{
    sdlMock->SDL_JoystickSetPlayerIndex(joystick, player_index);
}

int SDL_JoystickSetLED(SDL_Joystick* joystick, Uint8 red, Uint8 green,
                       Uint8 blue)
{
    return sdlMock->SDL_JoystickSetLED(joystick, red, green, blue);
}

const char* SDL_JoystickNameForIndex(int device_index)
{
    return sdlMock->SDL_JoystickNameForIndex(device_index);
}

const char* SDL_JoystickName(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickName(joystick);
}

SDL_Joystick* SDL_JoystickOpen(int device_index)
{
    return sdlMock->SDL_JoystickOpen_REAL(device_index);
}

void SDL_JoystickClose(SDL_Joystick* joystick)
{
    return sdlMock->SDL_JoystickClose_REAL(joystick);
}

const char* SDL_GetError(void)
{
    return sdlMock->SDL_GetError_REAL();
}

int SDL_RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture,
                     const SDL_Rect* srcrect, const SDL_Rect* dstrect,
                     const double angle, const SDL_Point* center,
                     const SDL_RendererFlip flip)
{
    return sdlMock->SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle,
                                     center, flip);
}

int SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                   const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
    return sdlMock->SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode* mode)
{
    return sdlMock->SDL_GetCurrentDisplayMode(displayIndex, mode);
}

void SDL_DestroyRenderer(SDL_Renderer* renderer)
{
    sdlMock->SDL_DestroyRenderer(renderer);
}

int SDL_RenderDrawPoint(SDL_Renderer* renderer, int x, int y)
{
    return sdlMock->SDL_RenderDrawPoint(renderer, x, y);
}

int SDL_RenderDrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2)
{
    return sdlMock->SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

int SDL_RenderDrawRect(SDL_Renderer* renderer, const SDL_Rect* rect)
{
    return sdlMock->SDL_RenderDrawRect(renderer, rect);
}

int SDL_RenderFillRect(SDL_Renderer* renderer, const SDL_Rect* rect)
{
    return sdlMock->SDL_RenderFillRect(renderer, rect);
}

SDL_RWops* SDL_RWFromFile(const char* file, const char* mode)
{
    return sdlMock->SDL_RWFromFile(file, mode);
}

SDL_Surface* SDL_LoadBMP_RW(SDL_RWops* src, int freesrc)
{
    return sdlMock->SDL_LoadBMP_RW(src, freesrc);
}

SDL_Surface* SDL_ConvertSurface(SDL_Surface* src, const SDL_PixelFormat* fmt,
                                Uint32 flags)
{
    return sdlMock->SDL_ConvertSurface(src, fmt, flags);
}

int SDL_GetTextureColorMod(SDL_Texture* texture, Uint8* r, Uint8* g, Uint8* b)
{
    return sdlMock->SDL_GetTextureColorMod(texture, r, g, b);
}

SDL_Texture* SDL_CreateTexture(SDL_Renderer* renderer, Uint32 format,
                               int access, int w, int h)
{
    return sdlMock->SDL_CreateTexture(renderer, format, access, w, h);
}

int SDL_SetRenderTarget(SDL_Renderer* renderer, SDL_Texture* texture)
{
    return sdlMock->SDL_SetRenderTarget(renderer, texture);
}

/****** SDL_TTF *********/

int TTF_Init(void)
{
    return sdlMock->TTF_Init();
}

int TTF_SetFontSize(TTF_Font* font, int ptsize)
{
    return sdlMock->TTF_SetFontSize(font, ptsize);
}

void TTF_CloseFont(TTF_Font* font)
{
    sdlMock->TTF_CloseFont(font);
}

TTF_Font* TTF_OpenFont(const char* file, int ptsize)
{
    return sdlMock->TTF_OpenFont(file, ptsize);
}

SDL_Surface* TTF_RenderText_Shaded(TTF_Font* font, const char* text,
                                   SDL_Color fg, SDL_Color bg)
{
    return sdlMock->TTF_RenderText_Shaded(font, text, fg, bg);
}

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer,
                                          SDL_Surface* surface)
{
    return sdlMock->SDL_CreateTextureFromSurface(renderer, surface);
}

int SDL_QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w,
                     int* h)
{
    return sdlMock->SDL_QueryTexture(texture, format, access, w, h);
}

void SDL_DestroyTexture(SDL_Texture* texture)
{
    sdlMock->SDL_DestroyTexture(texture);
}

void SDL_FreeSurface(SDL_Surface* surface)
{
    sdlMock->SDL_FreeSurface(surface);
}

int TTF_SizeText(TTF_Font* font, const char* text, int* w, int* h)
{
    return sdlMock->TTF_SizeText(font, text, w, h);
}

Uint64 SDL_GetPerformanceCounter()
{
    return sdlMock->SDL_GetPerformanceCounter();
}

Uint64 SDL_GetPerformanceFrequency()
{
    return sdlMock->SDL_GetPerformanceFrequency();
}

int SDL_SetTextureBlendMode(SDL_Texture* tex, SDL_BlendMode blendMode)
{
    return sdlMock->SDL_SetTextureBlendMode(tex, blendMode);
}

int SDL_GetTextureBlendMode(SDL_Texture* tex, SDL_BlendMode* blendMode)
{
    return sdlMock->SDL_GetTextureBlendMode(tex, blendMode);
}

int SDL_GetTextureAlphaMod(SDL_Texture* a, Uint8* b)
{
    return sdlMock->SDL_GetTextureAlphaMod(a, b);
}

int SDL_SetTextureColorMod(SDL_Texture* a, Uint8 b, Uint8 c, Uint8 d)
{
    return sdlMock->SDL_SetTextureColorMod(a, b, c, d);
}

int SDL_SetTextureAlphaMod(SDL_Texture* a, Uint8 b)
{
    return sdlMock->SDL_SetTextureAlphaMod(a, b);
}

Uint32 SDL_MapRGB(const SDL_PixelFormat* a, Uint8 b, Uint8 c, Uint8 d)
{
    return sdlMock->SDL_MapRGB(a, b, c, d);
}

Uint32 SDL_MapRGBA(const SDL_PixelFormat* a, Uint8 b, Uint8 c, Uint8 d, Uint8 e)
{
    return sdlMock->SDL_MapRGBA(a, b, c, d, e);
}

int SDL_SetColorKey(SDL_Surface* a, int b, Uint32 c)
{
    return sdlMock->SDL_SetColorKey(a, b, c);
}

int SDL_RenderReadPixels(SDL_Renderer* a, const SDL_Rect* b, Uint32 c, void* d,
                         int e)
{
    return sdlMock->SDL_RenderReadPixels(a, b, c, d, e);
}

int SDL_UpdateTexture(SDL_Texture* a, const SDL_Rect* b, const void* c, int d)
{
    return sdlMock->SDL_UpdateTexture(a, b, c, d);
}

SDL_PixelFormat* SDL_AllocFormat(Uint32 a)
{
    return sdlMock->SDL_AllocFormat(a);
}

void SDL_FreeFormat(SDL_PixelFormat* a)
{
    return sdlMock->SDL_FreeFormat(a);
}

int IMG_Init(int flag)
{
    return sdlMock->IMG_Init(flag);
}
void IMG_Quit()
{
    sdlMock->IMG_Quit();
}

SDL_Surface* IMG_Load(const char* path)
{
    return sdlMock->IMG_Load(path);
}

void SDL_StartTextInput()
{
    sdlMock->SDL_StartTextInput();
}

int SDL_GetDisplayUsableBounds(int a, SDL_Rect* b)
{
    return sdlMock->SDL_GetDisplayUsableBounds(a, b);
}

int SDL_RenderSetClipRect(SDL_Renderer* a, const SDL_Rect* b)
{
    return sdlMock->SDL_RenderSetClipRect(a, b);
}

SDL_Surface* TTF_RenderGlyph_Blended(TTF_Font* font, Uint16 ch, SDL_Color fg)
{
    return sdlMock->TTF_RenderGlyph_Blended(font, ch, fg);
}

int TTF_FontHeight(const TTF_Font* font)
{
    return sdlMock->TTF_FontHeight(font);
}

SDL_Surface* SDL_CreateRGBSurfaceWithFormat(Uint32 a, int b, int c, int d,
                                            Uint32 e)
{
    return sdlMock->SDL_CreateRGBSurfaceWithFormat(a, b, c, d, e);
}

int SDL_FillRect(SDL_Surface* a, const SDL_Rect* b, Uint32 c)
{
    return sdlMock->SDL_FillRect(a, b, c);
}

int SDL_UpperBlit(SDL_Surface* a, const SDL_Rect* b, SDL_Surface* c,
                  SDL_Rect* d)
{
    return sdlMock->SDL_UpperBlit(a, b, c, d);
}

int TTF_GlyphMetrics(TTF_Font* font, Uint16 ch, int* minx, int* maxx, int* miny,
                     int* maxy, int* advance)
{
    return sdlMock->TTF_GlyphMetrics(font, ch, minx, maxx, miny, maxy, advance);
}

int TTF_SizeUTF8(TTF_Font* font, const char* text, int* w, int* h)
{
    return sdlMock->TTF_SizeUTF8(font, text, w, h);
}

SDL_Surface* TTF_RenderUTF8_Blended(TTF_Font* font, const char* text,
                                    SDL_Color fg)
{
    return sdlMock->TTF_RenderUTF8_Blended(font, text, fg);
}

SDL_Window* SDL_RenderGetWindow(SDL_Renderer* a)
{
    return sdlMock->SDL_RenderGetWindow(a);
}

SDL_Texture* SDL_GetRenderTarget(SDL_Renderer* a)
{
    return sdlMock->SDL_GetRenderTarget(a);
}

void SDL_LogError(SDL_LogCategory a, const char* b)
{
    sdlMock->SDL_LogError(a, b);
}

void SDL_LogError(SDL_LogCategory a, const char* b, const char* c)
{
    sdlMock->SDL_LogError(a, b, c);
}