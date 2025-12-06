// runtime_meter.hpp
// Header-only runtime meter for ECE309 planner.
// Usage:
//   #include "runtime_meter.hpp"
//   int main() {
//     rt::ScopeTimer _timer("runtime_ms"); // prints to stderr on destruction
//     // ... load ./data/edges.txt, process all stdin queries ...
//     return 0;
//   }
//
// Notes:
// - Prints "runtime_ms=<milliseconds>" to STDERR (stdout remains clean).
// - If you prefer manual control, use RunTimer + print_ms() instead of ScopeTimer.
// - No external deps; uses std::chrono::steady_clock.
// - Optional: compile with -DRUNTIME_TIMER_ENABLE=0 to disable printing.

#ifndef RUNTIME_METER_HPP_
#define RUNTIME_METER_HPP_

#include <chrono>
#include <cstdio>
#include <cstdint>

#ifndef RUNTIME_TIMER_ENABLE
#define RUNTIME_TIMER_ENABLE 1
#endif

namespace rt {

  using clock_type = std::chrono::steady_clock;

  // Manual timer: call start(), do work, then stop_ms() and print_ms(...)
  struct RunTimer {
    clock_type::time_point t0;
    void start() noexcept { t0 = clock_type::now(); }
    double stop_ms() const noexcept {
      auto t1 = clock_type::now();
      return std::chrono::duration<double, std::milli>(t1 - t0).count();
    }
  };

  // Scope-based timer: prints "<label>=<ms>" to STDERR when it goes out of scope.
  // Default label is "runtime_ms".
  struct ScopeTimer {
    const char* label;
    clock_type::time_point t0;
    explicit ScopeTimer(const char* lbl = "runtime_ms")
      : label(lbl), t0(clock_type::now()) {}
    ~ScopeTimer() {
#if RUNTIME_TIMER_ENABLE
      auto t1 = clock_type::now();
      std::chrono::duration<double, std::milli> ms_double = t1 - t0;
      std::fprintf(stderr, "%s=%.4f\n", label, ms_double.count());
      std::fflush(stderr);
#endif
    }
  };

  // Explicit print helper (uses STDERR; safe for autograder).
  inline void print_ms(const char* label, double ms) {
#if RUNTIME_TIMER_ENABLE
    std::fprintf(stderr, "%s=%.4f\n", label, ms);
    std::fflush(stderr);
#endif
  }

} // namespace rt

#endif // RUNTIME_METER_HPP_