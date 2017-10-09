#pragma once

#include <Empyrion/Time/TimeExtent.h>
#include <Empyrion/Particles/ParticleEmitter.h>
#include <Empyrion/Particles/ParticleAffector.h>

namespace emp
{

  class ParticleSystem
  {
  public:
    ParticleSystem(std::size_t MaxParticles = 10000, sf::Texture *PTexture = nullptr);
    void AddAffector(const ParticleAffector &Paff, Duration dur = Duration::Milliseconds(1000000UL));
    void AddEmitter(const ParticleEmitter &Emit);
    void Update();
    void Render(sf::RenderTarget &Target);
    void SpawnParticle(const Particle &P);
    void SetParticleTexture(sf::Texture *Texture);

  private:

    void KillParticle(size_t Index);
    void UpdateParticles();
    
    sf::RenderStates m_RenderState;

    TimeStep m_Stepper;
    std::vector<ParticleAffector> m_Affectors;
    std::vector<ParticleEmitter> m_Emitters;

    std::size_t m_LiveCount = 0;
    std::vector<Particle> m_Particles;
    sf::VertexArray m_DrawParticles;

  };

}
