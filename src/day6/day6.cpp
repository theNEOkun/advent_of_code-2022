#include "day6.hpp"

namespace day6{

void part1(std::string arr);
void part2(std::string arr);
  
void run() {
  auto file = readFile("../resources/input_day6");
  std::string str = file[0];
  part1(str);
}

void part1(std::string arr) {
  int counter = 0;
  std::vector<char> temp;
  for(int i = 0; i < arr.length(); i++) {
    counter++;
    std::set<char> temp;
    temp.insert(arr[i]);
    temp.insert(arr[i + 1]);
    temp.insert(arr[i + 2]);
    temp.insert(arr[i + 3]);
    if(temp.size() == 4) {
      counter += 3;
      for(auto each: temp)
        std::printf("%c\n", each);
      break;
    }
  }
  std::printf("%d\n", counter);
}

void part2(std::string arr) {

}
}
