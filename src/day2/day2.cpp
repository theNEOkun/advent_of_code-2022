#include "././day2.hpp"


// Gnome moves
constexpr char G_STONE = 'A';
constexpr char G_ROCK = 'B';
constexpr char G_SCRS = 'C';

// Player moves
constexpr char P_STONE = 'Y';
constexpr char P_ROCK = 'X';
constexpr char P_SCRS = 'Z';

// Points when winning
constexpr int POINT_ROCK = 1;
constexpr int POINT_PEPR = 2;
constexpr int POINT_SCSR = 3;

// Match points
constexpr int LOSS = 0;
constexpr int DRAW = 3;
constexpr int WINN = 6;

std::string day2::run() {

  std::vector<std::string> lines = readFile("./src/day2/input");

  for(auto each : lines) {
    std::cout << each << std::endl;
  }

  return "";
}
