#pragma once
#include <chrono>
namespace event_bus {
enum class FocusEvent { TimerTick, SessionChanged };
struct EventPayload {
  std::chrono::seconds seconds_remaining; // Timestamp
  std::string session_name;
};
} // namespace event_bus
