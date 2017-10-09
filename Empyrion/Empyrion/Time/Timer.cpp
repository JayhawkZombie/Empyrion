#include <Empyrion/Time/Timer.h>

namespace emp
{

  void Timer::SetDuration(const Duration &dur)
  {
    m_Duration = dur;
  }

  void Timer::Start()
  {
    m_StopWatch.Start();
    m_IsDone = false;
    m_IsPaused = false;
    m_IsStarted = true;
  }

  void Timer::Pause()
  {
    m_IsPaused = true;
    m_StopWatch.Pause();
  }

  void Timer::Resume()
  {
    m_IsPaused = false;
    m_StopWatch.Restart();
  }

  void Timer::Restart()
  {
    m_IsPaused = false;
    m_IsDone = false;
    m_IsStarted = true;
    m_StopWatch.Restart();
  }

  void Timer::Stop()
  {
    m_IsDone = true;
    m_IsStarted = false;
    m_IsPaused = false;
    m_StopWatch.Stop();
  }

  void Timer::Finish()
  {
    m_IsDone = true;
    m_IsStarted = false;
    m_IsPaused = false;
    m_Duration.Clear();
    m_ExpirationCallback();
  }

  Duration Timer::GetTime()
  {
    Duration Dur = m_StopWatch.GetElapsed();

    if (Dur >= m_Duration) {
      m_IsDone = true;
      m_StopWatch.Stop();
    }

    return Dur;
  }

  bool Timer::IsFinished() const
  {
    return m_IsDone;
  }

  bool Timer::IsPaused() const
  {
    return m_IsPaused;
  }

  void Timer::SetExpirationCallback(const std::function<void()> &Func)
  {
    m_ExpirationCallback = Func;
  }

}
