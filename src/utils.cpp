#include "utils.hpp"

std::vector<std::string> readFile(const char* fileName) {
  std::ifstream myfile(fileName);
  std::vector<std::string> retvec;

  if (myfile.is_open()) {
    std::string myline;
    while(std::getline(myfile, myline)) {
      retvec.push_back(myline);
    }
  }
  return retvec;
}
