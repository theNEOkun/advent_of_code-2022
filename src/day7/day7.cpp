#include "day7.hpp"

#include <map>

namespace day7 {

enum info_type { COMMAND, DIRECTORY, FILE, FAIL };
class info {

  std::string command;
  std::string command_part2;
  std::string fileName;
  long size;
  info_type what_command;

public:
  info(std::string incoming, std::string incoming_2) : command(incoming), command_part2(incoming_2), what_command(info_type::COMMAND) {
  }
  info(long size, std::string fileName) : size(size), fileName(fileName), what_command(info_type::FILE) {}
  info(std::string directory) : fileName(directory), what_command(info_type::DIRECTORY) {}
  info() : what_command(info_type::FAIL) {}

  info_type getCommand() {
    return this->what_command;
  }

  long getFileSize() {
    return this->size;
  }
};

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run() {
  std::printf("DAY7");
  auto file = readFile("../resources/input_day7");
}

info parseSingleCommand(std::string line) {
  auto listOfWords = getListOfWords(line, " ");
  if (listOfWords[0] == "$") {
    if(listOfWords.size() > 2)
      return info(listOfWords[1], listOfWords[2]);
    else
      return info(listOfWords[1], "");
  }
  if (listOfWords[0] == "dir") {
    return info(listOfWords[1]);
  }
  try {
    int size = std::stol(listOfWords[0]);
    return info(size, listOfWords[1]);
  } catch (std::invalid_argument e) {
    return info();
  }
  return info();
}

void part1(std::vector<std::string> &file) {
  std::map<std::string, long> map;
  std::string current;
  long tally = 0;
  for(auto each: file) {
    info command = parseSingleCommand(each);
    switch(command.getCommand()) {
      case info_type::DIRECTORY:
        break;
      case info_type::FILE:
        break;
      case info_type::COMMAND:
        break;
      default:
        break;
    }
  }
}

void part2(std::vector<std::string> &file) {}
} // namespace day7
