namespace emp
{

  template<class Iter, class Predicate, class Func>
  void TransformIf(Iter Beg, Iter End, Predicate cond, Func Trans)
  {
    Iter it = Beg;
    while (it != End) {
      if (cond(*it))
        Trans(*it);
      ++it;
    }
  }

  template<class Iter, class Predicate, class Func>
  void TransformIfNot(Iter Beg, Iter End, Predicate cond, Func Trans)
  {
    Iter it = Beg;
    while (it != End) {
      if (!cond(*it)) {
        Trans(*it);
      }
      ++it;
    }
  }

  template<class Iter, class Predicate, class UnaryFunc>
  void ForEachIf(Iter Beg, Iter End, Predicate Cond, UnaryFunc Func)
  {
    Iter it = Beg;
    while (it != End) {
      if (Cond(*it)) {
        Func(*it);
      }
      ++it;
    }
  }

}