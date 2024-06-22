#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // You can use print statements as follows for debugging, they'll be visible when running tests.
  //std::cout << "Logs from your program will appear here!\n";

  // Uncomment this block to pass the first stage
  std::cout << "$ ";
  std::string input;
  do {
    std::getline(std::cin, input);
    if (input.substr(0,4) == "exit") {
      break;
    }
    if (input.substr(0,4) == "echo") {
      input.erase(0,5);
      std::cout << input << "\n";
    } else if(input.substr(0,4) == "type") {
      input.erase(0,5);
      if (input == "echo" || input == "exit" || input == "type") {
        std::cout << input << " is a shell builtin\n";
      } else {
        std::string path_env = std::getenv("PATH");
        std::stringstream ss(path_env);
        std::string path;
        bool found = false;
        while (!ss.eof()) {
          getline(ss, path, ':');
          std::string abs_path = path + '/' + input;
          std::cout << abs_path << std::endl;
          if(std::filesystem::exists(abs_path)){
            std::cout << input << " is " << path << std::endl;
            found = true;
            break;
          }
        }
        if(!found) {
          std::cout << input << ": not found\n";
        }
      }
    } else {
      std::cout << input << ": command not found\n";
    }
    std::cout << "$ ";
  } while (true);

  return 0;
}
