#ifndef SHELL_HPP
#define SHELL_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

enum ShellValues {
    exit_val,
    echo,
    type,
    exec,
    invalid
};

struct ShellCommands {
    ShellValues command;
    std::string command_str;
    std::string value;
    ShellCommands(std::string c, std::string v);
};

std::string get_path(std::string command);
ShellCommands getCommand(void);
bool execute_commands(ShellCommands current_command);

#endif