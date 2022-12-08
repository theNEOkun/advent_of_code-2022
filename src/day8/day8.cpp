#include "day8.hpp"
namespace day8 {

void part1(std::vector<std::string> &file);
void part2(std::vector<std::string> &file);

void run() {
  std::printf("DAY8\n");
  auto file = readFile("../resources/input_day8");
  part1(file);
  part2(file);
}

bool testFunc(int x, int y, int tree, std::vector<std::string> &file,
              std::string dir) {
  char tee = file[x][y];
  int testTree = tee - '0';
  if (testTree >= tree) {
    return true;
  }
  return false;
}

void part1(std::vector<std::string> &file) {
  int counter = 0;
  counter += file.size() * 2;
  counter += file[0].size() * 2 - 4;
  for (int treeRow = 1; treeRow < file.size() - 1; treeRow++) {
    for (int treeCol = 1; treeCol < file[treeRow].size() - 1; treeCol++) {
      int tree = file[treeRow][treeCol] - '0';
      bool leftBool = false;
      for (int i = 0; i < treeRow; i++) {
        leftBool |= testFunc(i, treeCol, tree, file, "Up");
      }
      bool rightBool = false;
      for (int i = treeRow + 1; i < file.size(); i++) {
        rightBool |= testFunc(i, treeCol, tree, file, "Down");
      }
      bool upBool = false;
      for (int j = 0; j < treeCol; j++) {
        upBool |= testFunc(treeRow, j, tree, file, "Left");
      }
      bool downBool = false;
      for (int j = treeCol + 1; j < file[treeRow].size(); j++) {
        downBool |= testFunc(treeRow, j, tree, file, "Right");
      }
      if (!leftBool | !rightBool | !upBool | !downBool)
        counter++;
    }
  }
  std::printf("Part1: %d\n", counter);
}

const bool DEBUG_P2 = false;

void part2(std::vector<std::string> &file) {
  std::vector<int> scenicCounter;
  for (int treeRow = 1; treeRow < file.size() - 1; treeRow++) {
    for (int treeCol = 1; treeCol < file[treeRow].size() - 1; treeCol++) {
      int tree = file[treeRow][treeCol] - '0';

      if(DEBUG_P2) std::printf("Tree %d, ( x: %d, y: %d )\n", tree, treeRow, treeCol);

      int scenic = 1;
      for (int i = treeRow - 1, count = 1; i >= 0; i--, count++) {
        if(testFunc(i, treeCol, tree, file, "Up") || i-1 == -1) {
          if(DEBUG_P2) std::printf("%d\t", count);
          scenic *= count;
          break;
        }
      }
      for (int i = treeRow + 1, count = 1; i < file.size(); i++, count++) {
        if(testFunc(i, treeCol, tree, file, "Down") || i+1 == file.size()) {
          if(DEBUG_P2) std::printf("%d\t", count);
          scenic *= count;
          break;
        }
      }
      for (int j = treeCol - 1, count = 1; j >= 0; j--, count++) {
        if(testFunc(treeRow, j, tree, file, "Left") || j-1 == -1) {
          if(DEBUG_P2) std::printf("%d\t", count);
          scenic *= count;
          break;
        }
      }
      for (int j = treeCol + 1, count = 1; j < file[treeRow].size(); j++, count++) {
        if(testFunc(treeRow, j, tree, file, "Right") || j+1 == file[treeRow].size()) {
          if(DEBUG_P2) std::printf("%d\t", count);
          scenic *= count;
          break;
        }
      }
      if(DEBUG_P2) std::printf("\n");
      scenicCounter.push_back(scenic);
    }
  }
  std::sort(scenicCounter.begin(), scenicCounter.end(), [](int a, int b){ return a > b; });
  std::printf("Part2: %d\n", scenicCounter[0]);
}
} // namespace day8
