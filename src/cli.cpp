#include "actions/actions.h"
#include "cli/commands.h"
#include <cli11/CLI11.hpp>
#include <iostream>
#include <unordered_map>

static const char USAGE[] =
    R"(focuslock.
    usage:
      focuslock new-session [--name=<session_name>]
      focuslock set-session [--name=<session_name>]
      focuslock status
      focuslock (-h | --help)
      focuslock --version

    options:
      -h --help          show this screen.
      --version          show version.

      new-session        create a new session with default or customized settings
      --name=<session_name>     specify the session name (for new-session).

      set-session        set an existing session as the active session
      --name=<session_name>     name of an existing session.

    )";

bool hasParameter(const std::map<std::string, std::string> &args,
                  std::string parameter) {
  return args.find(parameter) != args.end() && !args.at(parameter).empty();
}
// commands

void newSession(const std::map<std::string, std::string> &args) {
  if (hasParameter(args, "--name")) {
    std::string output = actions::newSession(args.at("--name"));
    std::cout << output << std::endl;
  } else {
    std::cout << "name session not specified..." << std::endl;
  }
}

void setSession(const std::map<std::string, std::string> &args) {
  if (hasParameter(args, "--name")) {
    std::string output = actions::setSession(args.at("--name"));
    std::cout << output << std::endl;
  } else {
    std::cout << "name session not specified..." << std::endl;
  }
}

// TODO: consider deleteSessionc command

void status(const std::map<std::string, std::string> &args) {
  std::string output = actions::status(args.at("--session"));
  std::cout << output << std::endl;
}

void block(const std::map<std::string, std::string> &args) {
  std::unordered_map<std::string, std::string> validArgs;
  // if parameter is enabled
  if (hasParameter(args, "--enable")) {
    validArgs["--enable"] = args.at("--enable") == "true" ? 1 : 0;
  }
  // save only valid args
  for (auto [key, val] : args) {
    if (val != "") {
      if (key != "--enable") {
        validArgs[key] = val;
      }
    }
  }
  std::string output = actions::block(validArgs);
  std::cout << output << std::endl;
}

void pomodoro(const std::map<std::string, std::string> &args) {
  std::unordered_map<std::string, int> validArgs;
  // if parameter is enabled
  if (hasParameter(args, "--enable")) {
    validArgs["--enable"] = args.at("--enable") == "true" ? 1 : 0;
  }
  // save only valid args
  for (auto [key, val] : args) {
    if (val != "") {
      try {
        if (key != "--enable") {
          validArgs[key] = std::stoi(val);
        }
      } catch (const std::exception &e) {
        std::cerr << "error with arguments, try --help"
                     "pomodoro command. "
                  << e.what() << " (Exception Type: " << typeid(e).name() << ")"
                  << std::endl;
        std::exit(EXIT_FAILURE);
      }
    }
  }
  std::string output = actions::pomodoro(validArgs);
  std::cout << output << std::endl;
}

void start(const std::map<std::string, std::string> &args) { actions::start(); }

void stop(const std::map<std::string, std::string> &args) {}

void listSessions(const std::map<std::string, std::string> &args) {
  std::string sessions = actions::listSessions();
  std::cout << sessions << std::endl;
}

void enable(const std::map<std::string, std::string> &args) {
  for (const auto &[cmd, vals] : args) {
    std::cout << "command: " << cmd << ", values: " << vals << std::endl;
  }
}

void disable(const std::map<std::string, std::string> &args) {}

// createCommands saving them on registry variable
void createCommands(CommandRegistry &registry, CLI::App &app) {
  registry.addCommand(
      Command(app, "new-session",
              "create a new session for focuslock. You can customize the "
              "session later using other commands.",
              newSession, {{"--name", "name of the session to create"}}));

  registry.addCommand(
      Command(app, "set-session",
              "set the specified session as active. \n\t The active session "
              "will be used for future commands until changed.",
              setSession, {{"--name", "name of existing session"}}));

  registry.addCommand(Command(
      app, "status",
      "display the current status of focuslock, including the active "
      "session and the status of enabled modules or an specific session.",
      status, {{"--session", "name of an specific session"}}));

  registry.addCommand(
      // TODO: --list command needs a TEXT value to access to it
      Command(app, "block",
              "add, remove, or list blocked URLs and directories. \n\t Use "
              "subcommands to modify the block list.",
              block,
              {{"--add", "add a URL or directory to the block list"},
               {"--remove", "remove a URL or directory from the block list"},
               {"--list", "show all blocked items"}}));
  registry.addCommand(Command(
      app, "pomodoro",
      "control the Pomodoro module for timed work sessions. You can "
      "configure work and break durations or start/stop the timer.",
      pomodoro,
      {{"--enable", "set a boolean value to enable or disable pomodoro module"},
       {"--work", "set pomodoro work duration (minutes)"},
       {"--break", "set pomodoro break time duration (minutes)"},
       {"--long-break", "set pomodoro long break time duration (minutes)"},
       {"--cycles",
        "set the number of Pomodoro sessions before a long break"}}));
  registry.addCommand(
      Command(app, "list-sessions",
              "show a list of all sessions currently available in focuslock. "
              "This includes their names and status",
              listSessions));

  registry.addCommand(Command(
      app, "start",
      "start focuslock and activate the configured modules. If a "
      "session name "
      "is provided, switches to that session before starting",
      start,
      {{"--name", " name of an existing session to switch to before start"}}));
  registry.addCommand(Command(app, "stop", "reset any ongoing sessions", stop));
  registry.addCommand(Command(app, "enable",
                              "activate one or more modules for focuslock. "
                              "Modules must be specified by name",
                              enable, {{"--modules", "modules to enable"}},
                              true));
  registry.addCommand(Command(app, "disable",
                              "deactivate one or more modules for focuslock. "
                              "Modules must be specified by name",
                              disable, {{"--modules", "modules to enable"}},
                              true));
}

namespace cli {
// run_cli read arguments of program execution and handle them
int runCli(int argc, char *argv[]) {
  CLI::App app{"Focuslock CLI Application"};
  CommandRegistry registry;
  createCommands(registry, app);
  CLI11_PARSE(app, argc, argv);
  const Command *cmd = registry.findCommand();
  if (cmd) {
    cmd->exec(cmd->getArgs());
  } else {
    std::cout << "command not found" << std::endl;
  }
  return 0;
}

} // namespace cli
