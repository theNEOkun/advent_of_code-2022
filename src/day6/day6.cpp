#include "day6.hpp"

namespace day6{
void run() {
  std::cout << "DAY 1" << std::endl;
  std::vector<std::string> file = readFile("../resources/input_day1");
  std::vector<int> gnomes{0};
  int index = 0;

  for (auto each : file) {
    if (each.size() == 0) {
      gnomes.push_back(0);
      index++;
    } else {
      gnomes[index] += std::stoi(each);
    }
  }

  std::sort(gnomes.begin(), gnomes.end(), [](int &a, int &b){
      return a > b;
      });

  int largest = gnomes[0];

  std::cout << "Largest:" << largest << std::endl;

  std::cout << "Three largest: "<< gnomes[0] + gnomes[1] + gnomes[2] << std::endl;
}
}
