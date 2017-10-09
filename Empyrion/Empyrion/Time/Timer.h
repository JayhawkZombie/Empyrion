#pragma once

#include <Empyrion/Time/StopWatch.h>
#include <functional>

namespace emp
{

  class Timer
  {
  public:
    Timer() = default;
    ~Timer() = default;

    Timer(const Timer &) = default;
    Timer(Timer &&) = default;

    void SetDuration(const Duration &dur);
    void Start();
    void Pause();
    void Resume();
    void Restart();
    void Stop();
    void Finish();

    // Update and return the time remaining on the timer (will be 0 if timer expired)
    Duration GetTime();

    bool IsFinished() const;
    bool IsPaused() const;

    void SetExpirationCallback(const std::function<void()> &Func);

  private:

    std::function<void()> m_ExpirationCallback = []() { };
    bool m_IsStarted = false;
    bool m_IsPaused = false;
    bool m_IsDone = true;

    Duration m_Duration;
    StopWatch m_StopWatch;

  };

}
