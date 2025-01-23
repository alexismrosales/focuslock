#include "actions/actions.h"
#include "serialization/serialization.hpp"
#include "sessions/sessions.h"
#include <iostream>

namespace actions {
void NewSession(std::string name) {
  // creating new session
  sessions::Session s = {name, sessions::Settings{}};
  serialization::serializeSession(s);
  sessions::loadSessions();
}
} // namespace actions
