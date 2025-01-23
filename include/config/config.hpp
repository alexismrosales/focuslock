#pragma once
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace config {
const std::string configPath = ".config/focuslock";
const std::string configFilename = "sessions.yaml";
void saveConfig(std::string config);
std::string loadConfig();
std::filesystem::path getPath();
} // namespace config
