#include "config/config.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace config {
void saveConfig(std::string configStr, std::string configPath,
                std::string fileName) {
  // TODO: duplication of getPath function call, can this be more efficient?
  // think that the function would be used in more than one method
  try {
    std::filesystem::path path = getPath(configPath) / "focuslock";
    // if directories of $HOME/.config/focuslock does not exist
    if (!std::filesystem::exists(path)) {
      std::filesystem::create_directories(path);
    }
    // 0755 permissions
    std::filesystem::permissions(path,
                                 std::filesystem::perms::owner_all |
                                     std::filesystem::perms::group_read |
                                     std::filesystem::perms::group_exec |
                                     std::filesystem::perms::others_read |
                                     std::filesystem::perms::others_exec,
                                 std::filesystem::perm_options::replace);
    std::filesystem::path fullPath = path / fileName;
    std::ofstream configFile(fullPath);
    if (!configFile.is_open()) {
      throw std::runtime_error("error obtaining file");
    }
    configFile << configStr;
    configFile.close();
  } catch (const std::exception &e) {
    std::cerr << "error writing sessions.yaml file: " << e.what()
              << " (Exception Type: " << typeid(e).name() << ")" << std::endl;

    // close execution
    // NOTE: is really necessary exit the program?
    // how does it would work keeping this error?
    std::exit(EXIT_FAILURE);
  }
}

std::string loadConfig(std::string configPath, std::string fileName) {
  try {
    std::filesystem::path path = getPath(configPath) / "focuslock";
    // if directories of $HOME/.config/focuslock does not exist
    if (!std::filesystem::exists(path)) {
      std::filesystem::create_directories(path);
    }
    // 0755 permissions
    std::filesystem::permissions(path,
                                 std::filesystem::perms::owner_all |
                                     std::filesystem::perms::group_read |
                                     std::filesystem::perms::group_exec |
                                     std::filesystem::perms::others_read |
                                     std::filesystem::perms::others_exec,
                                 std::filesystem::perm_options::replace);

    std::filesystem::path fullPath = path / fileName;
    std::string config = "";
    // if file of $HOME/.config/focuslock/sessions.yaml does not exist
    if (!std::filesystem::exists(fullPath)) {
      std::ofstream newConfigFile(fullPath);
    } else {
      // loading file
      std::ifstream configFile(fullPath);
      std::string line;
      // saving file into config string
      while (getline(configFile, line)) {
        config += line + "\n";
      }
      config.pop_back();
      configFile.close();
    }
    return config;

  } catch (const std::exception &e) {
    std::cerr << "error reading sessions.yaml file: " << e.what()
              << " (Exception Type: " << typeid(e).name() << ")" << std::endl;

    // close execution
    // NOTE: is really necessary exit the program?
    // how does it would work keeping this error?
    std::exit(EXIT_FAILURE);
  }
}

std::filesystem::path getPath(std::string configPath) {
  // obtaining home path
  char *homeC = std::getenv("HOME");
  // in case env does not exist
  if (!homeC) {
    throw std::runtime_error("error obtaining home directory");
  }
  std::filesystem::path homeDir = homeC;
  std::filesystem::path configDir = configPath;
  return homeDir / configDir;
}
} // namespace config
