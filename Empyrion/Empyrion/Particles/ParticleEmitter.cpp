#include <Empyrion/Particles/ParticleEmitter.h>
#include <Empyrion/Particles/ParticleSystem.h>

namespace emp
{

  void ParticleEmitter::Play()
  {
    m_TimeStep.Start();
  }

  void ParticleEmitter::Pause()
  {
    m_TimeStep.Pause();
  }

  void ParticleEmitter::Resume()
  {
    m_TimeStep.Resume();
  }

  void ParticleEmitter::Update(ParticleSystem *System)
  {
    m_TimeStep.Update();

    while (m_TimeStep.IsStepUpdateNeeded()) {
      Particle p;
      p.Position = m_PositionDistribution();
      p.Velocity = m_VelocityDistribution();
      p.Radius = m_RadiusDistribution();
      auto life = m_LifetimeDistribution();
      p.TotalLife = life;
      p.LifeRemaining = life;

      System->SpawnParticle(p);
    }
  }

  void ParticleEmitter::SetEmissionRate(const Duration &Dur)
  {
    m_TimeStep.SetStep(Dur);
    m_TimeStep.SetMaximumAccumulation(Duration::Milliseconds(30UL));
  }

  void ParticleEmitter::SetPosition(std::function<SVector2f()> Func)
  {
    m_PositionDistribution = Func;
  }

  void ParticleEmitter::SetVelocity(std::function<SVector2f()> Func)
  {
    m_VelocityDistribution = Func;
  }

  void ParticleEmitter::SetRadius(std::function<float()> Func)
  {
    m_RadiusDistribution = Func;
  }

  void ParticleEmitter::SetLifetime(std::function<emp::Duration()> Func)
  {
    m_LifetimeDistribution = Func;
  }

}
