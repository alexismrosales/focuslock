#pragma once
#include "modules/block.h"
#include "modules/pomodoro.h"
#include <iostream>
#include <vector>
namespace actions {

struct Config {
  pomodoro::Pomodoro pomodoro;
  block::Block block;
};

struct Session {
  std::string name;
  Config config;
};

struct Sessions {
  std::vector<Session> sessionList;
};

void NewSession(std::string session);
} // namespace actions
