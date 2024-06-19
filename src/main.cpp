#include <iostream>

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
    if (input == "exit 0") {
      break;
    }
    if (input.find("echo") != std::string::npos) {
      input.erase(0,5);
      std::cout << input << "\n";
    } else {
      std::cout << input << ": command not found\n";
    }
    std::cout << "$ ";
  } while (true);

  return 0;
}
