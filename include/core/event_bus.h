#pragma once
#include "events.h"
#include <map>
#include <vector>
class EventBus {
public:
  using Callback = std::function<void(const event_bus::EventPayload &)>;
  static void subscribe(event_bus::FocusEvent e, Callback callback);
  static void publish(event_bus::FocusEvent e,
                      const event_bus::EventPayload &payload);
  // TODO: Do I need an unscubscribe function?
private:
  static std::map<event_bus::FocusEvent, std::vector<Callback>> listeners_;
};
