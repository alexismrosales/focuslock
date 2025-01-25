#include "sessions/sessions.h"
#include "config/config.h"
#include "serialization/serialization.h"
#include <ryml/ryml.hpp>
#include <stdexcept>
#include <vector>

namespace sessions {
std::vector<Session> loadSessions() {
  std::string yamlSessions = config::loadConfig();
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
    std::cerr << "Error parsing YAML: " << e.what()
              << " (Exception Type: " << typeid(e).name() << ")" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return sessions;
}

void saveSessions(std::vector<sessions::Session> sessions) {
  try {
    ryml::Tree t = serialization::serializeSessions(sessions);
    // parse and save config
    config::saveConfig(ryml::emitrs_yaml<std::string>(t));
  } catch (const std::exception &e) {
    std::cerr << "Error parsing YAML: " << e.what()
              << " (Exception Type: " << typeid(e).name() << ")" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}
} // namespace sessions
