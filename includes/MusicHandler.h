#pragma once

#include <string>

namespace doengine
{

class MusicHandler
{

    //   AbstractWindow *window;

  public:
    //   MusicHandler(AbstractWindow *window);

    virtual void addToList(std::string src) = 0;
    virtual void playFirst() = 0;
    virtual void playLast() = 0;
    virtual void PlayIndex(int index) = 0;
    virtual void removeIndex(int index) = 0;
    virtual std::string getPlayMusicName() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    enum class Repeat
    {
        OnlyThis,
        All,
        None,
    };

    virtual void setRepeat(Repeat repeat) = 0;
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