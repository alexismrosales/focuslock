#pragma once
#include <iostream>
#include <vector>
namespace actions {
void newSession(std::string name);
void setSession(std::string name);
std::string status();
std::string listSessions();
} // namespace actions
