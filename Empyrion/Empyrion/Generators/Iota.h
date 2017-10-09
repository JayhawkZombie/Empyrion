#pragma once

namespace emp
{

  template<typename T, typename V>
  class GenIota
  {
  public:
    GenIota(size_t count, V initial, V increment);
    explicit operator T() const;

  private:

    T m_Container;

  };

}

#include "Iota.inl"
