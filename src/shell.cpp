#include "shell.hpp"
#include <type_traits>

// Breaks down command into command type and necessary 
// values for the command to run properly. Retains the 
// name of the command if it is needed.
ShellCommands::ShellCommands(std::string c, std::string v) : command_str(c), value(v) {
    if (c == "exit") {
        command = exit_val;
    } else if (c == "echo") {
        command = echo;
    } else if (c == "type") {
        command = type;
    } else if (c == "pwd") {
        command = pwd;
    } else if (c == "cd") {
        command = cd;
    } else {
        std::string path = get_path(c);
        if (!path.empty()) {
            command = exec;
        } else {
            command = invalid;
        }
    }
}

// Returns a file path as a string value. If none exists, 
// returns an empty string.
std::string get_path(std::string command){
    std::string path_env = std::getenv("PATH");
    std::stringstream ss(path_env);
    std::string path;
    while(!ss.eof()){
        getline(ss, path, ':');
        std::string abs_path = path + '/' + command;
        if(std::filesystem::exists(abs_path)){
            return abs_path;
        }
    }
    return "";  
}

// Sets up and receives the next command, then returns the
// formatted command struct.
ShellCommands getCommand(void) {
    std::string input;
    // Clears flags for command line and errors
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";
    std::getline(std::cin, input);

    // Divide entered command into the command type and
    // values necessary for the command to run, and create
    // new command data structure
    std::string command_type = input.substr(0, input.find(' '));
    std::string command_value = input.substr(input.find(' ')+1);

    ShellCommands new_command(command_type, command_value);
    return new_command;
}

// Responsible for running the provided command. Returns true
// if the "exit" command was invoked, otherwise returns false.
bool execute_commands(ShellCommands current_command) {
    std::string path;
    switch (current_command.command) {
    // Exits the shell. Returns true to close program
    case exit_val:
        return true;
    // Prints the following string
    case echo:
        std::cout << current_command.value << "\n";
        return false;
    // Returns data about the command that follows the "type"
    // command. Lets user know if it is a builtin shell command
    // or it's location if it is an executable file. Returns 
    // "not found" if neither
    case type:
        if (current_command.value == "echo" || current_command.value == "exit" || current_command.value == "type" || current_command.value == "pwd" || current_command.value == "cd") {
            std::cout << current_command.value << " is a shell builtin\n";
        } else {
            // Searches for file described by command input. Returns
            // file path if executable found, otherwise returns empty
            // string.
            path = get_path(current_command.value);
            if(path.empty()){
                std::cout << current_command.value << ": not found\n";
            } else{
                std::cout << current_command.value << " is " << path << std::endl;
            }
        }
        return false;
    // Searches for executable to run.
    case exec:
        path = get_path(current_command.command_str) + " " + current_command.value;
        system(path.c_str());
        return false;
    // Prints out the current directory path.
    case pwd:
        path = std::filesystem::current_path();
        std::cout << path << std::endl;
        return false;
    // Changes current directory. If input is "~", return to home
    // directory. Else try to redirect to the directory listed. If 
    // directory doesn't exist, inform user. 
    case cd:
        if (current_command.value == "~") {
            std::filesystem::current_path(std::getenv("HOME"));
            return false;
        }
        try {
            std::filesystem::current_path(current_command.value);
        } catch(std::filesystem::filesystem_error const& e) {
            std::cout << "cd: " << current_command.value << ": No such file or directory\n";
        }
        return false;
    // Invalid command used.
    default:
        std::cout << current_command.command_str << ": command not found\n";
        return false;
    }
}