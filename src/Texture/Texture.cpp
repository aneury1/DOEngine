#include "DOEngine.h"

std::map<std::string, SDL_Texture*> Texture::textures;
SDL_Renderer* Texture::render;

bool Texture::IsloadThisTexture(std::string id)
{
    if (id.length() > 0)
        return textures[id] != NULL;
    return false;
}

int Texture::LoadTexture(std::string path, std::string id)
{
    if (path.length() > 0 && id.length() > 0)
    {
        if (IsloadThisTexture(id) == true)
            return 2;

        SDL_Surface* surface = IMG_Load(path.c_str());

        if (surface != NULL)
        {
            textures[id] = SDL_CreateTextureFromSurface(render, surface);
        }
    }
    return -1;
}

void Texture::DrawImage(std::string id, int x, int y, int w, int h)
{
    if (IsloadThisTexture(id))
    {
        SDL_Rect offset = {x, y, w, h};
        SDL_Rect clipset = {0, 0, 0, 0};
        SDL_RenderCopy(render, textures[id], NULL, &offset);
    }
}
bool saveScreenshotBMP(std::string filepath)
{
    SDL_Window* SDLWindow = Application::getApplication()->getWindow();
    SDL_Renderer* SDLRenderer =
        static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer());
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL)
    {
        std::cerr << "Failed to create info surface from window in "
                     "saveScreenshotBMP(string), SDL_GetError() - "
                  << SDL_GetError() << "\n";
    }
    else
    {
        unsigned char* pixels = new (
            std::nothrow) unsigned char[infoSurface->w * infoSurface->h *
                                        infoSurface->format->BytesPerPixel];
        if (pixels == 0)
        {
            std::cerr << "Unable to allocate memory for screenshot pixel data "
                         "buffer!\n";
            return false;
        }
        else
        {
            if (SDL_RenderReadPixels(
                    SDLRenderer, &infoSurface->clip_rect,
                    infoSurface->format->format, pixels,
                    infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
            {
                std::cerr << "Failed to read pixel data from SDL_Renderer "
                             "object. SDL_GetError() - "
                          << SDL_GetError() << "\n";
                delete[] pixels;
                return false;
            }
            else
            {
                saveSurface = SDL_CreateRGBSurfaceFrom(
                    pixels, infoSurface->w, infoSurface->h,
                    infoSurface->format->BitsPerPixel,
                    infoSurface->w * infoSurface->format->BytesPerPixel,
                    infoSurface->format->Rmask, infoSurface->format->Gmask,
                    infoSurface->format->Bmask, infoSurface->format->Amask);
                if (saveSurface == NULL)
                {
                    std::cerr << "Couldn't create SDL_Surface from renderer "
                                 "pixel data. SDL_GetError() - "
                              << SDL_GetError() << "\n";
                    delete[] pixels;
                    return false;
                }
                std::stringstream ss;
                ss << filepath << "-" << SDL_GetTicks() << ".bmp";
                /// SDL_Log("%s", saveSurface, ss.str().c_str());
                SDL_SaveBMP(saveSurface, ss.str().c_str());
                SDL_FreeSurface(saveSurface);
                saveSurface = NULL;
            }
            delete[] pixels;
        }
        SDL_FreeSurface(infoSurface);
        infoSurface = NULL;
    }
    return true;
}

void Texture::setRender(SDL_Renderer* render)
{
    if (render)
    {
        Texture::render = render;
    }
    SDL_Log("SetRender Called.");
}

void Texture::setRender(doengine::gfx::Renderer* render)
{
    if (render->isRenderOk())
    {
        Texture::render =
            static_cast<SDL_Renderer*>(render->getNativeRenderer());
    }
    SDL_Log("SetRender Called.");
}