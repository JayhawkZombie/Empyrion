#include <Empyrion/Particles/ParticleSystem.h>

namespace emp
{

  ParticleSystem::ParticleSystem(std::size_t MaxParticles /*= 10000*/, sf::Texture *PTexture /*= nullptr*/)
  {
    m_RenderState.blendMode = sf::BlendAdd;
    
    m_Stepper.SetStep(Duration::Milliseconds(milliseconds_double(13.337)));
    m_Stepper.SetMaximumAccumulation(Duration::Milliseconds(milliseconds_double(20.0)));
    m_Stepper.Start();

    m_Particles.resize(MaxParticles);
    m_DrawParticles.resize(MaxParticles * 4);
    m_DrawParticles.setPrimitiveType(sf::PrimitiveType::Quads);

    SVector2f TTopLeft(0.f, 0.f), TTopRight(1.f, 0.f), TBtmLeft(0.f, 1.f), TBtmRight(1.f, 1.f);
    if (PTexture) {
      TTopRight.x = ( float )PTexture->getSize().x;
      TBtmLeft.y = ( float )PTexture->getSize().y;
      TBtmRight.x = TTopRight.x;
      TBtmRight.y = TBtmLeft.y;

      m_RenderState.texture = PTexture;
    }

    for (size_t i = 0; i < MaxParticles; ++i) {
      auto &V1 = m_DrawParticles[4 * i];
      auto &V2 = m_DrawParticles[4 * i + 1];
      auto &V3 = m_DrawParticles[4 * i + 2];
      auto &V4 = m_DrawParticles[4 * i + 3];

      V1.texCoords = TTopLeft;
      V2.texCoords = TBtmLeft;
      V3.texCoords = TBtmRight;
      V4.texCoords = TTopRight;

      V1.color = V2.color = V3.color = V4.color = sf::Color::Transparent;
    }

  }

  void ParticleSystem::AddAffector(const ParticleAffector &Paff, Duration dur /*= Duration::Milliseconds(1000000)*/)
  {
    m_Affectors.push_back(Paff);
  }

  void ParticleSystem::AddEmitter(const ParticleEmitter &Emit)
  {
    m_Emitters.push_back(Emit);
    m_Emitters.back().Play();
  }

  void ParticleSystem::Update()
  {
    for (auto & emt : m_Emitters) {
      emt.Update(this);
    }

    m_Stepper.Update();
    
    if (m_Stepper.IsStepUpdateNeeded())
      UpdateParticles();
  }

  void ParticleSystem::Render(sf::RenderTarget &Target)
  {
    Target.draw(m_DrawParticles, m_RenderState);
  }

  void ParticleSystem::KillParticle(size_t Index)
  {
    if (Index < m_LiveCount && Index < m_Particles.size()) {
      size_t vecPos = 4 * ( m_LiveCount - 1 );
      size_t vecdPos = 4 * Index;

      auto &V1 = m_DrawParticles[vecPos];
      auto &V2 = m_DrawParticles[vecPos + 1];
      auto &V3 = m_DrawParticles[vecPos + 2];
      auto &V4 = m_DrawParticles[vecPos + 3];

      auto &VD1 = m_DrawParticles[vecdPos];
      auto &VD2 = m_DrawParticles[vecdPos + 1];
      auto &VD3 = m_DrawParticles[vecdPos + 2];
      auto &VD4 = m_DrawParticles[vecdPos + 3];

      VD1.color = VD2.color = VD3.color = VD4.color = sf::Color::Transparent;

      std::swap(m_Particles[Index], m_Particles[m_LiveCount - 1]);
      std::swap(V1, VD1);
      std::swap(V2, VD2);
      std::swap(V3, VD3);
      std::swap(V4, VD4);

      m_LiveCount--;
    }
  }

  void ParticleSystem::UpdateParticles()
  {
    auto step = m_Stepper.GetStep();

    for (size_t i = 0; i < m_LiveCount; ++i) {
      Particle &Ptcl = m_Particles[i];

      Ptcl.LifeRemaining -= step;
      if (Ptcl.LifeRemaining <= Duration::Milliseconds(0UL)) {
        KillParticle(i);
        continue;
      }

      size_t vecPos  = 4 * i;

      auto &V1 = m_DrawParticles[vecPos];
      auto &V2 = m_DrawParticles[vecPos + 1];
      auto &V3 = m_DrawParticles[vecPos + 2];
      auto &V4 = m_DrawParticles[vecPos + 3];
      
      Ptcl.TotalForces.x = 0.f;
      Ptcl.TotalForces.y = 0.f;

      for (auto & aff : m_Affectors) {
        aff(Ptcl);
      }

      Ptcl.Velocity += Ptcl.TotalForces * ( float )step.AsSeconds().count();
      Ptcl.Position += ( Ptcl.Velocity ) * ( float )step.AsSeconds().count();

      auto pos = Ptcl.Position;
      auto rad = Ptcl.Radius;

      V1.position = pos;
      V2.position = pos + SVector2f(rad, 0.f);
      V3.position = pos + SVector2f(rad, rad);
      V4.position = pos + SVector2f(0.f, rad);

      V1.color = Ptcl.Color;
      V2.color = Ptcl.Color;
      V3.color = Ptcl.Color;
      V4.color = Ptcl.Color;
    }
  }

  void ParticleSystem::SpawnParticle(const Particle &P)
  {
    if (m_LiveCount < m_Particles.size() - 1) {
      m_Particles[m_LiveCount] = P;
      m_Particles[m_LiveCount].LifeRemaining = P.TotalLife;
      m_LiveCount++;
    }
  }

  void ParticleSystem::SetParticleTexture(sf::Texture *Texture)
  {
    m_RenderState.texture = Texture;
  }

}
