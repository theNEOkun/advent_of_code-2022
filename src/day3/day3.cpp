#include "./day3.hpp"

int innerLoop(std::string each);

void day3::run() {
  std::cout << "DAY3" << std::endl;

  std::vector<std::string> file = readFile("./resources/input_day3");

  int sum = 0;
  for (auto each : file) {
    auto retval = innerLoop(each);
    if(retval == -1)
      throw;
    std::printf(" %d\n", retval);
    sum += retval;
  }
  std::cout << sum << std::endl;
}

int innerLoop(std::string each) {
  int sum = -1;
  auto len = (int) each.length();
  auto half = len >> 1;
  // For each in the first half
  for(int i = 0; i < half; i++) {
    char car = each[i];
    // For each in the second half
    for(int ii = half + 1; ii < len; ii++) {
      char ocar = each[ii];
      if(car == ocar) {
        if(car - 'A' < 27) {
          std::printf("%c", car);
          return (car - 'A') + 27;
        } else
          if(car - 'a' < 27) {
            std::printf("%c", car);
            return (car - 'a') + 1;
          }
      }
    }
  }
  return sum;
}
