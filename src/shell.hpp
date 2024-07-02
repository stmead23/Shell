#ifndef SHELL_HPP
#define SHELL_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

// Values for all possible commands
enum ShellValues {
    exit_val,
    echo,
    type,
    exec,
    pwd,
    cd,
    invalid
};

// Data struct for each shell command. Breaks down command into
// command type and necessary values for the command to run 
// properly. Retains the name of the command if it is needed.
struct ShellCommands {
    // Enum for interpreting each command
    ShellValues command;
    std::string command_str;
    std::string value;
    // Constructor
    ShellCommands(std::string c, std::string v);
};

// Returns a file path as a string value. If none exists, 
// returns an empty string.
std::string get_path(std::string command);
// Sets up and receives the next command, then returns the
// formatted command struct.
ShellCommands getCommand(void);
// Responsible for running the provided command. Returns true
// if the "exit" command was invoked, otherwise returns false.
bool execute_commands(ShellCommands current_command);

#endif