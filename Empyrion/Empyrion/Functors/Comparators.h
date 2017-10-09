#pragma once

namespace emp
{

  template<typename T>
  struct IsBetween
  {
    IsBetween(T val, T low, T high);
    operator bool() const;

    const T value;
    const T lower;
    const T higher;
  };

}

#include "Comparitors.inl"
