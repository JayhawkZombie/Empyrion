#pragma once

#include <Empyrion/Particles/Particle.h>
#include <functional>

namespace emp
{

  class ParticleAffector
  {
  public:
    ParticleAffector(std::function<void(Particle &p)> Func);
    void operator()(Particle &P);

  private:

    std::function<void(Particle &)> m_PFunc = [](Particle &P) { P; };

  };

  extern ParticleAffector ColorAffector(const sf::Color &StartColor, const sf::Color &EndColor);
  extern ParticleAffector FadeAffector(const float &StartPerc);
  extern ParticleAffector ForceAffector(const SVector2f &Dir, float Mag);
  extern ParticleAffector AttractionAffector(const SVector2f &Pos, float mag, float cutoffRad);
  extern ParticleAffector RepulsionAffector(const SVector2f &Pos, float mag, float cutoffRad);

}
