namespace emp
{

  template<typename T>
  IsBetween<T>::operator bool() const
  {
    return ( value >= low && value <= high );
  }

  template<typename T>
  IsBetween<T>::IsBetween(T val, T low, T high)
    : value(val), lower(low), higher(high)
  { }

}
