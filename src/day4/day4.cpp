#include "day4.hpp"

void part1();

void day4::run() {
  std::cout << "DAY4" << std::endl;
  std::vector<std::string> file = readFile("./resources/input_day4");
}

void part1(std::vector<std::string> &file) {
  for(auto string: file) {
    int comma = string.find(',');
    std::printf("%s, %c\n", string.c_str(), comma);
  }
}
