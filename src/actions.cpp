#include "actions/actions.h"
#include "sessions/sessions.h"
#include <iostream>
#include <vector>

namespace actions {
void NewSession(std::string name) {
  // creating new session
  sessions::Session s = {name, sessions::Settings{}};
  std::vector<sessions::Session> sessions = sessions::loadSessions();
  // verify session name duplication
  for (auto &session : sessions) {
    if (session.name == name) {
      std::cerr << "Error creating session: session name already exist"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  // add new session
  sessions.push_back(s);

  sessions::saveSessions(sessions);
}
} // namespace actions
