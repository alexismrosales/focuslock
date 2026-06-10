#include "core/engine.h"
#include "core/event_bus.h"
#include <chrono>
#include <iostream>
int main(int argc, char *argv[]) {
  EventBus::subscribe(event_bus::FocusEvent::TimerTick,
                      [](const event_bus::EventPayload &payload) {
                        std::cout
                            << "[Test Subscriber] Caught tick! Session: "
                            << payload.sessionName << " | Cycle: "
                            << payload.pomodoro_state.currentCycle
                            << " | Minutes Left: "
                            << payload.pomodoro_state.minutesRemaining.count()
                            << std::endl;
                      });
  std::chrono::minutes workMin(25);
  std::chrono::minutes breakMin(4);
  Engine::startSession(workMin, breakMin, 4);
  Engine::simulateTick();
  Engine::simulateTick();
  Engine::simulateTick();
}
