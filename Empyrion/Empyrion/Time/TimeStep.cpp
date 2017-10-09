#include <Empyrion/Time/TimeStep.h>

namespace emp
{
  void TimeStep::Update()
  {
    auto dur = m_Stopwatch.Restart();
    m_CurrentInterp = 1.f;

    // If more time has elapsed than the max step, only accumulate the max step
    // and discard the rest
    if (dur > m_MaxDuration) {
      m_CurrentElapsed += m_MaxDuration;
    }
    else {
      m_CurrentElapsed += dur;
    }
  }

  void TimeStep::Start()
  {
    m_Stopwatch.Start();
    m_CurrentElapsed.Clear();
  }

  void TimeStep::Pause()
  {
    m_Stopwatch.Pause();
  }

  void TimeStep::Resume()
  {
    m_Stopwatch.Resume();
  }

  void TimeStep::SetStep(const Duration &Dur)
  {
    m_StepDuration = Dur;
  }

  void TimeStep::SetMaximumAccumulation(const Duration &Dur)
  {
    m_MaxDuration = Dur;
  }

  const Duration& TimeStep::GetStep() const
  {
    return m_StepDuration;
  }

  float TimeStep::GetInterpolationAlpha() const
  {
    return m_CurrentInterp;
  }

  bool TimeStep::IsStepUpdateNeeded()
  {
    if (m_CurrentElapsed >= m_StepDuration) {
      m_CurrentElapsed -= m_StepDuration;
      return true;
    }

    // Quotient of the remaining elapsed time and the total step
    // is the interp alpha
    m_CurrentInterp = ( float )m_CurrentElapsed.AsMicroseconds().count() / ( float )( m_StepDuration.AsMicroseconds().count() );
    return false;
  }
}
