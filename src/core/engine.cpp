#include "core/engine.h"
#include "core/event_bus.h"
#include "core/events.h"
#include "modules/pomodoro.h"

// Allocating memory
pomodoro::PomodoroContext Engine::pomodoro_;

void Engine::broadcastState(event_bus::FocusEvent e) {
  // TODO: update session field with current session
  event_bus::EventPayload payload = {Engine::pomodoro_, "sample_session"};
  EventBus::publish(e, payload);
}

void Engine::simulateTick() {
  pomodoro::PomodoroContext *pContext = &Engine::pomodoro_;
  if (pContext->minutesRemaining.count() > 0) {
    pContext->minutesRemaining--;
  } else {
    pContext->currentCycle++;
  }
  Engine::broadcastState(event_bus::FocusEvent::TimerTick);
}
