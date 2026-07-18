#pragma once

#include "GameStateManager.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine::mocks
{

class GameStateManagerMock : public GameStateManager
{
  public:
    GameStateManagerMock(std::shared_ptr<WindowManager> window = nullptr)
        : GameStateManager(window)
    {
    }

    virtual ~GameStateManagerMock()
    {
    }

    MOCK_METHOD(void, AddState, (int, std::shared_ptr<GameState>), (override));
    MOCK_METHOD(void, RemoveState, (int), (override));
    MOCK_METHOD(void, SetState, (int), (override));
    MOCK_METHOD(void, Update, (float), (override));
    MOCK_METHOD(void, Render, (), (override));
};

} // namespace doengine::mocks
