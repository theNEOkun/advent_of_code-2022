#include "day10.hpp"
namespace day10 {

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run(utils utils) {
  std::printf("DAY10");
  std::vector<std::string> file = utils.readFile("input_day10");

  part1(file);
  part2(file);
}

enum ops { NOOP, ADD, FAIL };

ops getOps(std::string op) {
  if (op == "noop")
    return ops::NOOP;
  if (op == "addx")
    return ops::ADD;
  return ops::FAIL;
}

void part1(std::vector<std::string> &file) {
  int endcounter = 0;
  int next = 20;

  int X = 1;
  int cycles = 0;
  for (auto each : file) {
    int count = 0;
    std::vector<std::string> parts = utils::splitString(each, " ");

    int addToX = 0;
    switch (getOps(parts[0])) {
    case NOOP:
      count = 1;
      break;
    case ADD:
      addToX = std::stoi(parts[1]);
      count = 2;
      break;
    default:
      break;
    }

    for (int i = 0; i < count; i++) {
      cycles++;
      if (cycles == next) {
        endcounter += X * cycles;
        next += 40;
      }
    }
    X += addToX;
  }
  std::printf("Part 1: %d\n", endcounter);
}

char sprite(int X, int cycle) {
  if(X == cycle || (X - 1) == cycle || (X + 1) == cycle)
    return '#';
  return '.';
}

void part2(std::vector<std::string> &file) {
  int endcounter = 0;

  int X = 1;
  int cycles = 0;
  for (auto each : file) {
    int count = 0;
    std::vector<std::string> parts = utils::splitString(each, " ");

    int addToX = 0;
    switch (getOps(parts[0])) {
    case NOOP:
      count = 1;
      break;
    case ADD:
      addToX = std::stoi(parts[1]);
      count = 2;
      break;
    default:
      break;
    }

    for (int i = 0; i < count; i++) {
      std::cout << sprite(X, cycles);
      cycles++;
      if (cycles % 40 == 0) {
        std::cout << std::endl;
        cycles = 0;
      }
    }
    X += addToX;
  }
  std::printf("Part 2: %d\n", endcounter);
}
} // namespace day10
