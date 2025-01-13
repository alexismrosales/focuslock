#pragma once
#include <cli11/CLI11.hpp>
#include <iostream>
#include <map>
#include <vector>
// command class for every command
class Command {
public:
  // constructor with args
  Command(CLI::App &app, std::string name, std::string description,
          void (*func)(const std::map<std::string, std::string> &args),
          const std::map<std::string, std::string> &options = {});

  // with const at the end to avoid variable modification
  const std::string &getName() const;
  std::map<std::string, std::string> getArgs() const;
  const CLI::App &getCmd() const;
  void printDescription() const;
  void exec(const std::map<std::string, std::string> &) const;

private:
  CLI::App &app_;
  std::string name_;        // command name
  std::string description_; // desc of the command
  std::map<std::string, std::string> options_;
  void (*func_)(const std::map<std::string, std::string>
                    &args); // pointer to the function
  std::map<std::string, std::string> optionValues_;
  CLI::App *cmd_;
};

class CommandRegistry {
public:
  void addCommand(const Command command);
  const Command *findCommand();
  void listCommands();

private:
  std::vector<std::unique_ptr<Command>> commands_;
};
