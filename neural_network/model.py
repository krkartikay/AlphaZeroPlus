import torch

class ValueNetwork(torch.nn.Module):

  def __init__(self) -> None:
    super().__init__()

    self.layer = torch.nn.Linear(64, 1)


  def forward(self, board: torch.Tensor):
    val = self.layer(board.view(64))
    return val
  

if __name__ == '__main__':
  net = ValueNetwork()
  board = torch.Tensor([
    [-1, -1, -1, -1, -1, -1, -1, -1],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 1, 1, 1, 1, 1]
  ])

  print(board)

  result = net(board)
  print(result)
    