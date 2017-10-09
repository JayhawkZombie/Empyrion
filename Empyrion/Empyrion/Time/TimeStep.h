#pragma once

#include <Empyrion/Time/StopWatch.h>

namespace emp
{

  class TimeStep
  {
  public:
    TimeStep() = default;
    ~TimeStep() = default;

    void Update();
    void Start();
    void Pause();
    void Resume();
    void SetStep(const Duration &Dur);
    void SetMaximumAccumulation(const Duration &Dur);

    const Duration& GetStep() const;
    float GetInterpolationAlpha() const;

    bool IsStepUpdateNeeded();

  private:

    Duration m_MaxDuration;
    Duration m_CurrentElapsed;
    Duration m_StepDuration;

    float m_CurrentInterp = 1.f;

    StopWatch m_Stopwatch;

  };

}
