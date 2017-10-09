#pragma once

namespace emp
{

  template<typename Container_t, typename Val_t>
  class CompIterGTIterator
  {
  public:
    CompIterGTIterator(typename Container_t::iterator curiter, typename Container_t::iterator enditer, Val_t compval);
    bool operator == (const CompIterGTIterator &Iter);
    bool operator != (const CompIterGTIterator &Iter);
    Val_t& operator*();
    CompIterGTIterator operator++();

  private:

    typename Container_t::iterator m_EndIter;
    typename Container_t::iterator m_CurrIter;
    const Val_t m_CompVal;

  };

  template<typename Container_t, typename Val_t>
  class CompIterGT
  {
  public:
    CompIterGT(Container_t &Cont, Val_t val);
    CompIterGTIterator<Container_t, Val_t> begin() const;
    CompIterGTIterator<Container_t, Val_t>  end() const;

  private:

    Container_t &m_Container;
    typename Container_t::iterator m_begin;
    typename Container_t::iterator m_end;
    typename Container_t::iterator m_curIter;
    const Val_t m_CompVal;

  };

}

#include "CompRange.inl"
