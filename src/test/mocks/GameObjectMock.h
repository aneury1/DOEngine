#pragma once
#include "GameObject.h"
#include <gmock/gmock-function-mocker.h>

namespace doengine::mocks
{

class GameObjectMock : public GameObject
{
  public:
    GameObjectMock(AbstractWindow* window = nullptr) : GameObject(window)
    {
    }

    MOCK_METHOD(void, Update, (float timer), (override));
    MOCK_METHOD(void, Render, (), (override));
};

} // namespace doengine::mocks