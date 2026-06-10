#include "core/event_bus.h"
#include "core/events.h"

std::map<event_bus::FocusEvent, std::vector<EventBus::Callback>>
    EventBus::listeners_;
void EventBus::subscribe(event_bus::FocusEvent e, Callback c) {
  listeners_[e].push_back(c);
}

void EventBus::publish(event_bus::FocusEvent e,
                       const event_bus::EventPayload &payload) {
  if (!listeners_.contains(e))
    return;
  for (const Callback &c : listeners_[e]) {
    c(payload);
  }
}
