namespace emp
{

  template<typename Container_t, typename Val_t>
  CompIterGTIterator<Container_t, Val_t>::CompIterGTIterator(typename Container_t::iterator curiter, typename Container_t::iterator enditer, Val_t compval)
    : m_CompVal(compval), m_CurrIter(curiter), m_EndIter(enditer)
  { }

  template<typename Container_t, typename Val_t>
  bool CompIterGTIterator<Container_t, Val_t>::operator==(const CompIterGTIterator &Iter)
  {
    return ( m_CurrIter == Iter.m_CurrIter );
  }

  template<typename Container_t, typename Val_t>
  bool CompIterGTIterator<Container_t, Val_t>::operator!=(const CompIterGTIterator &Iter)
  {
    return ( m_CurrIter != Iter.m_CurrIter );
  }

  template<typename Container_t, typename Val_t>
  Val_t& CompIterGTIterator<Container_t, Val_t>::operator*()
  {
    return *m_CurrIter;
  }

  template<typename Container_t, typename Val_t>
  CompIterGTIterator<Container_t, Val_t> CompIterGTIterator<Container_t, Val_t>::operator++()
  {
    ++m_CurrIter;

    while (m_CurrIter != m_EndIter && *m_CurrIter <= m_CompVal)
      ++m_CurrIter;

    return CompIterGTIterator(m_CurrIter, m_EndIter, m_CompVal);
  }


  /*
    CompIterGT - GreaterThan comparitor iterator
  */

  template<typename Container_t, typename Val_t>
  CompIterGT<Container_t, Val_t>::CompIterGT(Container_t &Cont, Val_t val) : m_Container(Cont), m_begin(Cont.begin()), m_end(Cont.end()), m_CompVal(val)
  {
    size_t i = 0;
    for (const auto & it : Cont) {
      if (it > val) break;
      i++;
    }

    if (i < Cont.size() - 1)
      m_begin = Cont.begin() + i;
    else
      m_begin = m_end;

    m_curIter = m_begin;
  }

  template<typename Container_t, typename Val_t>
  CompIterGTIterator<Container_t, Val_t> CompIterGT<Container_t, Val_t>::begin() const
  {
    return CompIterGTIterator<Container_t, Val_t>(m_begin, m_end, m_CompVal);
  }


  template<typename Container_t, typename Val_t>
  CompIterGTIterator<Container_t, Val_t> CompIterGT<Container_t, Val_t>::end() const
  {
    return CompIterGTIterator<Container_t, Val_t>(m_Container.end(), m_end, m_CompVal);
  }

}
