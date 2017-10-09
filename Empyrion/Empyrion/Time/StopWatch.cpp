#include "StopWatch.h"

namespace emp
{

  StopWatch::StopWatch() = default;

  StopWatch::StopWatch(const StopWatch &Tmr) = default;

  StopWatch::~StopWatch() = default;

  Duration StopWatch::GetElapsed()
  {
    if (!m_IsStarted)
      return Duration(time_resolution(0.0));
    else if (m_IsPaused)
      return m_Elapsed;

    return Duration(std::chrono::duration_cast< time_resolution >( std::chrono::high_resolution_clock::now() - m_StartTime ));
  }

  void StopWatch::Start()
  {
    m_IsStarted = true;
    m_IsPaused = false;
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_PauseTime = m_StartTime;
    m_Elapsed.Clear();
  }

  Duration StopWatch::Restart()
  {
    m_IsPaused = false;
    m_IsStarted = true;
    Duration elap(std::chrono::duration_cast< time_resolution >( std::chrono::high_resolution_clock::now() - m_StartTime ));
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_Elapsed.Clear();
    return elap;
  }

  void StopWatch::Pause()
  {
    if (m_IsPaused)
      return;

    m_IsPaused = true;
    m_PauseTime = std::chrono::high_resolution_clock::now();
  }

  void StopWatch::Resume()
  {
    m_StartTime += ( std::chrono::high_resolution_clock::now() - m_PauseTime );
    if (!m_IsPaused)
      return;

    m_IsPaused = false;
  }

  void StopWatch::Stop()
  {
    m_IsStarted = false;
    m_IsPaused = false;
  }

  bool StopWatch::IsStopped() const
  {
    return ( !m_IsPaused && !m_IsStarted );
  }

  bool StopWatch::IsPaused() const
  {
    return ( m_IsPaused && m_IsStarted );
  }

  bool StopWatch::IsTiming() const
  {
    return ( m_IsStarted && !m_IsPaused );
  }

}
