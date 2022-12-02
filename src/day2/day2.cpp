#include "././day2.hpp"

// Gnome moves
constexpr char G_ROCK = 'A';
constexpr char G_PEPR = 'B';
constexpr char G_SCSR = 'C';

// Player moves
constexpr char P_ROCK = 'X';
constexpr char P_PEPR = 'Y';
constexpr char P_SCSR = 'Z';

constexpr char S_LOSE = 'X';
constexpr char S_DRAW = 'Y';
constexpr char S_WIN = 'Z';

// Points when winning
constexpr int POINT_ROCK = 1;
constexpr int POINT_PEPR = 2;
constexpr int POINT_SCSR = 3;

// Match points
constexpr int LOSS = 0;
constexpr int DRAW = 3;
constexpr int WIN = 6;

int test(char ownMove, char loseMove) { 
  int tally = 0;
  // If I make rock
  if(ownMove == P_ROCK) {
    tally += POINT_ROCK;
    // and they make scissor
    if(loseMove == G_SCSR) {
      // I win
      tally += WIN;
    }
    // and they make rock
    else if(loseMove == G_ROCK) {
      // We draw
      tally += DRAW;
    }
    // I lose
    else tally += LOSS;
  }
  // If I make paper
  if (ownMove == P_PEPR) {
    tally += POINT_PEPR;
    // and they make rock
    if(loseMove == G_ROCK) {
      // I win
      tally += WIN;
    }
    // and they make paper
    else if(loseMove == G_PEPR) {
      // We draw
      tally += DRAW;
    }
    // I lose
    else tally += LOSS;
  }
  // If I make scissor
  if(ownMove == P_SCSR) {
    tally += POINT_SCSR;
    // and the make paper
    if(loseMove == G_PEPR) {
      // I win
      tally += WIN;
    }
    // and they make scissor
    else if(loseMove == G_SCSR) {
      // We draw
      tally += DRAW;
    }
    // I lose
    else tally += LOSS;
  }
  return tally;
}

void day2::run() {

  std::cout << "DAY 2" << std::endl;

  std::vector<std::string> lines = readFile("./src/day2/input");

  long tally = 0;
  for (auto each : lines) {
    tally += test(each[2], each[0]);
  }
  std::cout << "TALLY: " << tally << std::endl;


}
