#include "game.h"

#include <iostream>

GameState::GameState() {
  // Initialize the board with pawns on the 1st and 8th row.
  for (int i = 0; i < 8; i++) {
    board[1][i] = Player::WHITE;
    board[6][i] = Player::BLACK;
  }
}

Player GameState::winner() const {
  // Check if any player has reached the opposite end.
  for (int i = 0; i < 8; i++) {
    if (board[0][i] == Player::BLACK) return Player::BLACK;
    if (board[7][i] == Player::WHITE) return Player::WHITE;
  }
  return Player::NONE;  // No winner yet
}

bool GameState::terminated() const {
  return winner() != Player::NONE || legalActions().empty();
}

std::vector<std::pair<int, int>> GameState::legalActions() const {
  // Generate legal pawn moves. This example only considers simple forward
  // moves.
  std::vector<std::pair<int, int>> actions;
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (board[row][col] == currentPlayer) {
        int nextRow = (currentPlayer == Player::WHITE) ? row + 1 : row - 1;
        if (nextRow >= 0 && nextRow < 8 &&
            board[nextRow][col] == Player::NONE) {
          actions.emplace_back(row * 8 + col, nextRow * 8 + col);
        }
      }
    }
  }
  return actions;
}

void GameState::makeMove(int fromIdx, int toIdx) {
  int fromRow = fromIdx / 8;
  int fromCol = fromIdx % 8;
  int toRow = toIdx / 8;
  int toCol = toIdx % 8;

  if (board[fromRow][fromCol] != currentPlayer ||
      board[toRow][toCol] != Player::NONE) {
    throw std::runtime_error("Illegal move");
  }

  // Move the pawn
  board[toRow][toCol] = currentPlayer;
  board[fromRow][fromCol] = Player::NONE;

  // Switch player
  currentPlayer =
      (currentPlayer == Player::WHITE) ? Player::BLACK : Player::WHITE;
}

void GameState::printBoard() const {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      switch (board[i][j]) {
        case Player::WHITE:
          std::cout << "W ";
          break;
        case Player::BLACK:
          std::cout << "B ";
          break;
        default:
          std::cout << ". ";
          break;
      }
    }
    std::cout << '\n';
  }
  std::cout << (currentPlayer == Player::WHITE ? "White" : "Black")
            << " to move\n";
}