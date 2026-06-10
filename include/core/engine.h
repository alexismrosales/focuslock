#pragma once
#include "core/events.h"
#include "modules/pomodoro.h"
#include <chrono>
class Engine {
public:
  // Controls the API layer will call from Crow routes
  static void startSession(std::chrono::minutes workMins,
                           std::chrono::minutes breakMins, int cycles);
  static void pauseSession();
  static void stopSession();

  // Test function
  static void simulateTick();

private:
  static pomodoro::PomodoroContext pomodoro_;
  static void broadcastState(event_bus::FocusEvent eventType);
};
