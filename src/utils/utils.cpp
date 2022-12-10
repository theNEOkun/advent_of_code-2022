#include "utils.hpp"

utils::utils(char* cwd): cwd(cwd) {
  this->baseDir = this->splitString(cwd, "/")[-2];
}

std::vector<std::string> utils::splitString(std::string str, std::string delimiter) {
  std::vector<std::string> retVal;
  size_t pos = 0;
  while((pos = str.find(delimiter)) != std::string::npos) {
    retVal.push_back(str.substr(0, pos));
    str.erase(0, pos + delimiter.length());
  }
  retVal.push_back(str);
  return retVal;
}

/**
 * Read a file line by line into a vector and then return
 * @param fileName is the fileName to read
 * @return std::vector<std::string> containing all lines of the file
 */
std::vector<std::string> utils::readFile(const char* fileName) {
  std::string file = this->baseDir + fileName;
  std::ifstream myfile(file);
  std::vector<std::string> retvec;

  if (myfile.is_open()) {
    std::string myline;
    while(std::getline(myfile, myline)) {
      retvec.push_back(myline);
    }
  } else {
    std::printf("That file does not exist %s\n", file.c_str());
  }
  return retvec;
}
