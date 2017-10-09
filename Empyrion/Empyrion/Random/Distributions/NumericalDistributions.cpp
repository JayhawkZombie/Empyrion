#include <Empyrion/Random/Distributions/NumericalDistributions.h>

namespace emp
{

  distributions::Duration::Duration(double min, double max)
    : m_Min(min), m_Max(max)
    , m_Dist(min, max)
  {

  }

  emp::Duration distributions::Duration::operator()()
  {
    auto time = m_Dist();

    return emp::Duration::Seconds(seconds_double(time));
  }

  distributions::Duration::Duration(const Duration &dur)
    : m_Min(dur.m_Min), m_Max(dur.m_Max)
    , m_Dist(m_Min, m_Max)
  {

  }

  distributions::Duration::operator std::function<emp::Duration() >()
  {
    auto f = [dur = Duration(*this)]() mutable -> emp::Duration
    {
      return dur();
    };

    return f;
  }

}
