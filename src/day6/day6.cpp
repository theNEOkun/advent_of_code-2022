#include "day6.hpp"

namespace day6 {

void part1(std::string arr);
void part2(std::string arr);

void run(utils utils) {
  std::printf("DAY6\n");
  auto file = utils.readFile("input_day6");
  std::string str = file[0];
  part1(str);
  part2(str);
}

int getInfo(std::string arr, int length) {
  int counter = 0;
  for (int i = 0; i < arr.length(); i++) {
    counter++;
    std::set<char> temp;
    for(int n = 0; n < length; n++)
      temp.insert(arr[i + n]);
    if (temp.size() == length) {
      counter += length - 1;
      // for (auto each : temp)
      //   std::printf("%c\n", each);
      return counter;
    }
  }
  return -1;
}

void part1(std::string arr) {
  auto resp = getInfo(arr, 4);
  if(resp == -1) throw;
  std::printf("Part1: %d\n", resp);
}

void part2(std::string arr) {
  auto resp = getInfo(arr, 14);
  if(resp == -1) throw;
  std::printf("Part 2: %d\n", resp);
}
} // namespace day6
