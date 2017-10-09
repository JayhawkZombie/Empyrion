namespace emp
{

  template<typename NumType /*= int*/>
  RangeIterator<NumType>::RangeIterator(NumType Val) : m_Value(Val)
  {
    static_assert( std::is_integral_v<NumType>,
                  "RangeIterator only supports integral types" );
  }

  template<typename NumType /*= int*/>
  bool RangeIterator<NumType>::operator==(const RangeIterator<NumType> &Iter)
  {
    return ( m_Value == Iter.m_Value );
  }

  template<typename NumType /*= int*/>
  bool RangeIterator<NumType>::operator!=(const RangeIterator<NumType> &Iter)
  {
    return ( m_Value != Iter.m_Value );
  }

  template<typename NumType /*= int*/>
  const NumType& RangeIterator<NumType>::operator*() const
  {
    return m_Value;
  }

  template<typename NumType /*= int*/>
  RangeIterator<NumType>& RangeIterator<NumType>::operator++()
  {
    ++m_Value;
    return *this;
  }

  template<typename NumType /*= int*/>
  Range<NumType>::Range(NumType Low, NumType High) : m_Low(Low), m_High(High)
  {
    static_assert( std::is_integral_v<NumType>,
                  "Range only supports integral types" );
  }

  template<typename NumType /*= int*/>
  RangeIterator<NumType> Range<NumType>::begin() const
  {
    return { m_Low };
  }

  template<typename NumType /*= int*/>
  RangeIterator<NumType> Range<NumType>::end() const
  {
    return { m_High + 1 };
  }

  /*
    Reverse Range
  */
  template<typename NumType /*= int*/>
  ReverseRangeIterator<NumType>::ReverseRangeIterator(NumType Val) : m_Value(Val)
  {
    static_assert( std::is_integral_v<NumType>,
                  "ReverseRangeIterator only supports integral types" );
  }

  template<typename NumType /*= int*/>
  bool ReverseRangeIterator<NumType>::operator==(const ReverseRangeIterator<NumType> &Iter)
  {
    return ( m_Value == Iter.m_Value );
  }

  template<typename NumType /*= int*/>
  bool ReverseRangeIterator<NumType>::operator!=(const ReverseRangeIterator<NumType> &Iter)
  {
    return ( m_Value != Iter.m_Value );
  }

  template<typename NumType /*= int*/>
  const NumType& ReverseRangeIterator<NumType>::operator*() const
  {
    return m_Value;
  }

  template<typename NumType /*= int*/>
  ReverseRangeIterator<NumType>& ReverseRangeIterator<NumType>::operator++()
  {
    --m_Value;
    return *this;
  }

  template<typename NumType /*= int*/>
  ReverseRange<NumType>::ReverseRange(NumType Low, NumType High) : m_Low(Low), m_High(High)
  {
    static_assert( std::is_integral_v<NumType>,
                  "ReverseRange only supports integral types" );
  }

  template<typename NumType /*= int*/>
  ReverseRangeIterator<NumType> ReverseRange<NumType>::begin() const
  {
    return { m_High };
  }

  template<typename NumType /*= int*/>
  ReverseRangeIterator<NumType> ReverseRange<NumType>::end() const
  {
    return { m_Low - 1 };
  }

}
