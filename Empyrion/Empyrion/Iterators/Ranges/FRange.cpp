#include <Empyrion/Iterators/Ranges/FRange.h>

namespace emp
{

  bool FloatRangeIterator::operator!=(const FloatRangeIterator &Iter)
  {
    float fdiff = ( Iter.m_Value - m_Value );
    return abs(fdiff > 0.f);
  }

  bool FloatRangeIterator::operator==(const FloatRangeIterator &Iter)
  {
    float fdiff = abs(Iter.m_Value - m_Value);
    return ( fdiff == 0.f );
  }

  FloatRangeIterator::FloatRangeIterator(float value, float Incr) : m_Value(value), m_Incr(Incr)
  {

  }

  const float& FloatRangeIterator::operator*() const
  {
    return m_Value;
  }

  FloatRangeIterator& FloatRangeIterator::operator++()
  {
    m_Value += m_Incr;
    return *this;
  }

  FloatRange::FloatRange(float From, float To, float Increment) : m_From(From), m_To(To), m_Increment(Increment)
  {

  }

  FloatRangeIterator FloatRange::begin() const
  {
    return { m_From, m_Increment };
  }

  FloatRangeIterator FloatRange::end() const
  {
    return { m_To, m_Increment };
  }

}
