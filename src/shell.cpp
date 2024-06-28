#include "shell.hpp"
#include <type_traits>

ShellCommands::ShellCommands(std::string c, std::string v) : command_str(c), value(v) {
    if (c == "exit") {
        command = exit_val;
    } else if (c == "echo") {
        command = echo;
    } else if (c == "type") {
        std::cout << "Command " << c << " is type.\n";
        command = type;
    } else if (c == "pwd") {
        std::cout << "Command " << c << " is pwd.\n";
        command = pwd;
    } else {
        std::string path = get_path(c);
        if (!path.empty()) {
            command = exec;
        } else {
            command = invalid;
        }
    }
}

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

ShellCommands getCommand(void) {
    std::string input;
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::cout << "$ ";
    std::getline(std::cin, input);
    std::string command_type = input.substr(0, input.find(' '));
    std::string command_value = input.substr(input.find(' ')+1);
    ShellCommands new_command(command_type, command_value);
    return new_command;
}

bool execute_commands(ShellCommands current_command) {
    std::string path;
    switch (current_command.command) {
    case exit_val:
        return true;
    case echo:
        std::cout << current_command.value << "\n";
        return false;
    case type:
        if (current_command.value == "echo" || current_command.value == "exit" || current_command.value == "type") {
            std::cout << current_command.value << " is a shell builtin\n";
        } else {
            path = get_path(current_command.value);
            if(path.empty()){
                std::cout << current_command.value << ": not found\n";
            } else{
                std::cout << current_command.value << " is " << path << std::endl;
            }
        }
        return false;
    case exec:
        path = get_path(current_command.command_str) + " " + current_command.value;
        system(path.c_str());
        return false;
    case pwd:
        path = std::filesystem::current_path();
        std::cout << path << std::endl;
        return false;
    default:
        std::cout << current_command.command_str << ": command not found\n";
        return false;
    }
}