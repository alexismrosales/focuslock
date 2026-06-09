#include "sessions/sessions.h"
#include "config/config.h"
#include "serialization/serialization.h"
#include <ryml/ryml.hpp>
#include <vector>

namespace sessions {

// parsingErrorException for yaml conversion
void parsingErrorException(const std::exception e) {
  std::cerr << "error parsing YAML: " << e.what()
            << " (Exception Type: " << typeid(e).name() << ")" << std::endl;
  std::exit(EXIT_FAILURE);
}

// loadSessions from $HOME/.config/focuslock/sessions.yaml
std::vector<Session> loadSessions() {
  std::string yamlSessions = config::loadConfig(".config", "sessions.yaml");
  std::vector<sessions::Session> sessions;
  // in case there are no sessions
  if (yamlSessions == "") {
    return {};
  }
  try {
    // obtaining sessions structs
    sessions =
        serialization::deserializeSessions(ryml::to_substr(yamlSessions));
  } catch (const std::exception &e) {
    parsingErrorException(e);
  }
  return sessions;
}

// saveSessions to $HOME/.config/focuslock/sessions.yaml
void saveSessions(std::vector<sessions::Session> sessions) {
  try {
    ryml::Tree t = serialization::serializeSessions(sessions);
    // parse and save config
    config::saveConfig(ryml::emitrs_yaml<std::string>(t), ".config",
                       "sessions.yaml");
  } catch (const std::exception &e) {
    parsingErrorException(e);
  }
}

// loadTemporalSession from $HOME/.local/focuslock/currentSession.yaml
Session loadTemporalSession() {
  std::string yamlSession =
      config::loadConfig(".local/share", "currentSession.yaml");
  if (yamlSession == "") {
    return {};
  }
  sessions::Session s;
  try {
    // return session
    s = serialization::deserializeSession(ryml::to_substr(yamlSession));
  } catch (const std::exception &e) {
    parsingErrorException(e);
  }
  return s;
}

// saveTemporalSession to $HOME/.local/focuslock/currentSession.yaml
void saveTemporalSession(sessions::Session s) {
  try {
    ryml::Tree t = serialization::serializeSession(s);
    config::saveConfig(ryml::emitrs_yaml<std::string>(t), ".local/share",
                       "currentSession.yaml");
  } catch (const std::exception &e) {
    parsingErrorException(e);
  }
}

std::string sessionInfo(const sessions::Session &s,
                        const bool isCurrentSession) {
  std::stringstream ss;
  ss << (isCurrentSession ? "current session: " : "session:") << s.name << "\n";
  ss << "   ├── pomodoro: "
     << (s.settings.pomodoro.enable ? "enabled" : "disabled") << "\n";
  ss << "   │   ├── work: " << s.settings.pomodoro.work.count() << " min\n";
  ss << "   │   ├── short break: " << s.settings.pomodoro.shortBreak.count()
     << " min\n";
  ss << "   │   ├── kong break: " << s.settings.pomodoro.longBreak.count()
     << " min\n";
  ss << "   │   └── cycles: " << s.settings.pomodoro.cycles << "\n";
  ss << "   └── blocker: " << (s.settings.block.enable ? "enabled" : "disabled")
     << "\n";

  if (!s.settings.block.domains.empty()) {
    ss << "   │   └── blocked Domains:\n";
    for (const auto &domain : s.settings.block.domains) {
      ss << "   │       • " << domain << "\n";
    }
  } else {
    ss << "       └── no domains blocked\n";
  }
  return ss.str();
}

int findSessionIndexByName(const std::vector<Session> ss, std::string name) {
  int i = 0;
  // find index of session selected
  while (i < ss.size()) {
    if (ss[i].name == name) {
      return i;
    }
    i++;
  }
  return -1;
}
} // namespace sessions
