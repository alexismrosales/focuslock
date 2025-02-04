#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
namespace actions {
std::string newSession(std::string name);
std::string setSession(std::string name);
std::string status(std::string name);
std::string listSessions();
std::string pomodoro(std::unordered_map<std::string, int> args);
std::string block(std::unordered_map<std::string, std::string> args);
void start();
} // namespace actions
