#include "day4.hpp"
#include <functional>

namespace day4 {
void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);
} // namespace day4

void day4::run(utils utils) {
  std::cout << "DAY4" << std::endl;
  std::vector<std::string> file = utils.readFile("resources/input_day4");

  part1(file);
  part2(file);
}

void getStrings(std::vector<std::string> &file,
                std::function<void(int, int, int, int)> func) {
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

    func(start, stop, start_i, stop_i);
  }
}

void day4::part1(std::vector<std::string> &file) {
  int counter = 0;
  getStrings(file, [&](int start, int stop, int start_i, int stop_i) {
    if ((start <= start_i && stop >= stop_i) ||
        (start_i <= start && stop_i >= stop)) {
      counter++;
    }
  });
  std::printf("Priorities: %d\n", counter);
}

void day4::part2(std::vector<std::string> &file) {
  int counter = 0;  
  getStrings(file, [&](int start, int stop, int start_i, int stop_i) {
    if ((start <= stop_i && start_i <= stop) ||
        (stop_i <= start && stop <= start_i)) {
      counter++;
    }
  });
  std::printf("Badges: %d\n", counter);
}
