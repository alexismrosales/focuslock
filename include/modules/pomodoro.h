#pragma once
#include <chrono>
#include <functional>
#include <stdio.h>
#include <string>
namespace pomodoro {
struct Pomodoro {
  bool enable;
  std::chrono::minutes work;
  std::chrono::minutes shortBreak;
  std::chrono::minutes longBreak;
  int cycles;
};
void startTimer(Pomodoro p);
void timer(std::chrono::minutes time,
           std::function<void(std::string minute, std::string second)>
               printTimerFunction);

void showStatus();
} // namespace pomodoro
