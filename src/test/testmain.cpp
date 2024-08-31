#include "FPSManager.h"
#include "GameStateManager.h"
///#include "mocks/WindowManagerMock.h"
#include "mocks/CameraMock.h"
#include "mocks/EventHandlerMock.h"
#include "mocks/FPSManagerMock.h"

#include "mocks/GameObjectMock.h"
#include "mocks/GameStateManagerMock.h"
#include "mocks/MusicHandlerMock.h"
#include "mocks/ParticleMock.h"
#include "mocks/RendererMock.h"
#include "mocks/SDLMock.h"
#include "mocks/UDPPacketMock.h"
#include <gmock/gmock-actions.h>
#include <gmock/gmock-nice-strict.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

using namespace doengine::mocks;
using namespace testing;

TEST(mocks_test, DISABLED_getMusicFromMarsTest)
{
    NiceMock<CameraMock> cameraMock;
    NiceMock<MusicHandlerMock> musicHandlerMock;
    NiceMock<ParticleMock> particleMock;
    NiceMock<RendererMock> rendererMock;
    ////NiceMock<FontMock> fontMock;
    NiceMock<KeyDownEventMock> keyDownEventMock;
    NiceMock<KeyUpEventMock> keyUpEventMock;
    /// NiceMock<WindowManagerMock> WindowManagerMock;
    NiceMock<GameObjectMock> gameObjectMock;
    NiceMock<UDPPacketMock> udpPacketMock;

    ON_CALL(musicHandlerMock, getPlayMusicName()).WillByDefault(Return("Mars"));
    ASSERT_EQ(1, 1);
    EXPECT_EQ(musicHandlerMock.getPlayMusicName(), "Mars");

    // ON_CALL(sdlMock, SDL_GetTicks()).WillByDefault(Return(1500U));
    // EXPECT_EQ(SDL_GetTicks(), 1500U);
    // testing::Mock::AllowLeak(&sdlMock);
}
