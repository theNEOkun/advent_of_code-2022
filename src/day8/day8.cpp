#include "day8.hpp"
namespace day8 {

void part1(std::vector<std::string> &file);
void part2();

void run() {
  std::printf("DAY8\n");
  auto file = readFile("../resources/input_day8");
  part1(file);
}

bool testFunc(int x, int y, int tree, std::vector<std::string> &file,
              std::string dir) {
  char tee = file[x][y];
  int testTree = tee - '0';
  if (testTree >= tree) {
    // std::printf("%s: tt: %d {%c} (%d - %d)\t",dir.c_str(), testTree, tee, x, y);
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
      // std::printf("Tree: %d { %c } (%d - %d)\n", tree, file[treeRow][treeCol],
      //             treeRow, treeCol);

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
      // std::printf("\n");
      if (!leftBool | !rightBool | !upBool | !downBool)
        counter++;
    }
  }
  std::printf("Part1: %d\n", counter);
}
void part2() {}
} // namespace day8
