#include "cli/commands.h"
#include <cli11/CLI11.hpp>
#include <iostream>

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

namespace cli {

void newSession(const std::map<std::string, std::string> &args) {
  if (args.find("--name") != args.end() && !args.at("--name").empty()) {
    std::cout << "creating new session: " << args.at("--name") << std::endl;
  } else {
    std::cout << "name session not specified..." << std::endl;
  }
}

void createCommands(CommandRegistry &registry, CLI::App &app) {
  registry.addCommand(Command(
      app, "new-session",
      "create a new session for focuslock. You can customize the session "
      "later using other commands.",
      newSession, {{"--name", "name of the session to create"}}));
}

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
