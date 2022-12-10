#include "./day5.hpp"

namespace day5 {

void part1(std::vector<std::vector<std::string>> crates,
           std::vector<std::vector<int>> directions);

void part2(std::vector<std::vector<std::string>> crates,
           std::vector<std::vector<int>> directions);

std::vector<std::vector<std::string>>
fix_crates(std::vector<std::string> &crate) {
  std::vector<std::vector<std::string>> all_crates;
  for (size_t i = 0; i < crate[0].size(); i += 4) {
    std::vector<std::string> inner_vec;
    for (size_t ii = 0; ii < crate.size(); ii++) {
      std::string str{crate[ii][i], crate[ii][i + 1], crate[ii][i + 2]};
      if (str == "   ")
        continue; // remove whitespace
      inner_vec.push_back(str);
    }
    all_crates.push_back(inner_vec);
  }

  // debug info

  // int counter = 0;
  // for (auto each : all_crates) {
  //   std::printf("%d ", counter);
  //   for (auto inner : each) {
  //     std::printf("%s\t", inner.c_str());
  //   }
  //   counter++;
  //   std::printf("\n");
  // }
  return all_crates;
}

std::vector<std::vector<int>> fix_directions(std::vector<std::string> &file) {
  std::vector<std::vector<int>> all_directions;

  for (auto each : file) {
    std::stringstream ss(each);
    std::string temp;
    std::vector<int> inner_vec;
    while (std::getline(ss, temp, ' ')) {
      try {
        auto in = std::stoi(temp);
        inner_vec.push_back(in);
      } catch (std::invalid_argument const&e) {
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

void run(utils utils) {
  std::cout << "DAY5" << std::endl;
  std::vector<std::string> incoming = utils.readFile("resources/input_day5");
  std::vector<std::string> crate(&incoming[0], &incoming[8]);
  std::vector<std::string> file(&incoming[10], &incoming[incoming.size()]);

  auto all_crates = fix_crates(crate);
  auto all_directions = fix_directions(file);

  day5::part1(all_crates, all_directions);
  day5::part2(all_crates, all_directions);
}

void part1(std::vector<std::vector<std::string>> crates,
           std::vector<std::vector<int>> directions) {
  std::printf("PART1\n");
  for (auto each : directions) {
    // std::printf("move %d @ %d to %d\n", each[0] - 1, each[1] - 1, each[2] -
    // 1);
    for (int i = 0; i < each[0]; i++) {
      auto crate = crates[each[1] - 1].front();
      // std::printf("move %s\n", crate.c_str());
      crates[each[1] - 1].erase(crates[each[1] - 1].begin());
      crates[each[2] - 1].insert(crates[each[2] - 1].begin(), crate);
    }
  }
  for (auto each : crates) {
    std::printf("%s\t", each[0].c_str());
  }
  std::printf("\n");
}

void part2(std::vector<std::vector<std::string>> crates,
           std::vector<std::vector<int>> directions) {
  std::printf("PART2\n");
  for (auto each : directions) {
    // std::printf("move %d @ %d to %d\n", each[0] - 1, each[1] - 1, each[2] -
    // 1);
    std::vector<std::string> temp;
    for (int i = 0; i < each[0]; i++) {
      auto crate = crates[each[1] - 1].front();
      // std::printf("move %s\n", crate.c_str());
      crates[each[1] - 1].erase(crates[each[1] - 1].begin());
      temp.insert(temp.begin(), crate);
    }
    for(auto crate: temp) {
      crates[each[2] - 1].insert(crates[each[2] - 1].begin(), crate);
    }
  }
  for (auto each : crates) {
    std::printf("%s\t", each[0].c_str());
  }
  std::printf("\n");
}
} // namespace day5
