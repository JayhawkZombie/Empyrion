namespace emp
{

  template<typename T, typename V>
  emp::GenIota<T, V>::GenIota(size_t count, V initial, V increment)
  {
    m_Container.resize(count);

    V val = initial;
    for (auto & v : m_Container) {
      v = val;
      val += increment;
    }
  }


  template<typename T, typename V>
  emp::GenIota<T, V>::operator T() const
  {
    return m_Container;
  }


}