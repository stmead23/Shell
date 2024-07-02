#include "shell.hpp"

int main() {
  // While the exit command hasn't been run, ask
  // for a new command and proceed to run
  bool is_exit = false;
  while (!is_exit) {
    ShellCommands current_command = getCommand();
    is_exit = execute_commands(current_command);
  }
  
  return 0;
}
