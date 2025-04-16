#include "Keyboard.h"
#include "SDLKeyboard.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/SDLMock.h"
#include <bitset>
#include <cstddef>
#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>

namespace doengine
{
namespace ut
{
using doengine::devices::Keyboard;
using doengine::devices::Keycode;
using doengine::devices::SDLKeyboard;
using doengine::fixture::DoEngineFixture;
using namespace testing;

class utSDLKeyboard : public DoEngineFixture
{
  public:
    utSDLKeyboard() : DoEngineFixture(), _sut()
    {
        memset(_sdlKeys, 0u, Keyboard::BUTTONS_COUNT);
    }

    void SetUp() override
    {
        DoEngineFixture::SetUp();

        _sdlKeys[SDL_SCANCODE_A] = 1;
        _sdlKeys[SDL_SCANCODE_0] = 1;
        _sdlKeys[SDL_SCANCODE_KP_1] = 1;
        ON_CALL(_sdlMock, SDL_GetKeyboardState(_))
            .WillByDefault(Return(_sdlKeys));
    }
    Uint8 _sdlKeys[Keyboard::BUTTONS_COUNT];
    SDLKeyboard _sut;
};

TEST_F(utSDLKeyboard, getKeyboardBitmapTest)
{
    const unsigned char* result = _sut.getKeysBitset();
    ASSERT_TRUE(result[static_cast<std::size_t>(Keycode::KeyA)]);
    ASSERT_TRUE(result[static_cast<std::size_t>(Keycode::Key0)]);
    ASSERT_TRUE(result[static_cast<std::size_t>(Keycode::KeyKp1)]);
}

} // namespace ut
} // namespace doengine