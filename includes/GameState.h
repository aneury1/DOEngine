#pragma once
#include <variant>
#include <string>

#include "GameObject.h"
namespace doengine
{



typedef std::variant<int, std::string, GameObject *> ArgValue;

class GameState
{
  public:
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update(float elapsed) = 0;
    virtual void Render() = 0;
};

} // namespace doengine