#include "day11.hpp"
#include <functional>

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
      return old1 + std::stoi(operations[2]);
    };
  else
    return [=](int old1, int old2) -> int {
      return old1 * std::stoi(operations[2]);
    };
}

std::function<int(int)> makeTest(std::string test, std::string trueMonkey,
                                 std::string falseMonkey) {
  return [=](int testnum) -> int {
    if (testnum % std::stoi(test) == 0) {
      return std::stoi(trueMonkey);
    } else {
      return std::stoi(falseMonkey);
    }
  };
}

class Monkey {
private:
  int name;
  std::vector<int> items;
  std::function<int(int, int)> operation;
  std::function<bool(int)> test;
  int inspections = 0;

public:
  Monkey(std::vector<std::string> monkeyInfo) {
    for (auto each : monkeyInfo)
      std::cout << each << std::endl;

    auto nameRow = utils::splitString(monkeyInfo[0]);
    this->name = std::stoi(nameRow[1]);

    auto itemRow = utils::splitString(monkeyInfo[1], ": ");
    auto itemList = utils::splitString(itemRow[1], ", ");
    std::vector<int> items;
    for (auto each : itemList) {
      items.push_back(std::stoi(each));
    }
    this->items = items;

    auto operationRow = utils::splitString(monkeyInfo[2], ": ");
    auto operations =
        utils::splitString(utils::splitString(operationRow[1], " = ")[1]);
    this->operation = makeOperation(operations);

    auto test = utils::splitString(monkeyInfo[3]).back();
    auto trueMonkey = utils::splitString(monkeyInfo[4]).back();
    auto falseMonkey = utils::splitString(monkeyInfo[5]).back();
    this->test = makeTest(test, trueMonkey, falseMonkey);
  }

  const int getName() const { return this->name; }

  void recieveItem(int item) { this->items.push_back(item); }

  int throwItem(int item) {
    int retVal = item / 3;
    retVal = this->operation(item, item);
    this->inspections++;
    return retVal;
  }

  int toMonkey(int item) {
    auto test = this->test(item);
    return test;
  }

  const std::vector<int> &getItems() const { return this->items; }

  bool hasItems() const { return this->items.empty(); }

  void clearItems() { this->items.clear(); }

  const int getInsp() const { return this->inspections; }

  void print() {
    std::cout << "Name: " << this->name << std::endl;
    for (auto each : this->getItems()) {
      std::cout << " Item: " << each << std::endl;
      ;
    }
  }

  bool operator<(Monkey &other) {
    return this->inspections < other.inspections;
  }
};

void part1(std::vector<Monkey> monkeyList);
void part2(std::vector<Monkey> monkeyList);

void run(utils utils) {
  std::printf("DAY11\n");
  auto file = utils.readFile("input_day11_examples");
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
  for (int i = 0; i < 2; i++) {
    std::cout << i << std::endl;
    for (auto monkey : monkeyList) {
      // monkey.print();
      for (int item : monkey.getItems()) {
        int nItem = monkey.throwItem(item);
        int toMonk = monkey.toMonkey(nItem);
        std::printf("original: %d, new: %d from: %d to: %d\n", item, nItem,
                    monkey.getName(), toMonk);
        monkeyList[toMonk].recieveItem(nItem);
      }
      monkey.clearItems();
    }
  }

  for (auto monkey : monkeyList) {
    monkey.print();
  }

  std::sort(monkeyList.begin(), monkeyList.end(),
            [](auto a, auto b) { return a < b; });
  std::printf("part1: %d\n", monkeyList[0].getInsp() * monkeyList[1].getInsp());
}

void part2(std::vector<Monkey> monkeyList) {}
} // namespace day11
