#include "./day5.hpp"

namespace day5 {
void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

std::vector<std::vector<std::string>>
fix_crates(std::vector<std::string> &crate) {
  std::vector<std::vector<std::string>> all_crates;
  for (int i = 0; i < crate[0].size(); i += 4) {
    std::vector<std::string> inner_vec;
    for (int ii = 0; ii < crate.size(); ii++) {
      std::string str{crate[ii][i], crate[ii][i + 1], crate[ii][i + 2]};
      if(str == "   ") continue; // remove whitespace
      inner_vec.push_back(str);
    }
    all_crates.push_back(inner_vec);
  }

  // debug info

  // for (auto each : all_crates) {
  //   for (auto inner : each) {
  //     std::printf("%s\t", inner.c_str());
  //   }
  //   std::printf("\n");
  // }
  return all_crates;
}

std::vector<std::vector<int>> 
fix_directions(std::vector<std::string> &file) {
  std::vector<std::vector<int>> all_directions;

  for(auto each: file) {
    std::stringstream ss(each);
    std::string temp;
    std::vector<int> inner_vec;
    while(std::getline(ss, temp, ' ')) {
      try {
        auto in = std::stoi(temp);
        inner_vec.push_back(in);
      } catch(std::invalid_argument e) {
        continue;
      }
    }
    all_directions.push_back(inner_vec);
  }

  // debug info

  // for (auto each : all_directions) {
  //   for(int i: each) {
  //     std::printf("%d\t", i);
  //   }
  //   std::printf("\n");
  // }

  return all_directions;
}

void run() {
  std::cout << "DAY5" << std::endl;
  std::vector<std::string> incoming = readFile("../resources/input_day5");
  std::vector<std::string> crate(&incoming[0], &incoming[8]);
  std::vector<std::string> file(&incoming[10], &incoming[incoming.size()]);

  auto all_crates = fix_crates(crate);
  auto good_files = fix_directions(file);

  std::printf("%s\n", all_crates[7][0].c_str());

  std::printf("FILE:\n");


  day5::part1(file);
  day5::part2(file);
}

void part1(std::vector<std::string> &file) { return; }

void part2(std::vector<std::string> &file) { return; }
} // namespace day5
