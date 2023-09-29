import torch
import game

# Create a GameState object
g = game.GameState()

# Perform moves until the game is terminated
while not g.terminated():
    actions = g.legalActions()
    g.printBoard()
    if actions:
        g.makeMove(actions[0][0], actions[0][1])
    else:
        print("Stalemate!")

# Print the final game board
g.printBoard()
