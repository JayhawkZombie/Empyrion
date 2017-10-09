#include "TimeExtent.h"

namespace emp
{

  void TimeExtent::BeginTime()
  {
    m_Stopwatch.Start();
    m_TimeSinceBeginning.Clear();
  }

  Duration TimeExtent::GetTime()
  {
    UpdateTime();
    return m_TimeSinceBeginning;
  }

  void TimeExtent::UpdateTime()
  {
    m_TimeSinceBeginning += m_Stopwatch.Restart() * m_TimeScale;
  }

  void TimeExtent::Reverse()
  {
    m_TimeScale *= -1.f;
  }

  void TimeExtent::SetSpeed(double timeSpeed)
  {
    m_TimeScale = timeSpeed;
  }

  void TimeExtent::Shift(const Duration &Dur)
  {
    m_TimeSinceBeginning += Dur;
  }

  void TimeExtent::Stop()
  {
    m_Stopwatch.Stop();
  }

  Duration TimeExtent::Restart()
  {
    auto dur = m_Stopwatch.Restart() * m_TimeScale;
    m_TimeSinceBeginning.Clear();
    m_TimeScale = 1.f;
    return dur;
  }

  void TimeExtent::Pause()
  {
    m_Stopwatch.Pause();
  }

  void TimeExtent::Resume()
  {
    m_Stopwatch.Resume();
  }

  bool TimeExtent::IsMovingForward() const
  {
    return ( m_TimeScale > 0.f );
  }

  bool TimeExtent::IsStopped() const
  {
    return m_Stopwatch.IsStopped();
  }

  bool TimeExtent::IsPaused() const
  {
    return m_Stopwatch.IsPaused();
  }

  TimeExtent::Instant TimeExtent::GetInstant() const
  {
    return m_TimeSinceBeginning.AsMilliseconds();
  }

}
