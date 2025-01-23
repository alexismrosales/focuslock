#pragma once
#include "modules/block.h"
#include "modules/pomodoro.h"
#include <iostream>
#include <vector>
namespace sessions {
struct Settings {
  pomodoro::Pomodoro pomodoro;
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

struct AllSessions {
  std::vector<Session> sessionList;
};
} // namespace sessions
