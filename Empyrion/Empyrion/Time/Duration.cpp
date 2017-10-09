#include "Duration.h"

namespace emp
{

  bool Duration::operator>=(const Duration &dur2)
  {
    return ( m_DurationTime >= dur2.m_DurationTime );
  }

  bool Duration::operator>(const Duration &dur2)
  {
    return ( m_DurationTime > dur2.m_DurationTime );
  }

  bool Duration::operator<=(const Duration &dur2)
  {
    return ( m_DurationTime <= dur2.m_DurationTime );
  }

  bool Duration::operator<(const Duration &dur2)
  {
    return ( m_DurationTime < dur2.m_DurationTime );
  }

  bool Duration::operator==(const Duration &dur2)
  {
    return ( m_DurationTime == dur2.m_DurationTime );
  }

  Duration Duration::Milliseconds(milliseconds_double millis)
  {
    Duration dur;
    dur.FromMilliseconds(millis);
    return dur;
  }

  Duration Duration::Microseconds(microseconds micros)
  {
    Duration dur;
    dur.FromMicroseconds(micros);
    return dur;
  }

  Duration Duration::Seconds(seconds_double secs)
  {
    Duration dur;
    dur.FromSeconds(secs);
    return dur;
  }

  Duration Duration::operator+(const Duration &dur)
  {
    Duration d;
    d.m_DurationTime = m_DurationTime + dur.m_DurationTime;
    return d;
  }

  Duration Duration::operator-(const Duration &dur)
  {
    Duration d;
    d.m_DurationTime = m_DurationTime - dur.m_DurationTime;
    return d;
  }

  void Duration::FromMicroseconds(const std::chrono::microseconds &mics)
  {
    m_DurationTime = std::chrono::duration_cast< milliseconds_double > ( mics );
  }

  void Duration::FromNanoseconds(const std::chrono::nanoseconds &nans)
  {
    m_DurationTime = std::chrono::duration_cast< milliseconds_double >( nans );
  }

  void Duration::FromMilliseconds(const milliseconds_double &mils)
  {
    m_DurationTime = mils;
  }

  void Duration::FromSeconds(const seconds_double &secs)
  {
    m_DurationTime = std::chrono::duration_cast< milliseconds_double >( secs );
  }

  void Duration::Clear()
  {
    m_DurationTime = std::chrono::microseconds(0);
  }

  std::chrono::microseconds Duration::AsMicroseconds() const
  {
    return std::chrono::duration_cast< microseconds >( m_DurationTime );
  }

  std::chrono::nanoseconds Duration::AsNanoseconds() const
  {
    return std::chrono::duration_cast< nanoseconds >( m_DurationTime );
  }

  milliseconds_double Duration::AsMilliseconds() const
  {
    return m_DurationTime;
  }

  seconds_double Duration::AsSeconds() const
  {
    return std::chrono::duration_cast< seconds_double >( m_DurationTime );
  }

  Duration& Duration::operator+=(const Duration &dur)
  {
    m_DurationTime += dur.m_DurationTime;
    return *this;
  }

  Duration& Duration::operator-=(const Duration &dur)
  {
    m_DurationTime -= dur.m_DurationTime;
    return *this;
  }

}
