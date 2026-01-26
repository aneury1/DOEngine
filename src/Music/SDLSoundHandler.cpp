#include "SDLSoundHandler.h"

namespace doengine
{

constexpr int FRECUENCY = 44100;
constexpr int CHANNEL = 2;
constexpr int CHUNK_SIZE = 2048;

SDLSoundHandler::SDLSoundHandler()
    : sounds(), channel(-1), repeatTimes(Repeat::Once), isOk(false)
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

SDLSoundHandler::~SDLSoundHandler()
{
    if (isOk)
    {
        stop(-1); // Stops all channels
        for (auto it = sounds.begin(); it != sounds.end(); it++)
        {
            Mix_FreeChunk(*it);
        }
        sounds.clear();
        Mix_CloseAudio();
    }
}

int SDLSoundHandler::addToList(const std::string& src)
{
    if (isOk)
    {
        Mix_Chunk* music = Mix_LoadWAV(src.c_str());
        if (music == nullptr)
        {
            SDL_Log("SDL Mixer failed to Load music: %s", Mix_GetError());
        }
        else
        {
            SDL_Log("Adding %s", src.c_str());
            sounds.push_back(music);
            return sounds.size() - 1;
        }
    }
    return -1;
}

void SDLSoundHandler::playFirst()
{
    if (isOk)
    {
        play(sounds.front());
    }
}

void SDLSoundHandler::playLast()
{
    if (isOk)
    {
        play(sounds.back());
    }
}

void SDLSoundHandler::playIndex(const int index)
{
    if (isOk && (index < sounds.size()))
    {
        play(sounds.at(index));
    }
}

void SDLSoundHandler::removeIndex(const int index)
{
    sounds.erase(sounds.begin() + index);
}

void SDLSoundHandler::pause(const int index)
{
    if (isPlaying(index))
    {
        Mix_Pause(index);
    }
}

void SDLSoundHandler::stop(const int index)
{
    Mix_HaltChannel(index);
}

bool SDLSoundHandler::isPlaying(const int index) const
{
    return Mix_Playing(index);
}

void SDLSoundHandler::setRepeat(Repeat repeat)
{
    repeatTimes = repeat;
}

void SDLSoundHandler::setChannel(const int ch)
{
    channel = ch;
}

void SDLSoundHandler::play(Mix_Chunk* chunk)
{
    if (Mix_PlayChannel(channel, chunk, static_cast<int>(repeatTimes)) == -1)
    {
        SDL_Log("Failed to play music: %s", Mix_GetError());
    }
}

} // namespace doengine
