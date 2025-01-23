#include "config/config.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace config {
void saveConfig(std::string config) {}

std::string loadConfig() {
  try {
    std::filesystem::path path = getPath();
    // if directories of $HOME/.config/focuslock does not exist
    if (!std::filesystem::exists(path)) {
      std::filesystem::create_directories(path);
    }
    // TODO: create a new file if it does not exist

    // loading file
    std::ifstream configFile(path / configFilename);
    std::string config = "";
    std::string line;
    // saving file into config string
    while (getline(configFile, line)) {
      config += line + "\n";
    }
    configFile.close();
    return config;
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    // close execution
    // NOTE: is really necessary exit the program?
    // how does it would work keeping this error?
    std::exit(EXIT_FAILURE);
  }
}

std::filesystem::path getPath() {
  // obtaining home path
  char *homeC = std::getenv("HOME");
  // in case env does not exist
  if (!homeC) {
    throw std::runtime_error("Error obtaining home directory");
  }
  std::filesystem::path homeDir = homeC;
  std::filesystem::path configDir = configPath;
  return homeDir / configDir;
}
} // namespace config
