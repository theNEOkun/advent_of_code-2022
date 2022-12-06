#include <iostream>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"
#include "day4/day4.hpp"
#include "day5/day5.hpp"
#include "day6/day6.hpp"

void line();

auto main(int argc, char *argv[]) -> int
{
  day1::run();
  line();
  day2::run();
  line();
  day3::run();
  line();
  day4::run();
  line();
  day5::run();
  line();
  day6::run();
  line();
}

void line() {
  std::cout << "----------------------" << std::endl;
}
