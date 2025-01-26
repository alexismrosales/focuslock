#pragma once
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace config {
void saveConfig(std::string configStr, std::string configPath,
                std::string fileName);
std::string loadConfig(std::string configPath, std::string fileName);
std::filesystem::path getPath(std::string configPath);
} // namespace config
