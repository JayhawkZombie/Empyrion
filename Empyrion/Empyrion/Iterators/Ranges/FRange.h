#pragma once
#include <type_traits>

namespace emp
{

  class FloatRangeIterator
  {
  public:
    FloatRangeIterator(float value, float Incr);
    bool operator == (const FloatRangeIterator &Iter);
    bool operator != (const FloatRangeIterator &Iter);
    const float& operator*() const;
    FloatRangeIterator& operator++();

  private:

    float m_Value;
    float m_Incr;

  };

  class FloatRange
  {
  public:
    FloatRange(float From, float To, float Increment);
    FloatRangeIterator begin() const;
    FloatRangeIterator end() const;

  private:

    const float m_From;
    const float m_To;
    const float m_Increment;

  };

  using fRange = FloatRange;

}
