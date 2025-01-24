#include "sessions/sessions.h"
#include "config/config.hpp"
#include <ryml/ryml.hpp>
#include <vector>

namespace sessions {
std::vector<Session> loadSessions() {
  std::string yamlSessions = config::loadConfig();
  // in case there are no sessions
  if (yamlSessions == "") {
    return {};
  }
  ryml::Tree t = ryml::parse_in_place(ryml::to_substr(yamlSessions));
  ryml::ConstNodeRef root = t.rootref(); // a const node reference
  std::vector<Session> sessionsList;

  // for every session in yaml
  for (ryml::ConstNodeRef node : root.children()) {
    // TODO: convert every child in tree into a Session struct object,
    // transforming every node into the values of the struct Session
    if (node.has_child("session")) {
      std::cout << "Session: " << node["session"].val() << std::endl;
      std::cout << "Pomodoro Work Time: "
                << node["settings"]["pomodoro"]["work"].val() << std::endl;
    }
  }
  return sessionsList;
}
} // namespace sessions
