#pragma once

#include <Empyrion/Common.h>
#include <Empyrion/Time/Duration.h>

namespace emp
{

  struct Particle
  {
    sf::Color Color = sf::Color::White;
    SVector2f Velocity;
    SVector2f TotalForces;
    Duration LifeRemaining;
    Duration TotalLife;
    SVector2f Position;
    float Radius;
  };

}

