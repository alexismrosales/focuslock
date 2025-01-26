#include "actions/actions.h"
#include "sessions/sessions.h"
#include <iostream>
#include <vector>

namespace actions {
void newSession(std::string name) {
  // creating new session
  sessions::Session s = {name, sessions::Settings{}};
  std::vector<sessions::Session> ss = sessions::loadSessions();
  // verify session name duplication
  for (auto &session : ss) {
    if (session.name == name) {
      std::cerr << "Error creating session: session name already exist"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  // add new session
  ss.push_back(s);

  sessions::saveSessions(ss);
}

void setSession(std::string name) {
  std::vector<sessions::Session> ss = sessions::loadSessions();
  int i = 0;
  // find index of session selected
  while (i < ss.size()) {
    if (ss[i].name == name) {
      break;
    }
    i++;
  }
  // in case session was not found
  if (i == ss.size()) {
    std::cerr << "error obtaining temp session: session does not exists"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }
  // save session
  sessions::saveTemporalSession(ss[i]);
}

std::string status() {
  sessions::Session s = sessions::loadTemporalSession();
  if (!s.name.empty()) {
    return "current session: " + s.name + "\n    -pomodoro: " +
           (s.settings.pomodoro.enable ? "enabled" : "disabled") +
           "\n    -blocker: " +
           (s.settings.pomodoro.enable ? "enabled" : "disabled");
  } else {
    return "no current session set";
  }
}

std::string listSessions() {
  std::vector<sessions::Session> ss = sessions::loadSessions();
  std::string sessionsStr = "";
  // iterate over sessions
  for (int i = 0; i < ss.size(); i++) {
    sessionsStr += "[" + std::to_string(i + 1) + "]" + "session:" + ss[i].name +
                   "\n    -pomodoro:" +
                   (ss[i].settings.pomodoro.enable ? "true" : "false") +
                   "\n    -blocker: " +
                   (ss[i].settings.pomodoro.enable ? "true" : "false") + "\n\n";
  }
  // remove last two line breaks
  sessionsStr.pop_back();
  sessionsStr.pop_back();
  return sessionsStr;
}
} // namespace actions
