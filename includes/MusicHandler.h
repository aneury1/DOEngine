#pragma once

#include <string>

namespace doengine
{

class MusicHandler
{

  public:
    virtual int addToList(const std::string& src) = 0;
    virtual void playFirst() = 0;
    virtual void playLast() = 0;
    virtual void playIndex(int index) = 0;
    virtual void removeIndex(const int index) = 0;
    virtual void pause(const int) = 0;
    virtual void stop(const int) = 0;
    virtual bool isPlaying(const int) const = 0;
    virtual std::string getPlayMusicName() = 0;
    enum class Repeat
    {
        OnlyThis = -1,
        Once,
        All,
    };

    virtual void setRepeat(Repeat repeat) = 0;
    virtual void setChannel(const int) = 0;
};
} // namespace doengine

#if 0

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        return 1;
    }

    // Load an MP3 file
    Mix_Music* music = Mix_LoadMUS("./nirv-mix-sitw-by-catanius-revival.mp3");
    if (!music) {
        std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
        return 1;
    }

    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) {
        std::cout << "Failed to play music: " << Mix_GetError() << std::endl;
        return 1;
    }


    // Wait until the music finishes playing
    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    // Cleanup and quit
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

#endif
