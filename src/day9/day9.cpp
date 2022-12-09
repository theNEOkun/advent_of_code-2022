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

enum Dir { RIGHT, DOWN, LEFT, UP, FAIL };

Dir getDir(char direction) {
  if (direction == 'R')
    return Dir::RIGHT;
  if (direction == 'L')
    return Dir::LEFT;
  if (direction == 'U')
    return Dir::UP;
  if (direction == 'D')
    return Dir::DOWN;
  return Dir::FAIL;
}

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

  void print() {
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 50; j++) {
        std::pair<int, int> npos = { i, j };
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
    Dir direction = getDir(movement[0]);
    int amount = std::stoi(&movement[2]);

    for (int i = 0; i < amount; i++) {
      switch (direction) {
      case Dir::RIGHT:
        this->headMove(std::make_pair(0, 1));
        break;
      case Dir::DOWN:
        this->headMove(std::make_pair(-1, 0));
        break;
      case Dir::LEFT:
        this->headMove(std::make_pair(0, -1));
        break;
      case Dir::UP:
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
