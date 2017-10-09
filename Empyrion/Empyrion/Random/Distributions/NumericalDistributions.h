#pragma once

#include <Empyrion/Common.h>
#include <Empyrion/Time/Duration.h>
#include <random>
#include <functional>

namespace emp
{

  namespace distributions
  {

    template<typename T>
    class Uniform
    {
    public:
      Uniform(T DistMin, T DistMax);
      Uniform(const Uniform &Unif);
      virtual ~Uniform() = default;

      virtual T operator()();
      operator std::function<T()>();

    protected:

      T m_Min;
      T m_Max;

      std::default_random_engine m_Engine;
      std::uniform_real_distribution<T> m_RealDist;
    };

    class Duration
    {
    public:
      Duration(double min, double max);
      Duration(const Duration &dur);

      emp::Duration operator()();
      operator std::function<emp::Duration()>();

    protected:

      double m_Min;
      double m_Max;

      Uniform<double> m_Dist;
    };

  }

}

#include "NumericalDistributions.inl"
