import game
import random

# Create a GameState object
g = game.GameState()

g.printBoard()

# Perform moves until the game is terminated
while not g.terminated():
    actions = g.legalActions()
    print(actions)
    print()

    first, second = random.choice(actions)
    g.makeMove(first, second)

    # Print the final game board
    g.printBoard()
    print()

if g.winner() == game.WHITE:
    print("White wins!")
elif g.winner() == game.BLACK:
    print("Black wins!")
else:
    print("No one wins!")

print()