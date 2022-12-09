#include "day9.hpp"
#include <cmath>
#include <set>
#include <utility>

#define DEBUG_START
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

std::pair<int, int>& operator+=(std::pair<int, int>& self, std::pair<int, int>& other) {
  self.first += other.first;
  self.second += other.second;
  return self;
}

class Rope {
private:
  std::pair<int, int> Head;
  std::pair<int, int> Tail;

  std::set<std::pair<int, int>> oldPos;

  void tailMove(std::pair<int, int> old) {
    int firstDiff = old.first - this->Tail.first;
    int secondDiff = old.second - this->Tail.second;
    if (std::abs(firstDiff) > 1 || std::abs(secondDiff) > 1) {
      int firstSign = firstDiff == 0 ? 0 : firstDiff / std::abs(firstDiff);
      int secondSign = secondDiff == 0 ? 0 : secondDiff / std::abs(secondDiff);

      auto nPair = std::make_pair(this->Tail.first + firstSign,
                                  this->Tail.second + secondSign);
      this->Tail = nPair;
      DEBUG("Tail: " << this->Tail)
      this->oldPos.insert(nPair);
    }
  }

  void headMove(std::pair<int, int> next) {
    auto old = this->Head;
    this->Head += next;
    DEBUG("Head: " << this->Head)
    tailMove(old);
  }

  void print() {
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 50; j++) {
        std::pair<int, int> npos = {i, j};
        if (this->Head == npos) {
          std::cout << "H";
          continue;
        }
        if (this->Tail == npos) {
          std::cout << "T";
          continue;
        }
        std::cout << ".";
      }
      std::cout << std::endl;
    }
  }

public:
  Rope() {
    this->Head = {0, 0};
    this->Tail = {0, 0};

    this->oldPos.insert(this->Tail);
  }

  void move(std::string movement) {
    int amount = movement[2] - '0';

    for (int i = 0; i < amount; i++) {
      switch (movement[0]) {
      case 'R':
        this->headMove(std::make_pair(1, 0));
        break;
      case 'L':
        this->headMove(std::make_pair(-1, 0));
        break;
      case 'D':
        this->headMove(std::make_pair(0, -1));
        break;
      case 'U':
        this->headMove(std::make_pair(0, 1));
        break;
      default:
        break;
      }
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
}

void part1(std::vector<std::string> &file) {
  Rope rope;
  for (auto each : file) {
    rope.move(each);
  }
#ifdef DEBUG_START_FULL
  auto pos = rope.getPositions();
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      std::pair<int, int> npos = {i, j};
      if (i == 0 && j == 0) {
        std::cout << "s";
        continue;
      }
      if (std::find(pos.begin(), pos.end(), npos) != pos.end()) {
        std::cout << "#";
        continue;
      }
      std::cout << ".";
    }
    std::cout << std::endl;
  }
  std::printf("Size: %zu\n", pos.size());
#endif
  std::printf("Part1: %lu\n", rope.getPositions().size());
}
void part2(std::vector<std::string> &file) {}
} // namespace day9
