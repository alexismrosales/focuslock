#pragma once
#include <chrono>
#include <stdio.h>
namespace pomodoro {
struct Pomodoro {
  bool enable;
  std::chrono::minutes work;
  std::chrono::minutes shortBreak;
  std::chrono::minutes longBreak;
  int cycles;
};
} // namespace pomodoro
