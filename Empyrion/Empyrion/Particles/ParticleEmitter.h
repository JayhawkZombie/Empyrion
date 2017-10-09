#pragma once

#include <Empyrion/Particles/Particle.h>
#include <Empyrion/Time/TimeStep.h>
#include <functional>

namespace emp
{

  class ParticleSystem;
  
  class ParticleEmitter
  {
  public:
    ParticleEmitter() = default;
    ~ParticleEmitter() = default;

    void Play();
    void Pause();
    void Resume();
    void Update(ParticleSystem *System);

    void SetEmissionRate(const Duration &Dur);
    void SetPosition(std::function<SVector2f()> Func);
    void SetVelocity(std::function<SVector2f()> Func);
    void SetRadius(std::function<float()> Func);
    void SetLifetime(std::function<emp::Duration()>);

  private:

    TimeStep m_TimeStep;

    std::function<SVector2f()> m_PositionDistribution = []() { return SVector2f(0.f, 0.f); };
    std::function<SVector2f()> m_VelocityDistribution = []() { return SVector2f(0.f, 0.f); };
    std::function<float()> m_RadiusDistribution = []() { return 0.f; };
    std::function<emp::Duration()> m_LifetimeDistribution = []() { return Duration::Milliseconds(2000UL); };

    Duration m_PLife;
  };

}
