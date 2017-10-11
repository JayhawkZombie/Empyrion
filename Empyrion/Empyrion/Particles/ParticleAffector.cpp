#include <Empyrion/Particles/ParticleAffector.h>

#include <Empyrion/Conversion/LiteralOps.h>

namespace emp
{

  ParticleAffector::ParticleAffector(std::function<void(Particle &p)> Func)
    : m_PFunc(Func)
  {

  }

  void ParticleAffector::operator()(Particle &P)
  {
    m_PFunc(P);
  }

  ParticleAffector ColorAffector(const sf::Color &StartColor, const sf::Color &EndColor)
  {
    auto f = [colorStart = StartColor, colorEnd = EndColor](Particle &P)
    {
      auto lifeRem = P.LifeRemaining.AsMilliseconds();
      auto totlife = P.TotalLife.AsMilliseconds();

      auto percAlive = lifeRem.count() / totlife.count();

      auto colorR = std::clamp(static_cast< sf::Uint8 >( percAlive * colorStart.r + ( 1 - percAlive ) * colorEnd.r ), 0_u8, 255_u8 );
      auto colorG = std::clamp(static_cast< sf::Uint8 >( percAlive * colorStart.g + ( 1 - percAlive ) * colorEnd.g ), 0_u8, 255_u8 );
      auto colorB = std::clamp(static_cast< sf::Uint8 >( percAlive * colorStart.b + ( 1 - percAlive ) * colorEnd.b ), 0_u8, 255_u8 );
      auto colorA = std::clamp(static_cast< sf::Uint8 >( percAlive * colorStart.a + ( 1 - percAlive ) * colorEnd.a ), 0_u8, 255_u8 );

      P.Color = sf::Color(colorR, colorG, colorB, colorA);
    };

    return ParticleAffector(f);
  }

  ParticleAffector FadeAffector(const float &StartPerc)
  {
    auto f = [percStart = StartPerc](Particle &P)
    {
      auto lifeRem = P.LifeRemaining.AsMilliseconds();
      auto totlife = P.TotalLife.AsMilliseconds();

      auto percAlive = lifeRem.count() / totlife.count();
      if (percAlive <= percStart) {

        auto percFaded = ( percStart - percAlive ) / percStart;

        P.Color.a = std::clamp(static_cast< sf::Uint8 >( 255_u8 * P.Color.a ), 0_u8, 255_u8);
      }
    };

    return ParticleAffector(f);
  }

  extern ParticleAffector ForceAffector(const SVector2f &Dir, float Mag)
  {
    auto f = [force = Dir, fmag = Mag](Particle &P)
    {
      P.TotalForces += force * fmag;
    };

    return ParticleAffector(f);
  }

  ParticleAffector AttractionAffector(const SVector2f &Pos, float mag, float cutoffRad)
  {
    auto f = [pos = Pos, fmag = mag, cutoff = cutoffRad](Particle &P)
    {
      auto diff = pos - P.Position;
      auto dist = hypotf(diff.x, diff.y);

 /*     if (dist >= cutoff)
        return;*/

      dist /= 100.f;

      SVector2f appliedforce = ( diff ) / dist;
      P.TotalForces += appliedforce * fmag;
    };

    return ParticleAffector(f);
  }

  extern ParticleAffector RepulsionAffector(const SVector2f &Pos, float mag, float cutoffRad)
  {
    auto f = [pos = Pos, fmag = mag, cutoff = cutoffRad](Particle &P)
    {
      auto diff = pos - P.Position;
      auto dist = hypotf(diff.x, diff.y);

      if (dist >= cutoff)
        return;

      dist /= 100.f;

      SVector2f appliedforce = ( diff ) / dist;
      P.TotalForces -= appliedforce * fmag;
    };

    return ParticleAffector(f);
  }

}
