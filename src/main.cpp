#include <iostream>

#include "day1/day1.hpp"
#include "day2/day2.hpp"

void line();

auto main(int argc, char *argv[]) -> int
{
  day1::run();
  line();
  day2::run();
  line();
}

void line() {
  std::cout << "----------------------" << std::endl;
}
