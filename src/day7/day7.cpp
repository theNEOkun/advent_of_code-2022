#include "day7.hpp"

#include <map>

namespace day7 {

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run() {
  std::printf("DAY7\n");
  auto file = readFile("../resources/input_day7_examples");

  part1(file);
}

Info parseSingleCommand(std::string line) {
  auto listOfWords = getListOfWords(line, " ");
  // for (auto ach : listOfWords) {
  //   std::printf("%s\t", ach.c_str());
  // }
  // std::printf("size: %zu\n", listOfWords.size());
  if (listOfWords[0] == "$") {
    if (listOfWords.size() > 2)
      return Info(listOfWords[1], listOfWords[2]);
    else
      return Info(listOfWords[1], "");
  }
  if (listOfWords[0] == "dir") {
    return Info(listOfWords[1]);
  }
  try {
    int size = std::stol(listOfWords[0]);
    return Info(size, listOfWords[1]);
  } catch (std::invalid_argument const &) {
    return Info();
  }
  return Info();
}

const std::string topDir = "/";

struct Tree {
  Info info;
  Tree* parent;
  Tree* children[20];
  int size;
};

std::string handle_cd(std::map<std::string, std::string> &parents,
                      std::string current, Info command) {
  if (command.getInput() == "..") {
    return parents[current];
  }
  if (command.getInput() == "/") {
    return topDir;
  }
  auto get = command.getInput();
  parents[get] = current;
  return get;
}

void part1(std::vector<std::string> &file) {
  std::map<std::string, long> map;
  std::map<std::string, std::string> parents;
  std::map<std::string, std::vector<std::string>> children;
  parents[topDir] = " ";
  std::string currentDir;
  std::string current;
  long tally = 0;
  bool set = true;

  for (auto command_line : file) {
    Info command = parseSingleCommand(command_line);
    switch (command.getInfoType()) {
    case info_type::COMMAND:
      if (command.getCommand() == "cd") {
        if (set) {
          map[currentDir] = tally;
        }
        set = false;
        current = handle_cd(parents, current, command);
        currentDir = parents[current] + "/" + current;
      }
      if (command.getCommand() == "ls") {
        set = true;
        tally = 0;
        std::printf("\n%s: ", current.c_str());
      }
      break;
    case info_type::FILE:
      tally += command.getFileSize();
      std::printf("%s - %ld\t", command.getFileName().c_str(),
                  command.getFileSize());
      break;
    case info_type::DIRECTORY:
      std::printf("%s\t", command.getFileName().c_str());
      children[currentDir].push_back(command.getFileName());
      break;
    default:
      break;
    }
  }
  int counter = 0;
  for (const auto &[key, value] : map) {
    std::printf("%s - %ld\n", key.c_str(), value);
    if (value <= 100000)
      counter += value;
  }
  std::printf("Part 1: %d\n", counter);
}

void part2(std::vector<std::string> &file) {}
} // namespace day7
