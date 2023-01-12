#include "day12.hpp"
#include <cassert>
#include <functional>
#include <optional>
#include <queue>
#include <set>
#include <unordered_set>

#define row first
#define col second

namespace day12 {
class Node {
  std::pair<int, int> position;
  char elevation;
  int g_score;

public:
  Node() : position(std::make_pair(-1, -1)), elevation('!'), g_score(0) {}
  Node(std::pair<int, int> position, char elevation)
      : position(position), elevation(elevation), g_score(0) {}
  Node(int row, int col, char elevation)
      : position(std::make_pair(row, col)), elevation(elevation), g_score(0) {}
  Node(std::pair<int, int> position, char elevation, int g_score)
      : position(position), elevation(elevation), g_score(g_score) {}

  const std::pair<int, int> getPos() const { return this->position; }

  const char getElev() const { return this->elevation; }

  Node setGScore(const int score) {
    this->g_score = score;
    return *this;
  }

  int getGScore() { return this->g_score; }

  bool empty() const {
    return this->position.row == -1 && this->position.col == -1 &&
           this->elevation == '!';
  }

  bool operator==(const Node &other) const {
    return this->position.row == other.position.row &&
           this->position.col == other.position.col;
  }

  bool operator<(const Node &other) const {
    return this->g_score < other.g_score;
  }

  bool operator>(const Node &other) const {
    return this->g_score > other.g_score;
  }

  size_t getHash() const {
    return std::hash<size_t>()(elevation + position.row + position.second);
  }

  std::size_t operator()() const {
    return std::hash<size_t>()(elevation + position.row + position.second);
  }

  void print() {
    std::printf("( %d, %d ) - %c \n", this->position.row, this->position.second,
                this->elevation);
  }
};

struct node_hasher {
  size_t operator()(const Node &e) const {
    size_t hash_result = 0;
    hash_result += e.getElev() * 31;
    auto pos = e.getPos();
    hash_result += pos.row * 32;
    hash_result += pos.col * 33;
    // calculate the hash result
    return hash_result;
  }
};

void part1(std::vector<std::string> &file, Node start, Node end);
void part2(std::vector<std::string> &file, Node start, Node end);

void run(utils utils) {
  std::printf("DAY12\n");
  auto file = utils.readFile("input_day12");

  Node start;
  Node end;
  for (int row = 0; row < file.size(); row++) {
    for (int col = 0; col < file[row].size(); col++) {
      if (start.empty() && file[row][col] == 'S') {
        start = Node(row, col, 'a');
      }
      if (end.empty() && file[row][col] == 'E') {
        end = Node(row, col, 'z');
      }
    }
    if (!start.empty() && !end.empty()) {
      break;
    }
  }
  part1(file, start, end);
  part2(file, start, end);
}

template <class T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class MyQueue : public std::priority_queue<T, Container, Compare> {
public:
  typedef typename std::priority_queue<
      T, Container, Compare>::container_type::const_iterator const_iterator;

  const_iterator find(const T &val) const {
    auto row = this->c.cbegin();
    auto last = this->c.cend();
    while (row != last) {
      if (*row == val)
        return row;
      ++row;
    }
    return last;
  }

  const bool contains(const T &val) const {
    return this->find(val) != this->c.cend();
  }

  bool eraseNode(const T &value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);

    if (it == this->c.end()) {
      return false;
    }
    if (it == this->c.begin()) {
      // deque the top element
      this->pop();
    } else {
      // remove element and re-heap
      this->c.erase(it);
      std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
    return true;
  }
};

class AStar {
  std::vector<std::string> map;
  int linelength;
  int height;
  Node start;
  Node end;

  std::pair<int, int> indexOut(int index) {
    return std::make_pair(index / linelength, index % linelength);
  }

  int indexIn(int row, int col) { return row * linelength + col; }

  int indexIn(std::pair<int, int> current) {
    return current.row * linelength + current.col;
  }

  std::vector<Node> getNeighbours(std::pair<int, int> current) {
    std::vector<Node> retVec;
    if ((current.row + 1) < height) {
      retVec.push_back(getFromMap(current.row + 1, current.col));
    }
    if ((current.row - 1) >= 0) {
      retVec.push_back(getFromMap(current.row - 1, current.col));
    }
    if ((current.col + 1) < linelength) {
      retVec.push_back(getFromMap(current.row, current.col + 1));
    }
    if ((current.col - 1) >= 0) {
      retVec.push_back(getFromMap(current.row, current.col - 1));
    }
    return retVec;
  }

  std::vector<Node> getSuccessors(Node node) {
    std::vector<Node> retVec;
    for (auto each : this->getNeighbours(node.getPos())) {
      if (each.getElev() == (node.getElev() + 1) ||
          each.getElev() <= node.getElev()) {
        retVec.push_back(each.setGScore(node.getGScore() + 1));
      }
    }
    return retVec;
  }

public:
  AStar(std::vector<std::string> mapString, Node start, Node end)
      : map(mapString), linelength(mapString[0].size()),
        start(start.getPos(), start.getElev(), 0),
        end(end.getPos(), end.getElev()) {
    this->height = mapString.size();
  }

  Node getFromMap(std::pair<int, int> current) {
    if (current == start.getPos())
      return start;
    if (current == end.getPos())
      return end;
    return Node(current, map[current.row][current.col]);
  }

  Node getFromMap(int row, int col) {
    const auto pos = std::make_pair(row, col);
    if (pos == start.getPos())
      return start;
    if (pos == end.getPos())
      return end;
    return Node(pos, map[row][col]);
  }

  std::optional<Node> astar() {
    MyQueue<Node, std::vector<Node>, std::greater<Node>> frontier;
    std::unordered_set<Node, node_hasher> explored;

    frontier.push(this->start);

    while (!frontier.empty()) {
      Node current = frontier.top();
      frontier.pop();

      if (current == this->end) {
        return std::make_optional(current);
      }

      explored.insert(current);

      for (Node successor : getSuccessors(current)) {
        if (explored.count(successor) == 0 && !frontier.contains(successor)) {
          frontier.push(successor);
          continue;
        }

        bool hasErased = false;
        Node prev = *frontier.find(successor);
        if (prev == successor && successor.getGScore() < prev.getGScore()) {
          hasErased = frontier.eraseNode(prev);
        }
        if (hasErased) {
          frontier.push(successor);
        }
      }
    }
    return {};
  }
};

void part1(std::vector<std::string> &file, Node start, Node end) {
  AStar astar(file, start, end);
  auto result = astar.astar();
  std::printf("part 1: %d\n", result.value().getGScore());
}

void part2(std::vector<std::string> &file, Node start, Node end) {
  std::vector<Node> nodevec;
  for(int row = 0; row < file.size(); row++) {
    for(int col = 0; col < file[row].size(); col++) {
      if(file[row][col] == 'a') {
        nodevec.push_back(Node(std::make_pair(row, col), 'a'));
      }
    }
  }
  std::vector<std::pair<int, Node>> resultvec;
  for(auto startpos: nodevec) {
    AStar astar(file, startpos, end);
    auto result = astar.astar();
    if(result.has_value())
      resultvec.push_back(std::make_pair(result.value().getGScore(), startpos));
  }

  std::sort(resultvec.begin(), resultvec.end(), [](auto a, auto b) { return a.first < b.first; });

  std::printf("part2: %d\n", resultvec[0].first);
}
} // namespace day12
