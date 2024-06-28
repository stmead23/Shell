#include "shell.hpp"

int main() {
  bool is_exit = false;
  while (!is_exit) {
    ShellCommands current_command = getCommand();
    is_exit = execute_commands(current_command);
  }
  
  return 0;
}
