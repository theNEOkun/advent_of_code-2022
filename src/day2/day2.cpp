#include "././day2.hpp"

// Gnome moves
constexpr char G_ROCK = 'A';
constexpr char G_PEPR = 'B';
constexpr char G_SCSR = 'C';

// Player moves
constexpr char P_ROCK = 'X';
constexpr char P_PEPR = 'Y';
constexpr char P_SCSR = 'Z';

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
  if (ownMove == P_ROCK) {
    tally += POINT_ROCK;
    // and they make scissor
    if (loseMove == G_SCSR) {
      // I win
      tally += WIN;
    }
    // and they make rock
    else if (loseMove == G_ROCK) {
      // We draw
      tally += DRAW;
    }
    // I lose
    else
      tally += LOSS;
  }
  // If I make paper
  if (ownMove == P_PEPR) {
    tally += POINT_PEPR;
    // and they make rock
    if (loseMove == G_ROCK) {
      // I win
      tally += WIN;
    }
    // and they make paper
    else if (loseMove == G_PEPR) {
      // We draw
      tally += DRAW;
    }
    // I lose
    else
      tally += LOSS;
  }
  // If I make scissor
  if (ownMove == P_SCSR) {
    tally += POINT_SCSR;
    // and the make paper
    if (loseMove == G_PEPR) {
      // I win
      tally += WIN;
    }
    // and they make scissor
    else if (loseMove == G_SCSR) {
      // We draw
      tally += DRAW;
    }
    // I lose
    else
      tally += LOSS;
  }
  return tally;
}

/**
 * Get the move based on the outcome
 * @param outcome is lose, win or draw
 * @param their_move is the move they are going to make
 * @return rock, paper or scissor based on their move
 */
char get_move(char outcome, char their_move) {
  constexpr char S_LOSE = 'X';
  constexpr char S_DRAW = 'Y';
  constexpr char S_WIN = 'Z';

  if (outcome == S_LOSE) {
    if (their_move == G_PEPR)
      return P_ROCK;
    if (their_move == G_ROCK)
      return P_SCSR;
    if (their_move == G_SCSR)
      return P_PEPR;
  }
  if (outcome == S_DRAW) {
    if (their_move == G_PEPR)
      return P_PEPR;
    if (their_move == G_ROCK)
      return P_ROCK;
    if (their_move == G_SCSR)
      return P_SCSR;
  }
  if (outcome == S_WIN) {
    if (their_move == G_PEPR)
      return P_SCSR;
    if (their_move == G_ROCK)
      return P_PEPR;
    if (their_move == G_SCSR)
      return P_ROCK;
  }
  return 0;
}

void day2::run() {

  std::cout << "DAY 2" << std::endl;

  std::vector<std::string> lines = readFile("../resources/input_day2");
  long tally = 0;
  for (auto each : lines) {
    tally += test(each[2], each[0]);
  }
  std::cout << "FIRST TALLY: " << tally << std::endl;

  long second_tally = 0;
  for (auto each : lines) {
    char choice = get_move(each[2], each[0]);
    second_tally += test(choice, each[0]);
  }
  std::cout << "SECOND TALLY: " << second_tally << std::endl;
}
