#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class utils {
  std::string cwd;
  std::string baseDir;

public:
  utils(char *cwd);
  std::vector<std::string> readFile(const char *fileName);
  static std::vector<std::string> splitString(std::string str, std::string delimiter);
  static int map(int number, int start1, int stop1, int start2, int stop2);
};
