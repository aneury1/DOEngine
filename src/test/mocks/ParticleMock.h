#pragma once

#include "Particle.h"
#include <gmock/gmock-function-mocker.h>

class ParticleMock : public Particle
{
  public:
    MOCK_METHOD(void, Update, (), (override));
    MOCK_METHOD(void, Draw, (), (override));
};
