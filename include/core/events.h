#pragma once
#include "modules/pomodoro.h"
namespace event_bus {
enum class FocusEvent { TimerTick, SessionChanged };
struct EventPayload {
  pomodoro::PomodoroContext pomodoro_state;
  std::string sessionName;
};
} // namespace event_bus
