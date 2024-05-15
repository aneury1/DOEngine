#pragma once

#include "MusicHandler.h"
#include <gmock/gmock-function-mocker.h>
#include <string>


class MusicHandlerMock : public MusicHandler
{
  public:
    MOCK_METHOD(void, addToList, (std::string), (override));
    MOCK_METHOD(void, playFirst, (), (override));
    MOCK_METHOD(void, playLast, (), (override));
    MOCK_METHOD(void, PlayIndex, (int), (override));
    MOCK_METHOD(void, removeIndex, (int), (override));
    MOCK_METHOD(std::string, getPlayMusicName, (), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, setRepeat, (Repeat), (override));
};
