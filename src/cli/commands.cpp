#include "cli/commands.h"
#include <cli11/CLI11.hpp>
#include <iostream>
#include <map>
#include <vector>

// constructor without args
Command::Command(CLI::App &app, std::string name, std::string description,
                 void (*func)(const std::map<std::string, std::string> &args),
                 const std::map<std::string, std::string> &options,
                 const bool &dynamicArgs)
    : app_(app), name_(std::move(name)), description_(std::move(description)),
      cmd_(app_.add_subcommand(name_, description_)), func_(func),
      options_(options), dynamicArgs_(dynamicArgs) {
  for (const auto &[key, val] : options_) {
    // saving values for dynamic args
    if (dynamicArgs_) {
      auto values = std::make_shared<std::vector<std::string>>();
      optionValues_[key] = values;
      cmd_->add_option(key, *values, val)->expected(-1);
    } else {
      // saving value without dynamic args
      auto value = std::make_shared<std::vector<std::string>>();
      value->emplace_back("");
      optionValues_[key] = value;
      cmd_->add_option(key, optionValues_[key]->front(), val);
    }
  }
}

// getName from name variable of class
const std::string &Command::getName() const { return name_; }

// getCmd value of class
const CLI::App &Command::getCmd() const { return *cmd_; }

// getArgs return a map with the commands avalaible and the value or values of
// the command given by user
std::map<std::string, std::string> Command::getArgs() const {
  std::map<std::string, std::string> args;
  for (const auto &[key, valuesPtr] : optionValues_) {
    const auto &values = *valuesPtr;
    if (dynamicArgs_) {
      std::string combinedValues;
      // saving every value of optionValues_
      for (const auto &val : values) {
        if (!combinedValues.empty()) {
          combinedValues += ",";
        }
        combinedValues += val;
      }
      args[key] = combinedValues;
    } else {
      args[key] = values.empty() ? "" : values.front();
    }
  }
  return args;
}

// printDescription
void Command::printDescription() const {
  std::cout << description_ << std::endl;
}
// exec function given as a constructor parameter
void Command::exec(const std::map<std::string, std::string> &args) const {
  func_(args);
}

// addCommand to class CommandRegisty
void CommandRegistry::addCommand(const Command command) {
  commands_.emplace_back(std::make_unique<Command>(std::move(command)));
}

// findCommand from CommandRegisty, returns a pointer of the command else
// nullptr
const Command *CommandRegistry::findCommand() {
  for (const auto &cmd : commands_) {
    const auto &subCmd = cmd->getCmd();
    if (subCmd.parsed()) {
      return cmd.get();
    }
  }
  return nullptr;
}
