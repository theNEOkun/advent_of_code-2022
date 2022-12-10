#include "utils.hpp"

utils::utils(char* cwd): cwd(cwd) {}

/**
 * Read a file line by line into a vector and then return
 * @param fileName is the fileName to read
 * @return std::vector<std::string> containing all lines of the file
 */
std::vector<std::string> utils::readFile(const char* fileName) {
  std::ifstream myfile(cwd + '/' + fileName);
  std::vector<std::string> retvec;

  if (myfile.is_open()) {
    std::string myline;
    while(std::getline(myfile, myline)) {
      retvec.push_back(myline);
    }
  } else {
    std::printf("That file does not exist");
  }
  return retvec;
}

std::vector<std::string> getListOfWords(std::string string, std::string delimiter) {
  std::vector<std::string> retVal;
  size_t pos = 0;
  while((pos = string.find(delimiter)) != std::string::npos) {
    retVal.push_back(string.substr(0, pos));
    string.erase(0, pos + delimiter.length());
  }
  retVal.push_back(string);
  return retVal;
} 
