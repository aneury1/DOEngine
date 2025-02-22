#pragma once

#include "DOEngine_SDL_includes.h"
#include "MusicHandler.h"
#include <vector>

namespace doengine
{
class SDLSoundHandler : public MusicHandler
{
  public:
    SDLSoundHandler();
    ~SDLSoundHandler();
    virtual int addToList(const std::string& src) override;
    virtual void playFirst() override;
    virtual void playLast() override;
    virtual void playIndex(const int index) override;
    virtual void removeIndex(const int index) override;
    virtual void pause(const int) override;
    virtual void stop(const int) override;
    virtual void setRepeat(Repeat repeat) override;
    virtual void setChannel(const int) override;
    virtual bool isPlaying(const int) const override;

  private:
    void play(Mix_Chunk* chunk);

    std::vector<Mix_Chunk*> sounds;
    int channel;
    Repeat repeatTimes;
    bool isOk;
};
} // namespace doengine
