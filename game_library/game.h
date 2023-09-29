#pragma once

#include <vector>

enum class Player { NONE, WHITE, BLACK };

class GameState {
 public:
  GameState();
  Player player() const { return currentPlayer; }
  Player winner() const;
  bool terminated() const;
  std::vector<std::pair<int, int>> legalActions() const;

  void makeMove(int fromIdx, int toIdx);

  void printBoard() const;

 private:
  Player board[8][8] = {Player::NONE};
  Player currentPlayer = Player::WHITE;
};
