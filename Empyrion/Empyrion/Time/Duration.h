#pragma once

#include <chrono>

namespace emp
{

  using milliseconds_double = std::chrono::duration<double, std::chrono::milliseconds::period>;
  using seconds_double = std::chrono::duration<double, std::chrono::seconds::period>;
  using std::chrono::microseconds;
  using std::chrono::nanoseconds;

  class Duration
  {
  public:
    Duration() = default;
    Duration(const Duration &) = default;
    Duration(Duration &&) = default;
    ~Duration() = default;

    static Duration Milliseconds(milliseconds_double millis);
    template<typename T>
    static Duration Milliseconds(T mills);
    static Duration Microseconds(microseconds micros);
    static Duration Seconds(seconds_double secs);

    template<typename TimeType>
    Duration(const TimeType &TType);

    template<typename ScaleType>
    Duration operator*(const ScaleType &Scale);

    Duration operator+(const Duration &dur);
    Duration operator-(const Duration &dur);
    Duration& operator+=(const Duration &dur);
    Duration& operator-=(const Duration &dur);
    Duration& operator=(const Duration &) = default;

    template<typename TimeType = microseconds>
    friend Duration operator*=(const Duration &dur, const TimeType &Tme);

    template<typename TimeType = microseconds>
    friend Duration operator+=(const Duration &dur, const TimeType &Tme);

    bool operator >= (const Duration &dur2);
    bool operator > (const Duration &dur2);
    bool operator <= (const Duration &dur2);
    bool operator < (const Duration &dur2);
    bool operator == (const Duration &dur2);

    void FromMicroseconds(const microseconds &mics);
    void FromNanoseconds(const nanoseconds &nans);
    void FromMilliseconds(const milliseconds_double &mils);
    void FromSeconds(const seconds_double &secs);

    void Clear();
    microseconds AsMicroseconds() const;
    nanoseconds AsNanoseconds() const;
    milliseconds_double AsMilliseconds() const;
    seconds_double AsSeconds() const;

    using base_time_unit = milliseconds_double;

  private:

    milliseconds_double m_DurationTime = milliseconds_double(0.0);

  };

}

#include "Duration.inl"
