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
};
