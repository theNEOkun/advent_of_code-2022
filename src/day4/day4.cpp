#include "day4.hpp"

void part1(std::vector<std::string> &file);

void day4::run() {
  std::cout << "DAY4" << std::endl;
  std::vector<std::string> file = readFile("./resources/input_day4");

  part1(file);
}

void part1(std::vector<std::string> &file) {
  int counter = 0;
  for (auto string : file) {
    auto first = string.substr(0, string.find(','));
    auto second = string.substr(string.find(',') + 1, string.length());

    auto first_1 = first.substr(0, first.find('-'));
    auto first_2 = first.substr(first.find('-') + 1, first.length());
    auto second_1 = second.substr(0, second.find('-'));
    auto second_2 = second.substr(second.find('-') + 1, second.length());
    int start = std::stoi(first_1);
    int stop = std::stoi(first_2);
    int start_i = std::stoi(second_1);
    int stop_i = std::stoi(second_2);

    if ((start <= start_i && stop >= stop_i) || (start_i <= start && stop_i >= stop)) {
      std::printf("%s - %s %s - %s <- this\n", first_1.c_str(), first_2.c_str(), second_1.c_str(), second_2.c_str());
      counter++;
    } else {
      std::printf("%s - %s %s - %s <- not this\n", first_1.c_str(), first_2.c_str(), second_1.c_str(), second_2.c_str());
    }
  }
  std::printf("Part1: %d\n", counter);
}
