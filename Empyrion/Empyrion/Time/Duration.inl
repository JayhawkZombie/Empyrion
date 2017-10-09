namespace emp
{


  template<typename T>
  Duration emp::Duration::Milliseconds(T mills)
  {
    Duration dur;
    dur.m_DurationTime = std::chrono::duration_cast< milliseconds_double >( std::chrono::milliseconds(mills) );
    return dur;
  }

  template<typename TimeType>
  Duration operator*=(const Duration &dur, const TimeType &Tme)
  {
    if constexpr ( std::is_same_v<TimeType, milliseconds_double> )
    {
      Duration d;
      d.m_DurationTime = dur.m_DurationTime * Tme;
      return d;

    } else {
      Duration d;
      auto dur = std::chrono::duration_cast< TimeType, milliseconds_double::period >( m_DurationTime );
      dur *= Tme;
      d.m_DurationTime = std::chrono::duration_cast< milliseconds_double >( dur );
      return d;
    }
  }


  template<typename TimeType>
  Duration operator+=(const Duration &dur, const TimeType &Tme)
  {
    if constexpr ( std::is_same_v<TimeType, milliseconds_double> )
    {
      Duration d;
      d.m_DurationTime = dur.m_DurationTime + Tme;
      return d;

    } else {
      Duration d;
      d.m_DurationTime = dur.m_DurationTime + std::chrono::duration_cast< milliseconds_double >( Tme );
      return d;
    }
  }

  template<typename TimeType>
  Duration::Duration(const TimeType &TType)
  {
    if constexpr ( std::is_same_v<TimeType, milliseconds_double> )
    {
      m_DurationTime = TType;
    } else {
      m_DurationTime = std::chrono::duration_cast< milliseconds_double >( TType );
    }
  }

  template<typename ScaleType>
  Duration Duration::operator*(const ScaleType &Scale)
  {
    if constexpr ( std::is_same_v<ScaleType, double> )
    {
      Duration dur;
      dur.m_DurationTime = m_DurationTime * Scale;
      return dur;
    } else {
      Duration dur;
      ScaleType scaled = m_DurationTime.count() * Scale;
      dur.m_DurationTime = milliseconds_double(static_cast< double >( scaled ));
      return dur;
    }
  }

}