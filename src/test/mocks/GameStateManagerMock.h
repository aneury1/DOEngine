#pragma once

#include "GameStateManager.h"
#include <gmock/gmock-function-mocker.h>

class GameStateManagerMock : public GameStateManager
{
  public:
    GameStateManagerMock(AbstractWindow* window = nullptr)
        : GameStateManager(window)
    {
    }

    virtual ~GameStateManagerMock()
    {
    }

    MOCK_METHOD(void, AddState, (int, GameState*), (override));
    MOCK_METHOD(void, RemoveState, (int), (override));
    MOCK_METHOD(void, SetState, (int), (override));
    MOCK_METHOD(void, Update, (float), (override));
    MOCK_METHOD(void, Render, (), (override));
};
