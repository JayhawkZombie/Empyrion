#pragma once

#include "Duration.h"
namespace emp
{

  class StopWatch
  {
  public:
    StopWatch();
    StopWatch(const StopWatch &Tmr);
    ~StopWatch();

    using time_resolution = milliseconds_double;

    Duration GetElapsed();
    void Start();
    Duration Restart();
    void Pause();
    void Resume();
    void Stop();

    bool IsStopped() const;
    bool IsPaused() const;
    bool IsTiming() const;

  private:

    bool m_IsPaused = false;
    bool m_IsStarted = false;

    Duration m_Elapsed;

    std::chrono::high_resolution_clock::time_point m_StartTime;
    std::chrono::high_resolution_clock::time_point m_PauseTime;
  };

}
