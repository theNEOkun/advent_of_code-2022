#ifndef INFO_HPP
#define INFO_HPP

#include <string>

enum class info_type { COMMAND = 0, DIRECTORY = 1, FILE = 2, FAIL = -1 };

class Info {

private:
  std::string command;
  std::string command_part2;
  std::string fileName;
  long size;
  info_type what_command;

public:
  Info();
  Info(std::string incoming, std::string incoming_2);
  Info(long size, std::string fileName);
  Info(std::string directory);

  const info_type getInfoType() const;

  const std::string getCommand() const;

  const std::string getInput() const;

  const long getFileSize() const;

  const std::string getFileName() const;
};

#endif //INFO_HPP
