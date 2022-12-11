#include "day11.hpp"
#include <functional>

namespace day11 {

  class Monkey {
    private:
      std::string name;
      std::vector<int> items;
      std::function<int(int, int)> operation;
      std::function<bool(int, int)> test;
    public:
    Monkey(std::vector<std::string> monkeyInfo) {
      utils::splitString(monkeyInfo[0]);
    }
  };

void part1();
void part2();

void run(utils utils) { std::printf("DAY11\n"); }

void part1() {}
void part2() {}
} // namespace day11
