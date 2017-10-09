#pragma once

#include <Empyrion/Random/Distributions/NumericalDistributions.h>
#include <functional>

namespace emp
{

  namespace distributions
  {

    class Circle
    {
    public:
      Circle(const SVector2f &Center, const float &Radius);
      Circle(const Circle &Circ);
      SVector2f operator()();
      operator std::function<SVector2f()>();

    private:

      Uniform<float> m_Dist;
      SVector2f m_Center;
      float m_Radius;
    };

    class Direction
    {
    public:
      Direction(const SVector2f &Dir, const float &Deviation);
      Direction(const Direction &Dir);
      SVector2f operator()();
      operator std::function<SVector2f()>();

    private:

      Uniform<float> m_Dist;
      SVector2f m_Direction;
      float m_Deviation;
    };

    class CircularArea
    {
    public:
      CircularArea(const SVector2f &Center, const float &Radius);
      CircularArea(const CircularArea &Area);
      SVector2f operator()();
      operator std::function<SVector2f()>();

    private:

      SVector2f m_Center;
      float m_Radius;
      Uniform<float> m_RadDist;
      Uniform<float> m_AngleDist;

    };

    class Line
    {
    public:
      Line(const SVector2f &Start, const SVector2f &End);
      SVector2f operator()();
      operator std::function<SVector2f()>();

    private:

      SVector2f m_Start;
      SVector2f m_Diff;

      Uniform<float> m_MagDist;

    };

    class Radial
    {
    public:
      Radial(const float &Min, const float &Max, const float &MagMin, const float &MagMax);
      SVector2f operator()();
      operator std::function<SVector2f()>();

    private:

      Uniform<float> m_MagDist;
      Uniform<float> m_AndleDist;
    };

  }

}
