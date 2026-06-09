#pragma once
#include "core/events.h"
#include "modules/pomodoro.h"
class Engine {
public:
  // Controls the API layer will call from Crow routes
  static void startSession(int workMins, int breakMins, int cycles);
  static void pauseSession();
  static void stopSession();

  // Test function
  static void simulateTick();

private:
  static pomodoro::PomodoroContext pomodoro_;
  static void broadcastState(event_bus::FocusEvent eventType);
};
