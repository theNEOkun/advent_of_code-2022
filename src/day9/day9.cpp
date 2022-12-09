#include "day9.hpp"
#include <cmath>
#include <set>
#include <utility>

// #define DEBUG_START
#ifdef DEBUG_START
#define DEBUG(x) std::cout << x << std::endl;
#endif
#ifndef DEBUG_START
#define DEBUG(x)
#endif

namespace day9 {

std::ostream &operator<<(std::ostream &Str, std::pair<int, int> const &f) {
  Str << "{ x: " << f.first << ", y: " << f.second << " }";
  return Str;
}

std::pair<int, int> operator+(std::pair<int, int> &self,
                              std::pair<int, int> &other) {
  return std::make_pair(self.first + other.first, self.second + other.second);
}

std::pair<int, int> operator+=(std::pair<int, int> &self,
                               std::pair<int, int> &other) {
  self.first += other.first;
  self.second += other.second;
  return self;
}

class Rope {
private:
  std::vector<std::pair<int, int>> rope;
  std::size_t size;

  std::set<std::pair<int, int>> oldPos;

  bool chebyshev(std::pair<int, int> first, std::pair<int, int> second) {
    return std::max(std::abs(first.first - second.first),
                    std::abs(first.second - second.second)) > 1;
  }

  void tailMove(std::pair<int, int> old) {
    auto prev = old;
    for (int i = 1; i < rope.size(); i++) {
      if (chebyshev(this->rope[i - 1], this->rope[i])) {
        DEBUG("before rope: " << *(this->rope.end() - 1) << " old: " << old)
        prev = this->rope[i];
        this->rope[i] = old;
        // if the position is not already in there
        DEBUG("after rope: " << *(this->rope.end() - 1)
                             << " head: " << *this->rope.begin())
      }
    }
    this->oldPos.insert(*(this->rope.end() - 1));
  }

  void headMove(std::pair<int, int> next) {
    auto old = *this->rope.begin();
    DEBUG("Head: " << *this->rope.begin())
    this->rope[0] += next;
    DEBUG("New Head: " << *this->rope.begin())
    tailMove(old);
  }

public:
  Rope(int size) : size(size), rope() {
    auto start = std::make_pair(0, 0);
    for (auto i = 0; i < size; i++) {
      this->rope.push_back(start);
    }
    std::printf("%zu\n", this->rope.size());
    // this->oldPos.insert(*this->rope.end());
  }

  std::pair<int, int> getNext(char move) {
    switch (move) {
    case 'R':
      return std::make_pair(0, 1);
      break;
    case 'D':
      return std::make_pair(-1, 0);
      break;
    case 'L':
      return std::make_pair(0, -1);
      break;
    case 'U':
      return std::make_pair(1, 0);
      break;
    default:
      break;
    }
    return std::make_pair(-10000, -10000);
  }

  void move(std::string movement) {
    int amount = std::stoi(&movement[2]);

    for (auto i = 0; i < amount; i++) {
      auto next = getNext(movement[0]);
      headMove(next);
    }
  }

  const std::set<std::pair<int, int>> &getPositions() const {
    return this->oldPos;
  }
};

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run() {
  std::printf("DAY9\n");
  auto file = readFile("../resources/input_day9");

  part1(file);
  part2(file);
}

void part1(std::vector<std::string> &file) {
  Rope rope(2);
  for (auto each : file) {
    rope.move(each);
  }
  std::printf("Part1: %lu\n", rope.getPositions().size());
}
void part2(std::vector<std::string> &file) {
  Rope rope(10);
  for (auto each : file) {
    rope.move(each);
  }
  std::printf("Part1: %lu\n", rope.getPositions().size());
}
} // namespace day9
