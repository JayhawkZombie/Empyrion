#pragma once

#include <type_traits>
#include <iterator>

namespace emp
{

  template<typename NumType = int>
  class RangeIterator
  {
  public:
    RangeIterator(NumType Val);
    bool operator == (const RangeIterator<NumType> &Iter);
    bool operator != (const RangeIterator<NumType> &Iter);
    const NumType& operator*() const;
    RangeIterator& operator++();

  private:

    NumType m_Value;

  };

  template<typename NumType = int>
  class Range
  {
  public:
    Range(NumType Low, NumType High);
    RangeIterator<NumType> begin() const;
    RangeIterator<NumType> end() const;

  private:

    const NumType m_Low;
    const NumType m_High;

  };

  using iRange = Range<int>;


  /************************************************************************/
  /*
  Reverse-order range iterator
  Usage:
  for (const auto & i : ReverseRange(0, 100))
  {
  // values will iterate from 100 to 0, inclusive on both ends
  }
  */
  /************************************************************************/

  template<typename NumType = int>
  class ReverseRangeIterator
  {
  public:
    ReverseRangeIterator(NumType Val);
    bool operator == (const ReverseRangeIterator<NumType> &Iter);
    bool operator != (const ReverseRangeIterator<NumType> &Iter);
    const NumType& operator*() const;
    ReverseRangeIterator& operator++();

  private:

    NumType m_Value;
  };

  template<typename NumType = int>
  class ReverseRange
  {
  public:

    ReverseRange(NumType Low, NumType High);

    using iterator = ReverseRangeIterator<NumType>;
    using const_iterator = ReverseRangeIterator<NumType>;
    ReverseRangeIterator<NumType> begin() const;
    ReverseRangeIterator<NumType> end() const;

  private:

    const NumType m_Low;
    const NumType m_High;

  };

  using iRange_r = ReverseRange<int>;

}

#include "IRange.inl"
