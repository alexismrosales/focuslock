#include <docopt/docopt.h>
#include <iostream>

// Definición del mensaje de uso para docopt
static const char USAGE[] =
    R"(Focuslock CLI Application.
    Usage:
      focuslock --name=<name> [--greet]
      focuslock (-h | --help)
      focuslock --version

    Options:
      -h --help          Show this screen.
      --version          Show version.
      --name=<name>      Specify a name.
      --greet            Print a greeting message.
    )";

namespace cli {

int run_cli(int argc, char *argv[]) {
  // Analizar los argumentos con docopt
  std::map<std::string, docopt::value> args =
      docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "Focuslock 0.0.1");

  // Mostrar los argumentos analizados
  std::cout << "Parsed arguments:" << std::endl;
  for (const auto &arg : args) {
    std::cout << arg.first << ": " << arg.second << std::endl;
  }

  // Lógica de ejemplo
  if (args["--greet"].asBool() && args["--name"]) {
    std::cout << "Hello, " << args["--name"].asString() << "!" << std::endl;
  }

  return 0;
}

} // namespace cli
