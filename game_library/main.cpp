#include <iostream>

#include "game.h"

int main() {
  GameState gameState;

  // Example usage of the GameState class
  while (!gameState.terminated()) {
    // Print the current player and board state
    std::cout << (gameState.player() == Player::WHITE ? "White" : "Black")
              << " to move\n";

    // Get legal actions and make a move (for example, the first legal action)
    auto actions = gameState.legalActions();
    if (actions.empty()) {
      break;
    }
    gameState.makeMove(actions[0].first, actions[0].second);
    gameState.printBoard();
  }

  std::cout << (gameState.winner() == Player::WHITE
                    ? "White"
                    : (gameState.winner() == Player::BLACK ? "Black"
                                                           : "No one"))
            << " wins!\n";

  return 0;
}