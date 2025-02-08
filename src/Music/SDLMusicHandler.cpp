#include "SDLMusicHandler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace doengine::devices
{

constexpr int FRECUENCY = 44100;
constexpr int CHANNEL = 2;
constexpr int CHUNK_SIZE = 2048;

SDLMusicHandler::SDLMusicHandler()
    : musics(), repeatTimes(Repeat::Once), isPlayingSound(false), isOk(false)
{
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0)
    {
        isOk = SDL_Init(SDL_INIT_AUDIO) == 0;
    }
    else
    {
        isOk = true;
    }

    if (!isOk)
    {
        SDL_Log("SDL Audio failed to Init: %s", SDL_GetError());
    }
    else
    {
        isOk = Mix_OpenAudio(FRECUENCY, MIX_DEFAULT_FORMAT, CHANNEL,
                             CHUNK_SIZE) == 0;

        if (!isOk)
        {
            SDL_Log("SDL Mixer failed to OpenAudio: %s", Mix_GetError());
        }
    }
}

SDLMusicHandler::~SDLMusicHandler()
{
    if (isOk)
    {
        for (auto it = musics.begin(); it != musics.end(); it++)
        {
            Mix_FreeMusic(*it);
        }
        musics.clear();
        Mix_CloseAudio();
    }
}

int SDLMusicHandler::addToList(const std::string& src)
{
    if (isOk)
    {
        Mix_Music* music = Mix_LoadMUS(src.c_str());
        if (music == nullptr)
        {
            SDL_Log("SDL Mixer failed to Load music: %s", Mix_GetError());
        }
        else
        {
            SDL_Log("Adding %s", src.c_str());
            musics.push_back(music);
        }
    }
    return 0;
}

void SDLMusicHandler::playFirst()
{
    if (isOk)
    {
        if (Mix_PlayMusic(musics.front(), static_cast<int>(repeatTimes)) == -1)
        {
            SDL_Log("Failed to play music: %s", Mix_GetError());
        }
    }
}

void SDLMusicHandler::playLast()
{
    if (isOk)
    {
        if (Mix_PlayMusic(musics.back(), -1) == -1)
        {
            SDL_Log("Failed to play music: %s", Mix_GetError());
        }
    }
}

void SDLMusicHandler::PlayIndex(const int index)
{
    if (isOk && (index < musics.size()))
    {
        if (Mix_PlayMusic(musics.at(index), -1) == -1)
        {
            SDL_Log("Failed to play music: %s", Mix_GetError());
        }
    }
}

void SDLMusicHandler::removeIndex(const int index)
{
    musics.erase(musics.begin() + index);
}

void SDLMusicHandler::pause(const int)
{
    if (isPlaying(0))
    {
        Mix_PauseMusic();
    }
}

void SDLMusicHandler::stop(const int)
{
    Mix_HaltMusic();
}

bool SDLMusicHandler::isPlaying(const int) const
{
    return Mix_PlayingMusic();
}

void SDLMusicHandler::setRepeat(Repeat repeat)
{
    repeatTimes = repeat;
}

} // namespace doengine::devices
