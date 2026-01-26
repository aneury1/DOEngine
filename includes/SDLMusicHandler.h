#pragma once

#include "DOEngine_SDL_includes.h"
#include "MusicHandler.h"
#include <vector>

namespace doengine
{
class SDLMusicHandler : public MusicHandler
{
  public:
    SDLMusicHandler();
    ~SDLMusicHandler();
    virtual int addToList(const std::string& src) override;
    virtual void playFirst() override;
    virtual void playLast() override;
    virtual void playIndex(const int index) override;
    virtual void removeIndex(const int index) override;
    virtual void pause(const int) override;
    virtual void stop(const int) override;
    virtual void setRepeat(Repeat repeat) override;
    virtual bool isPlaying(const int) const override;
    virtual std::string getPlayMusicName() override;
    bool setPosition(const double pos);
    int setVolume(const int newVol);
    double getMusicDuration(const unsigned int index) const;
    double getMusicPosition(const unsigned int index) const;
    

  private:
    virtual void setChannel(const int) override {};
    void play(Mix_Music*);
    std::vector<Mix_Music*> musics;

    Repeat repeatTimes;

    bool isPlayingSound;
    bool isOk;
};
} // namespace doengine
