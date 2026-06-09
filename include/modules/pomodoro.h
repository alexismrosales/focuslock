#pragma once
#include <chrono>
#include <functional>
#include <stdio.h>
#include <string>
namespace pomodoro {
struct PomodoroContext {
  bool enable;
  std::chrono::minutes work;
  std::chrono::minutes shortBreak;
  std::chrono::minutes longBreak;
  int cycles;
  int currentCycle;
  bool active;
  std::chrono::minutes minutesRemaining;
};
void startTimer(PomodoroContext p);
void timer(std::chrono::minutes time,
           std::function<void(std::string minute, std::string second)>
               printTimerFunction);

void showStatus();
} // namespace pomodoro
