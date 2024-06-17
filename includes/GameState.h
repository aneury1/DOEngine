#pragma once
namespace doengine
{
class GameState
{
  public:
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update(float elapsed) = 0;
    virtual void Render() = 0;
};

} // namespace doengine