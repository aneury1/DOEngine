#include "GameState.h"
#include "GameStateManager.h"
#include "fixtures/DoEngineFixture.h"
#include "mocks/GameStateMock.h"
#include <cstddef>

class utGameStateManager : public ::testing::Test
{
  public:
    utGameStateManager() : _sut(nullptr), _gsId(0xCAFEBABE)
    {
    }

    void SetUp() override
    {
        ::testing::Test::SetUp();

        const int gsId = 0xCAFEBABE;
        _sut.AddState(_gsId, &_gsMock);
    }

    testing::NiceMock<GameStateMock> _gsMock;
    GameStateManager _sut;

    const int _gsId;
};

TEST_F(utGameStateManager, doengineSetStateShouldNotCallOnExitFirstTime)
{
    EXPECT_CALL(_gsMock, OnExit()).Times(0);
    EXPECT_CALL(_gsMock, OnEnter());

    _sut.SetState(_gsId);
}

TEST_F(utGameStateManager, doengineSetStateShouldCallOnEnterOnExitSameState)
{
    EXPECT_CALL(_gsMock, OnExit());
    EXPECT_CALL(_gsMock, OnEnter()).Times(2);

    _sut.SetState(_gsId);
    _sut.SetState(_gsId);
}

TEST_F(utGameStateManager, doengineSetStateShouldCallOnEnterOnExitChangeState)
{
    const int gsId = 0xDEADBEEF;
    testing::NiceMock<GameStateMock> anotherGsMock;
    _sut.AddState(gsId, &anotherGsMock);

    EXPECT_CALL(_gsMock, OnExit());
    EXPECT_CALL(_gsMock, OnEnter());

    EXPECT_CALL(anotherGsMock, OnExit()).Times(0);
    EXPECT_CALL(anotherGsMock, OnEnter());

    _sut.SetState(_gsId);
    _sut.SetState(gsId);
}

TEST_F(utGameStateManager, doengineUpdateStateShouldCallUpdate)
{
    float elapsed = 10234.0f;
    EXPECT_CALL(_gsMock, Update(elapsed));

    _sut.SetState(_gsId);
    _sut.Update(elapsed);
}

TEST_F(utGameStateManager, DISABLED_doengineRemoveState)
{
    const int gsId = 0xDEADBEEF;

    // EXCEPT_EQ(_sut.GetStateId(), gsId);
    _sut.AddState(gsId, &_gsMock);

    // EXCEPT_NE(_sut.GetStateId(), gsId);
    _sut.RemoveState(gsId);
}

TEST_F(utGameStateManager, doengineRender)
{
    float elapsed = 10234.0f;
    EXPECT_CALL(_gsMock, Render());

    _sut.SetState(_gsId);
    _sut.Render();
}
