#include "cli/commands.h"
#include <cli11/CLI11.hpp>
#include <iostream>
#include <map>
#include <vector>

// constructor without args
Command::Command(CLI::App &app, std::string name, std::string description,
                 void (*func)(const std::map<std::string, std::string> &args),
                 const std::map<std::string, std::string> &options)
    : app_(app), name_(std::move(name)), description_(std::move(description)),
      func_(func), options_(options),
      cmd_(app_.add_subcommand(name_, description_)) {
  for (const auto &[key, val] : options_) {
    optionValues_[key] = "";
    cmd_->add_option(key, optionValues_[key], val);
  }
}

// getName from name variable of class
const std::string &Command::getName() const { return name_; }

const CLI::App &Command::getCmd() const { return *cmd_; }

std::map<std::string, std::string> Command::getArgs() const {
  std::map<std::string, std::string> updatedArgs;
  for (const auto &[key, _] : options_) {
    if (cmd_->count(key)) {
      updatedArgs[key] = cmd_->get_option(key)->as<std::string>();
    } else {
      updatedArgs[key] = "";
    }
  }
  return updatedArgs;
}

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
