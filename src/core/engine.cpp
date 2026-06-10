#include "core/engine.h"
#include "core/event_bus.h"
#include "core/events.h"
#include "modules/pomodoro.h"
#include <chrono>

// Allocating memory
pomodoro::PomodoroContext Engine::pomodoro_;

void Engine::startSession(std::chrono::minutes workMins,
                          std::chrono::minutes breakMins, int cycles) {
  pomodoro::PomodoroContext *p = &Engine::pomodoro_;
  p->cycles = cycles;
  p->work = workMins;
  p->shortBreak = breakMins;

  p->minutesRemaining = workMins;
  // Noticing subscribers a new change
  Engine::broadcastState(event_bus::FocusEvent::TimerTick);
}
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
