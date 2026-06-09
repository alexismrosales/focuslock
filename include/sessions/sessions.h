#pragma once
#include "modules/block.h"
#include "modules/pomodoro.h"
#include <vector>
namespace sessions {
struct Settings {
  pomodoro::PomodoroContext pomodoro;
  block::Block block;
  Settings()
      : pomodoro{true, std::chrono::minutes(25), std::chrono::minutes(5),
                 std::chrono::minutes(15), 4},
        block{false, {}} {}
};

struct Session {
  std::string name;
  Settings settings;
};

std::vector<Session> loadSessions();
void saveSessions(std::vector<sessions::Session> sessions);
Session loadTemporalSession();
void saveTemporalSession(sessions::Session s);
std::string sessionInfo(const sessions::Session &s,
                        const bool isCurrentSession);
int findSessionIndexByName(const std::vector<Session> ss, std::string name);
} // namespace sessions
