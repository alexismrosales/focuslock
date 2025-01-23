#include "sessions/sessions.h"
#include "config/config.hpp"
#include <vector>

namespace sessions {
std::vector<Session> loadSessions() {
  std::vector<Session> sessionsList;
  // log
  std::cout << "content loaded:" << std::endl
            << config::loadConfig() << std::endl;
  return sessionsList;
}
} // namespace sessions
