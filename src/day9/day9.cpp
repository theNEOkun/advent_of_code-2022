#include "day9.hpp"
#include <cmath>
#include <set>

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

struct Pos {
  int x;
  int y;

  bool operator==(const Pos other) const {
    return other.x == this->x && other.y == this->y;
  }

  bool isHere(int i, int j) { return i == this->x && j == this->y; }

  friend std::ostream &operator<<(std::ostream &Str, const Pos &v);
};

std::ostream &operator<<(std::ostream &Str, const Pos &v) {
  Str << "{ x: " << v.x << ", y: " << v.y << " }";
  return Str;
}

class Rope {
private:
  Pos Head;
  Pos Tail;

  std::vector<Pos> oldPos;

  void tailMove(int x, int y) {
    if (std::max(std::abs(this->Head.x - this->Tail.x),
                 std::abs(this->Head.y - this->Tail.y)) > 1) {
      // if the position is not already in there

      DEBUG("Tail: " << this->Tail)
      this->Tail.x += x;
      this->Tail.y += y;

      // if (std::find(oldPos.begin(), oldPos.end(), this->Tail) == oldPos.end())
        this->oldPos.push_back(this->Tail);
    }
  }

  void headMove(int x, int y) {
    int oldx = this->Head.x;
    int oldy = this->Head.y;
    DEBUG("Head: " << this->Head)
    this->Head.x += x;
    this->Head.y += y;
    tailMove(x, y);
  }

  void print() {
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 50; j++) {
        if (this->Head.isHere(i, j)) {
          std::cout << "H";
          continue;
        }
        if (this->Tail.isHere(i, j)) {
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

    this->oldPos.push_back(this->Tail);
  }

  void move(std::string movement) {
    Dir direction = getDir(movement[0]);
    int amount = movement[2] - '0';

    for (int i = 0; i < amount; i++) {
      switch (direction) {
      case Dir::RIGHT:
        this->headMove(0, 1);
        break;
      case Dir::DOWN:
        this->headMove(-1, 0);
        break;
      case Dir::LEFT:
        this->headMove(0, -1);
        break;
      case Dir::UP:
        this->headMove(1, 0);
        break;
      default:
        break;
      }
    }
  }

  const std::vector<Pos> &getPositions() const { return this->oldPos; }
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
      Pos npos = {i, j};
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

  std::printf("Part 1: %zu\n", rope.getPositions().size());
}
void part2(std::vector<std::string> &file) {}
} // namespace day9
