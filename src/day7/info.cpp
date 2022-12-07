#include "info.hpp"

Info::Info(std::string incoming, std::string incoming_2)
    : command{incoming}, command_part2{incoming_2} {
  this->what_command = info_type::COMMAND;
}
Info::Info(long size, std::string fileName) : fileName{fileName}, size(size) {
  this->what_command = info_type::FILE;
}
Info::Info(std::string directory) : fileName{directory}, size(0) {
  this->what_command = info_type::DIRECTORY;
}
Info::Info(): size(0) {
  this->what_command = info_type::FAIL;
}

const info_type Info::getInfoType() const { return this->what_command; }

const std::string Info::getCommand() const { return this->command; }

const std::string Info::getInput() const { return this->command_part2; }

const long Info::getFileSize() const { return this->size; }

const std::string Info::getFileName() const { return this->fileName; }
