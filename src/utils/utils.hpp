#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class utils {
  std::string cwd;
public:
  utils(char* cwd);
  std::vector<std::string> readFile(const char *fileName);
};

std::vector<std::string> getListOfWords(std::string, std::string);
