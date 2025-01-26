#include "sessions/sessions.h"
#include "config/config.h"
#include "serialization/serialization.h"
#include <ryml/ryml.hpp>
#include <stdexcept>
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
} // namespace sessions
