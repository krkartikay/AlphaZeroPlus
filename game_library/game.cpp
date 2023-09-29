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
  std::vector<std::pair<int, int>> actions;

  int direction = (currentPlayer == Player::WHITE)
                      ? 1
                      : -1;  // White moves up, Black moves down.

  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      if (board[row][col] == currentPlayer) {
        // Forward move
        if (row + direction >= 0 && row + direction < 8 &&
            board[row + direction][col] == Player::NONE) {
          actions.emplace_back(row * 8 + col, (row + direction) * 8 + col);

          // Double forward move from starting position
          if ((currentPlayer == Player::WHITE && row == 1) ||
              (currentPlayer == Player::BLACK && row == 6)) {
            if (board[row + 2 * direction][col] == Player::NONE) {
              actions.emplace_back(row * 8 + col,
                                   (row + 2 * direction) * 8 + col);
            }
          }
        }

        // Capture moves
        for (int offset : {-1, 1}) {
          if (col + offset >= 0 && col + offset < 8 &&
              board[row + direction][col + offset] ==
                  Player(-int(currentPlayer))) {
            actions.emplace_back(row * 8 + col,
                                 (row + direction) * 8 + col + offset);
          }
        }

        // En passant
        if (lastMove) {
          int lastFromRow = lastMove->first / 8;
          int lastFromCol = lastMove->first % 8;
          int lastToRow = lastMove->second / 8;
          int lastToCol = lastMove->second % 8;

          if (abs(lastToRow - lastFromRow) == 2 && lastToCol == col &&
              abs(lastToRow - row) == 1) {
            actions.emplace_back(row * 8 + col, lastToRow * 8 + col);
          }
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
      board[toRow][toCol] == currentPlayer) {
    throw std::runtime_error("Illegal move");
  }

  // Update board and lastMove
  board[toRow][toCol] = board[fromRow][fromCol];
  board[fromRow][fromCol] = Player::NONE;
  lastMove = std::make_pair(fromIdx, toIdx);

  // Handle en passant capture
  if (abs(toRow - fromRow) == 1 && toCol != fromCol &&
      board[toRow][toCol] == Player::NONE) {
    board[fromRow][toCol] = Player::NONE;
  }

  // Switch player
  currentPlayer = Player(-int(currentPlayer));
}

void GameState::printBoard() const {
  for (int i = 7; i >= 0; i--) {
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

std::array<std::array<int, 8>, 8> GameState::toImage() const {
  std::array<std::array<int, 8>, 8> image = {0};  // Initializing to zeros

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      switch (board[i][j]) {
        case Player::WHITE:
          image[i][j] = 1;
          break;
        case Player::BLACK:
          image[i][j] = -1;
          break;
        default:
          image[i][j] = 0;
          break;
      }
    }
  }

  return image;
}

int GameState::leafValue() const {
  Player winnerPlayer = winner();
  if (winnerPlayer == Player::NONE) {
    return 0;
  }
  return (winnerPlayer == currentPlayer) ? 1 : -1;
}