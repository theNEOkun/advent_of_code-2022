#include "./day3.hpp"

namespace day3 {
void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

int part2_loop(std::vector<std::string> &file, int counter);
int innerLoop(std::string &each);

int get_val(char car) {
  if (car - 'A' < 27) {
    return (car - 'A') + 27;
  } else if (car - 'a' < 27) {
    return (car - 'a') + 1;
  }
  return -1;
}

void part1(std::vector<std::string> &file) {

  int sum = 0;
  for (auto each : file) {
    auto retval = innerLoop(each);
    if (retval == -1)
      throw;
    sum += retval;
  }
  std::cout << "part1: " << sum << std::endl;
}

void part2(std::vector<std::string> &file) {
  int sum = 0;
  for (size_t counter = 0; counter < file.size(); counter += 3) {
    auto retval = part2_loop(file, counter);
    if (retval == -1)
      throw;
    sum += retval;
  }
  std::cout << "part2: " << sum << std::endl;
}

int part2_loop(std::vector<std::string> &file, int counter) {
  for (auto first : file[counter]) {
    for (auto second : file[counter + 1]) {
      if (first == second) {
        for (auto third : file[counter + 2]) {
          if (first == third)
            return get_val(third);
        }
      }
    }
  }
  return -1;
}

void run(utils utils) {
  std::cout << "DAY3" << std::endl;
  std::vector<std::string> file = utils.readFile("resources/input_day3");
  part1(file);
  part2(file);
}

int innerLoop(std::string &each) {
  int sum = -1;
  auto len = (int)each.length();
  auto half = len >> 1;

  // For each in the first half
  for (int i = 0; i < half; i++) {
    char car = each[i];
    // For each in the second half
    for (int ii = half; ii < len; ii++) {
      char ocar = each[ii];
      if (car == ocar) {
        return get_val(car);
      }
    }
  }
  return sum;
}
} // namespace day3
