#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
namespace actions {
void newSession(std::string name);
void setSession(std::string name);
std::string status();
std::string listSessions();
void pomodoro(std::unordered_map<std::string, int> args);
} // namespace actions
