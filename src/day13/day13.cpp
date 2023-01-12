#include "day13.hpp"
#include <algorithm>

namespace day13 {

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run(utils utils) {
  auto file = utils.readFile("input_day13_examples");

  part1(file);
}

void part1(std::vector<std::string> &file) {
  for(int i = 0; i < file.size(); i += 3) {
    auto first = utils::splitString(file[i], ",");
    auto second = utils::splitString(file[i + 1], ",");

    for(int j = 0; j < std::min(first.size(), second.size()); j++) {
      if(std::stoi(first[j]) < std::stoi(second[j]))
        return;
      std::cout << first[j] << " " << second[j] << std::endl;
    }

  }
}
void part2(std::vector<std::string> &file) {}
} // namespace day1
