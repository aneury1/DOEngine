#pragma once

#include "FPSManager.h"
#include <gmock/gmock.h>

class FpsManagerMock : public FpsManager
{
  public:
    FpsManagerMock() : FpsManager()
    {
    }

    ~FpsManagerMock()
    {
    }

    MOCK_METHOD(void, setFPS, (long fps), (override));
    MOCK_METHOD(void, Start, (), (override));
    MOCK_METHOD(void, Handle, (), (override));
    MOCK_METHOD(float, getElapsedTime, (), (override));
};
