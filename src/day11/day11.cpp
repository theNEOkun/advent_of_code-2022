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
    return [=](int old1, int old2) -> int { return old1 + std::stoi(operations[2]); };
  else
    return [=](int old1, int old2) -> int { return old1 * std::stoi(operations[2]); };
}

std::function<int(int)>
makeTest(std::string test, std::string trueMonkey, std::string falseMonkey) {
  return [=](int testnum) -> int {
    if(testnum % std::stoi(test) == 0) {
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

public:
  Monkey(std::vector<std::string> monkeyInfo) {
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

    auto test = utils::splitString(monkeyInfo[3])[-1];
    auto trueMonkey = utils::splitString(monkeyInfo[4])[-1];
    auto falseMonkey = utils::splitString(monkeyInfo[5])[-1];
    this->test = makeTest(test, trueMonkey, falseMonkey);
  }

  void getItem(int item) {
    this->items.push_back(item);
  }

  int throwItem(int item) {
    int ret = this->items.back();
    this->items.pop_back();
    return ret;
  }

  std::ostream& operator<<(std::ostream& Str) {
    Str << "Name: " << this->name;
    return Str;
  }
};

void part1(std::vector<Monkey> &monkeyList);
void part2(std::vector<Monkey> &monkeyList);

void run(utils utils) {
  std::printf("DAY11\n");
  auto file = utils.readFile("input_day11_examples");
  std::vector<Monkey> monkeyList;
  for(int i = 0; i < file.size(); i+=6) {
    std::vector<std::string> range(&monkeyList[i], &monkeyList[i + 5]);
    Monkey temp{ range };
    monkeyList.push_back(temp);
  }
}

void part1(std::vector<Monkey> &monkeyList) {}
void part2(std::vector<Monkey> &monkeyList) {}
} // namespace day11
