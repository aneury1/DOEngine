
#include "Geometric.h"
#include "Sprite.h"
#include "Texture.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/NativeStructsMock.h"
#include "mocks/SDLMock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

namespace doengine
{
namespace ut
{

using testing::_;

class utSprite : public fixture::DoEngineFixture
{
  public:
    utSprite()
        : fixture::DoEngineFixture(),
          _tex("assets/myspritesheet.bmp", &_textureMock), _textureMock(),
          _sut(nullptr)

    {
    }

    void SetUp() override
    {
        fixture::DoEngineFixture::SetUp();
        frames.emplace_back(Rect{0, 0, 4, 4});
        _sut = new Sprite(&_tex, frames, Point{1, 0});
    }

    void TearDown() override
    {
        delete _sut;
    }

    std::vector<Rect> frames;
    Texture _tex;
    testing::NiceMock<mocks::NativeTextureMock> _textureMock;

    Sprite* _sut;
};

TEST_F(utSprite, DISABLED_DrawSeveralSprites)
{
    EXPECT_CALL(_textureMock, Draw(_, _, _, _));
    _sut->Draw(Rect{5, 5});
}

} // namespace ut
} // namespace doengine
