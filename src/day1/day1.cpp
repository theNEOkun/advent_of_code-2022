#include "day1.hpp"

int day1::run() {
  std::cout << "Hello from day1" << std::endl;
  std::vector<std::string> file = readFile("./src/day1/input");
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

  std::cout << gnomes[0] + gnomes[1] + gnomes[2] << std::endl;

  return largest;
}
