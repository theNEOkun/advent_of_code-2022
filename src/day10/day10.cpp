#include "day10.hpp"
namespace day10 {

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run(utils utils) {
  std::vector<std::string> file = utils.readFile("resources/input_day10");
  
  part1(file);
}

enum ops { NOOP, ADD, FAIL };

ops getOps(std::string op){
  if(op == "noop")
    return ops::NOOP;
  if(op == "addx")
    return ops::ADD;
  return ops::FAIL;
}

void part1(std::vector<std::string> &file) {
  int endcounter = 0;
  int next = 20;

  int X = 1;
  int cycles = 0;
  for(auto each: file) {
    int count = 0;
    std::vector<std::string> parts = utils::splitString(each, " ");

    int addToX = 0;
    switch(getOps(parts[0])) {
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

    for(int i = 0; i < count; i++) {
      cycles++;
      if(cycles == next) {
        std::printf("%d - %d\n", X, cycles);
        endcounter += X * cycles;
        next += 40;
      }
    }
    X += addToX;
  }
  std::printf("%d\n", endcounter);
}
void part2(std::vector<std::string> &file) {}
} // namespace day10
