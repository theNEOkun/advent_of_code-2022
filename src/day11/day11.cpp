#include "day11.hpp"
#include <cassert>
#include <deque>
#include <functional>

#define DEBUG_PRINT

#ifdef DEBUG_PRINT
#define DEBUG(x) std::cout << x << std::endl;
#endif
#ifdef DEBUG_PRINT
#define DEBUG_LIST(x)                                                          \
  for (auto each : x)                                                          \
    std::cout << each << std::endl;
#endif
#ifndef DEBUG_PRINT
#define DEBUG(x)
#endif
#ifndef DEBUG_PRINT
#define DEBUG_LIST(x)
#endif

namespace day11 {

std::function<uint64_t(uint64_t, uint64_t)>
makeOperation(std::vector<std::string> operations) {
  if (operations[2] == "old") {
    if (operations[1] == "*") {
      return
          [](uint64_t old1, uint64_t old2) -> uint64_t { return old1 * old2; };
    }
    if (operations[1] == "+")
      return
          [](uint64_t old1, uint64_t old2) -> uint64_t { return old1 + old2; };
  }
  if (operations[1] == "*")
    return [=](uint64_t old1, uint64_t old2) -> uint64_t {
      return old1 * std::stoi(operations[2]);
    };
  else
    return [=](uint64_t old1, uint64_t old2) -> uint64_t {
      return old1 + std::stoi(operations[2]);
    };
}

std::function<uint64_t(uint64_t)> makeTest(uint64_t test, uint64_t trueMonkey,
                                           uint64_t falseMonkey) {
  return [=](uint64_t testnum) -> uint64_t {
    return (testnum % test == 0) ? trueMonkey : falseMonkey;
  };
}

class Monkey {
private:
  int name;
  std::deque<uint64_t> items;
  std::function<uint64_t(uint64_t, uint64_t)> operation;
  int test;
  int trueMonkey;
  int falseMonkey;
  int inspections = 0;

public:
  Monkey(std::vector<std::string> monkeyInfo) {
    auto nameRow = utils::splitString(monkeyInfo[0]);
    name = std::stoi(nameRow[1]);

    auto itemRow = utils::splitString(monkeyInfo[1], ": ");
    auto itemList = utils::splitString(itemRow[1], ", ");
    for (auto each : itemList) {
      items.push_back(std::stoi(each));
    }

    auto operationRow = utils::splitString(monkeyInfo[2], ": ");
    auto operations =
        utils::splitString(utils::splitString(operationRow[1], " = ")[1]);
    operation = makeOperation(operations);

    test = std::stoi(utils::splitString(monkeyInfo[3]).back());
    trueMonkey = std::stoi(utils::splitString(monkeyInfo[4]).back());
    falseMonkey = std::stoi(utils::splitString(monkeyInfo[5]).back());
  }

  const int getName() const { return name; }

  const int getTest() const { return test; }

  void recieveItem(uint64_t item) { items.push_back(item); }

  const uint64_t throwItem(bool managed) {
    inspections++;
    uint64_t item = items.front();
    items.pop_front();
    uint64_t retVal = operation(item, item);
    if (!managed) {
      retVal /= 3;
    }
    return retVal;
  }

  uint64_t toMonkey(uint64_t item) { return (item % test == 0)? trueMonkey: falseMonkey; }

  const std::deque<uint64_t> &getItems() const { return items; }

  bool hasItems() const { return !items.empty(); }

  const uint64_t getInsp() const { return inspections; }

  void print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Items: ";
    for (auto each : getItems()) {
      std::cout << each << ", ";
    }
    std::cout << std::endl;
  }

  bool operator<(Monkey &other) { return inspections < other.inspections; }
  bool operator>(Monkey &other) { return inspections > other.inspections; }
};

void part1(std::vector<Monkey> monkeyList);
void part2(std::vector<Monkey> monkeyList);

void run(utils utils) {
  std::printf("DAY11\n");
  auto file = utils.readFile("input_day11");
  std::vector<Monkey> monkeyList;
  for (auto i = 0; i < file.size(); i += 7) {
    std::vector<std::string> range;
    for (uint64_t j = 0; j < 6; j++)
      range.push_back(file[i + j]);
    Monkey temp{range};
    monkeyList.push_back(temp);
  }
  part1(monkeyList);
  part2(monkeyList);
}

void part1(std::vector<Monkey> monkeyList) {
  for (int i = 0; i < 20; i++) {
    for (auto &monkey : monkeyList) {
      while (monkey.hasItems()) {
        uint64_t nItem = monkey.throwItem(false);
        uint64_t toMonk = monkey.toMonkey(nItem);
        monkeyList[toMonk].recieveItem(nItem);
      }
    }
  }

  std::sort(monkeyList.begin(), monkeyList.end(),
            [](auto a, auto b) { return a > b; });
  std::printf("part1: %lu\n",
              monkeyList[0].getInsp() * monkeyList[1].getInsp());
}

void part2(std::vector<Monkey> monkeyList) {
  int testNum = 1;
  for(auto each: monkeyList){
    testNum *= each.getTest();
  }
  for (int i = 0; i < 10000; i++) {
    for (auto &monkey : monkeyList) {
      while (monkey.hasItems()) {
        uint64_t nItem = monkey.throwItem(true) % testNum;
        uint64_t toMonk = monkey.toMonkey(nItem);
        monkeyList[toMonk].recieveItem(nItem);
      }
    }
  }

  std::sort(monkeyList.begin(), monkeyList.end(),
            [](auto a, auto b) { return a > b; });
  std::printf("part2: %lu\n",
              monkeyList[0].getInsp() * monkeyList[1].getInsp());
}
} // namespace day11
