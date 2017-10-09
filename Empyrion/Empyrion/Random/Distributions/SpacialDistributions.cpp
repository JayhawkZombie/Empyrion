#include <Empyrion/Random/Distributions/SpacialDistributions.h>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <iostream>

namespace emp
{

  namespace distributions
  {

    Circle::Circle(const SVector2f &Center, const float &Radius)
      : m_Dist(0.f, 2.f * (float)M_PI)
      , m_Center(Center)
      , m_Radius(Radius)
    {

    }

    Circle::Circle(const Circle &Circ)
      : m_Dist(0.f, 2.f * (float)M_PI)
      , m_Center(Circ.m_Center)
      , m_Radius(Circ.m_Radius)
    {

    }

    SVector2f Circle::operator()()
    {
      auto angle = m_Dist();

      SVector2f displ = SVector2f(std::sinf(angle), std::cosf(angle));
      return ( m_Center + m_Radius * displ );
    }

    Circle::operator std::function<SVector2f() >()
    {
      auto f = [circ = Circle(*this)]() mutable -> SVector2f
      {
        return circ();
      };

      return f;
    }

    Direction::Direction(const SVector2f &Dir, const float &Deviation)
      : m_Dist(-Deviation * ( 2.f * (float)M_PI / 180.f ), Deviation * ( 2.f * (float)M_PI / 180.f ))
      , m_Direction(Dir / hypotf(Dir.x, Dir.y)), m_Deviation(Deviation)
    {

    }

    Direction::Direction(const Direction &Dir)
      : m_Deviation(Dir.m_Deviation), m_Direction(Dir.m_Direction)
      , m_Dist(-m_Deviation * ( 2.f * ( float )M_PI / 180.f ), m_Deviation * ( 2.f * ( float )M_PI / 180.f ))
    {

    }

    SVector2f Direction::operator()()
    {
      auto angleOffset = m_Dist();

      SVector2f newDir;

      auto sinA = std::sinf(angleOffset);
      auto cosA = std::cosf(angleOffset);

      newDir.x = m_Direction.x * cosA - m_Direction.y * sinA;
      newDir.y = m_Direction.y * cosA + m_Direction.x * sinA;
      return newDir;
    }

    Direction::operator std::function<SVector2f() >()
    {
      auto f = [dir = Direction(*this)]() mutable->SVector2f
      {
        return dir();
      };

      return f;
    }

    CircularArea::CircularArea(const SVector2f &Center, const float &Radius)
      : m_RadDist(-m_Radius, Radius), m_AngleDist(0.f, 2.f * (float)M_PI), m_Center(Center), m_Radius(Radius)
    {

    }

    CircularArea::CircularArea(const CircularArea &Area)
      : m_Center(Area.m_Center), m_Radius(Area.m_Radius)
      , m_RadDist(-m_Radius, m_Radius), m_AngleDist(0.f, 2.f * ( float )M_PI)
    {

    }

    SVector2f CircularArea::operator()()
    {
      auto radx = m_RadDist();
      auto rady = m_RadDist();
      auto angle = m_AngleDist();

      SVector2f pointOff(radx * std::cosf(angle), rady * std::sinf(angle));
      return ( m_Center + pointOff );
    }

    CircularArea::operator std::function<SVector2f() >()
    {
      auto f = [circ = CircularArea(*this)]() mutable -> SVector2f
      {
        return circ();
      };

      return f;
    }

    Line::Line(const SVector2f &Start, const SVector2f &End)
      : m_Start(Start), m_Diff(End - Start)
      , m_MagDist(0.f, 1.f)
    {

    }

    SVector2f Line::operator()()
    {
      auto mag = m_MagDist();

      SVector2f pt = m_Start + m_Diff * mag;
      return pt;
    }

    Line::operator std::function<SVector2f() >()
    {
      auto f = [lin = Line(*this)]() mutable->SVector2f
      {
        return lin();
      };

      return f;
    }

    Radial::Radial(const float &Min, const float &Max, const float &MagMin, const float &MagMax)
      : m_AndleDist(Min, Max), m_MagDist(MagMin, MagMax)
    {

    }

    SVector2f Radial::operator()()
    {
      auto angle = m_AndleDist();
      auto mag = m_MagDist();

      return SVector2f(mag * std::cosf(angle), mag * std::sinf(angle));
    }

    Radial::operator std::function<SVector2f()>()
    {
      auto f = [ang = Radial(*this)]() mutable -> SVector2f
      {
        return ang();
      };

      return f;
    }

  }

}
