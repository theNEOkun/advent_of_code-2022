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

std::function<int(int, int)>
makeOperation(std::vector<std::string> operations) {
  if (operations[2] == "old") {
    if (operations[1] == "*") {
      return [](int old1, int old2) -> int { return old1 * old2; };
    }
    if (operations[1] == "+")
      return [](int old1, int old2) -> int { return old1 + old2; };
  }
  if (operations[1] == "*")
    return [=](int old1, int old2) -> int {
      return old1 * std::stoi(operations[2]);
    };
  else
    return [=](int old1, int old2) -> int {
      return old1 + std::stoi(operations[2]);
    };
}

std::function<int(int)> makeTest(int test, int trueMonkey, int falseMonkey) {
  return [=](int testnum) -> int {
    return (testnum % test == 0) ? trueMonkey : falseMonkey;
  };
}

class Monkey {
private:
  int name;
  std::deque<int> items;
  std::function<int(int, int)> operation;
  std::function<int(int)> test;
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

    auto testNum = utils::splitString(monkeyInfo[3]).back();
    auto trueMonkey = utils::splitString(monkeyInfo[4]).back();
    auto falseMonkey = utils::splitString(monkeyInfo[5]).back();
    test = makeTest(std::stoi(testNum), std::stoi(trueMonkey),
                    std::stoi(falseMonkey));
  }

  const int getName() const { return name; }

  void recieveItem(int item) { items.push_back(item); }

  const int throwItem() {
    int item = items.front();
    items.pop_front();
    int retVal = operation(item, item);
    retVal /= 3;
    inspections++;
    return retVal;
  }

  int toMonkey(int item) { return test(item); }

  const std::deque<int> &getItems() const { return items; }

  bool hasItems() const { return !items.empty(); }

  const int getInsp() const { return inspections; }

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
    for (int j = 0; j < 6; j++)
      range.push_back(file[i + j]);
    Monkey temp{range};
    monkeyList.push_back(temp);
  }
  part1(monkeyList);
}

void part1(std::vector<Monkey> monkeyList) {
  for (int i = 0; i < 20; i++) {
    std::cout << i << std::endl;
    for (auto i = 0; i < monkeyList.size(); i++) {
      while (monkeyList[i].hasItems()) {
        int nItem = monkeyList[i].throwItem();
        int toMonk = monkeyList[i].toMonkey(nItem);
        monkeyList[toMonk].recieveItem(nItem);
      }
    }
    for (auto monkey : monkeyList) {
      monkey.print();
    }
  }

  std::sort(monkeyList.begin(), monkeyList.end(),
            [](auto a, auto b) { return a > b; });
  std::printf("part1: %d\n", monkeyList[0].getInsp() * monkeyList[1].getInsp());
}

void part2(std::vector<Monkey> monkeyList) {}
} // namespace day11
