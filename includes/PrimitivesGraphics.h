#pragma once
#include "Window.h"
#include "DOEngine_SDL_includes.h"
namespace doengine
{
void DrawRect(SDL_Renderer* render, SDL_Rect rect);
void DrawRect(Window* window, SDL_Rect rect);

} // namespace doengine