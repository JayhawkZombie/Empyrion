template<typename T>
emp::distributions::Uniform<T>::Uniform(T DistMin, T DistMax) : m_RealDist(DistMin, DistMax), m_Min(DistMin), m_Max(DistMax)
{ }


template<typename T>
emp::distributions::Uniform<T>::Uniform(const Uniform &Unif)
  : m_Min(Unif.m_Min), m_Max(Unif.m_Max)
  , m_RealDist(m_Min, m_Max)
{

}

template<typename T>
T emp::distributions::Uniform<T>::operator()()
{
  return m_RealDist(m_Engine);
}

template<typename T>
emp::distributions::Uniform<T>::operator std::function<T() >()
{
  auto f = [uni = Uniform(*this)]() mutable -> T
  {
    return uni();
  };

  return f;
}
