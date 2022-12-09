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

std::ostream& operator<<(std::ostream& Str, std::pair<int, int> const& f) {
  Str << "{ x: " << f.first << ", y: " << f.second << " }";
  return Str;
}

std::pair<int, int> operator+(std::pair<int, int> &self, std::pair<int, int> &other) {
  return std::make_pair(self.first + other.first, self.second + other.second);
}

std::pair<int, int> operator+=(std::pair<int, int> &self, std::pair<int, int> &other) {
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
    if (std::max(std::abs(this->Head.first - this->Tail.first),
                 std::abs(this->Head.second - this->Tail.second)) > 1) {
      // if the position is not already in there

      DEBUG("Tail: " << this->Tail)
      this->Tail = old;
      this->oldPos.insert(this->Tail);
    }
  }

  void headMove(std::pair<int, int> next) {
    auto old = this->Head;
    DEBUG("Head: " << this->Head)
    this->Head += next;
    tailMove(old);
  }

public:
  Rope() {
    this->Head = {0, 0};
    this->Tail = {0, 0};

    this->oldPos.insert(this->Tail);
  }

  void move(std::string movement) {
    int amount = std::stoi(&movement[2]);

    for (int i = 0; i < amount; i++) {
      switch (movement[0]) {
      case 'R':
        this->headMove(std::make_pair(0, 1));
        break;
      case 'D':
        this->headMove(std::make_pair(-1, 0));
        break;
      case 'L':
        this->headMove(std::make_pair(0, -1));
        break;
      case 'U':
        this->headMove(std::make_pair(1, 0));
        break;
      default:
        break;
      }
    }
  }

  const std::set<std::pair<int, int>> &getPositions() const { return this->oldPos; }
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
  std::printf("Part1: %lu\n", rope.getPositions().size());
}
void part2(std::vector<std::string> &file) {}
} // namespace day9
