#pragma once
#include "Application.h"
#include "Geometric.h"

#include <string>

class GameObject
{
  public:
    GameObject(){}
    virtual ~GameObject(){}
    virtual void Update(float timer = 0) = 0;
    virtual void Render() = 0;
    virtual bool collideWith(const Rect &rect) = 0;
    virtual bool collideWith(const Object &object) = 0;
};