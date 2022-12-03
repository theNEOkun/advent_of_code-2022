#include "./day3.hpp"

int innerLoop(std::string each);

void day3::run() {
  std::cout << "DAY3" << std::endl;

  std::vector<std::string> file = readFile("./resources/input_day3");

  int sum = 0;
  for (auto each : file) {
    sum += innerLoop(each);
  }
  std::cout << sum << std::endl;
}

int innerLoop(std::string each) {
  int sum = 0;
  auto len = (int) each.length();
  auto half = len >> 1;
  std::map<char, int> map;
  for() {
    map[car] += 1;
    if(map[car] > 1) {
      if(car - 'A' < 27) {
        sum += (car - 'A') + 27;
      }
      sum += (car - 'a') + 1;
    }
  }
  return sum;
}
