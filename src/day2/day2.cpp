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

enum move {
  ROCK = 1,
  PAPER = 2,
  SCISSOR = 3,
  FAIL = -1
};

move getWinningMove(move move) {
  if(move == move::ROCK) {
    return move::PAPER;
  }
  if(move == move::PAPER) {
    return move::SCISSOR;
  }
  return move::ROCK;
}

move getLosingMove(move move) {
  if(move == move::ROCK) {
    return move::SCISSOR;
  }
  if(move == move::PAPER) {
    return move::ROCK;
  }
  return move::PAPER;
}


move getPMove(char move) {
  if(move == P_ROCK || move == G_ROCK)
    return move::ROCK;
  if(move == P_PEPR || move == G_PEPR)
    return move::PAPER;
  if(move == P_SCSR || move == G_SCSR)
    return move::SCISSOR;
  return move::FAIL;
}

int test(move ownMove, move theirMove) {
  int tally = ownMove;
  if(ownMove == getWinningMove(theirMove))
    tally += WIN;
  if(ownMove == theirMove)
    tally += DRAW;
  else
    tally += LOSS;
  return tally;
}

/**
 * Get the move based on the outcome
 * @param outcome is lose, win or draw
 * @param their_move is the move they are going to make
 * @return rock, paper or scissor based on their move
 */
move get_move(char outcome, move their_move) {
  constexpr char S_LOSE = 'X';
  constexpr char S_DRAW = 'Y';
  constexpr char S_WIN = 'Z';

  if (outcome == S_LOSE) {
    return getLosingMove(their_move);
  }
  if (outcome == S_DRAW) {
    return their_move;
  }
  if (outcome == S_WIN) {
    return getWinningMove(their_move);
  }
  return move::FAIL;
}

void day2::run() {

  std::cout << "DAY 2" << std::endl;

  std::vector<std::string> lines = readFile("../resources/input_day2");
  long tally = 0;
  for (auto each : lines) {
    tally += test(getPMove(each[2]), getPMove(each[0]));
  }
  std::cout << "FIRST TALLY: " << tally << std::endl;

  long second_tally = 0;
  for (auto each : lines) {
    move choice = get_move(each[2], getPMove(each[0]));
    second_tally += test(choice, getPMove(each[0]));
  }
  std::cout << "SECOND TALLY: " << second_tally << std::endl;
}
