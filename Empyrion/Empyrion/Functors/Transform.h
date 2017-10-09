#pragma once

namespace emp
{

  template<class Iter, class Predicate, class Func>
  extern void TransformIf(Iter Beg, Iter End, Predicate cond, Func Trans);

  template<class Iter, class Predicate, class Func>
  extern void TransformIfNot(Iter Beg, Iter End, Predicate cond, Func Trans);

  template<class Iter, class Predicate, class UnaryFunc>
  extern void ForEachIf(Iter Beg, Iter End, Predicate Cond, UnaryFunc Func);

}

#include "Transform.inl"
