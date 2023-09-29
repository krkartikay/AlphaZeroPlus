#pragma once

#include <array>
#include <optional>
#include <vector>

enum class Player { NONE = 0, WHITE = 1, BLACK = -1 };

class GameState {
 public:
  GameState(const GameState& other);
  GameState();

  Player player() const { return currentPlayer; }
  Player winner() const;
  bool terminated() const;
  std::vector<std::pair<int, int>> legalActions() const;
  std::array<std::array<int, 8>, 8> toImage() const;
  int leafValue() const;

  void makeMove(int fromIdx, int toIdx);
  void printBoard() const;

 private:
  Player board[8][8] = {Player::NONE};
  Player currentPlayer = Player::WHITE;
  std::optional<std::pair<int, int>> lastMove =
      std::nullopt;  // Keeps track of the last move made.
};
