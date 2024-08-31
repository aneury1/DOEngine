#pragma once
#include "Window.h"
#include <SDL2/SDL.h>
namespace doengine
{
void DrawRect(SDL_Renderer* render, SDL_Rect rect);
void DrawRect(Window* window, SDL_Rect rect);

} // namespace doengine