#pragma once
#include "GameObject.h"
#include <gmock/gmock-function-mocker.h>


class GameObjectMock : public GameObject
{
  public:
    GameObjectMock(AbstractWindow* window = nullptr) : GameObject(window)
    {
    }

    MOCK_METHOD(void, Update, (float timer), (override));
    MOCK_METHOD(void, Render, (), (override));
};
