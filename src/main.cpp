#include <iostream>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"
#include "day4/day4.hpp"
#include "day5/day5.hpp"
#include "day6/day6.hpp"
#include "day7/day7.hpp"
#include "day8/day8.hpp"
#include "day9/day9.hpp"
#include "day10/day10.hpp"
#include "day11/day11.hpp"
#include "day12/day12.hpp"
#include "day13/day13.hpp"

void line();

auto main(int argc, char *argv[]) -> int
{
  utils utils(argv[0]);
  // day1::run(utils); line();
  // day2::run(utils); line();
  // day3::run(utils); line();
  // day4::run(utils); line();
  // day5::run(utils); line();
  // day6::run(utils); line();
  // day7::run(utils); line();
  // day8::run(utils); line();
  // day9::run(utils); line();
  // day10::run(utils); line();
  // day11::run(utils); line();
  day12::run(utils); line();
  // day13::run(utils); line();
}

void line() {
  std::cout << "----------------------" << std::endl;
}
