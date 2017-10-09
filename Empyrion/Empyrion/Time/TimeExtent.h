#pragma once

#include "StopWatch.h"

namespace emp
{

	class TimeExtent
	{
	public:
	  TimeExtent() = default;
	  TimeExtent(const TimeExtent &) = default;
	  TimeExtent(TimeExtent &&) = default;
	  ~TimeExtent() = default;
	
	  void BeginTime();
	  Duration GetTime();
	  void UpdateTime();
	  void Reverse();
	  void SetSpeed(double timeSpeed);
	  void Shift(const Duration &Dur);
	  void Stop();
	  Duration Restart();
	  void Pause();
	  void Resume();
	
	  bool IsMovingForward() const;
	  bool IsStopped() const;
	  bool IsPaused() const;
	
	  using Instant = Duration::base_time_unit;
	
	  Instant GetInstant() const;
	
	private:
	
	  Duration m_TimeSinceBeginning;
	  StopWatch m_Stopwatch;
	
	  double m_TimeScale = 1.f;
	
	};

}
