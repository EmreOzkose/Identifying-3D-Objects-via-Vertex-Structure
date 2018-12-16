import torch
import torch.nn as nn
import torch.nn.functional as F


# Vertex to Label Model
class V2L(nn.Module):
    def __init__(self, num_of_vertices=680, num_of_class=3):
        super(V2L, self).__init__()

        # Parameters
        self.num_of_vertices = num_of_vertices
        self.num_of_class = num_of_class

        # Layers
        self.fc1 = nn.Linear(num_of_vertices*3, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, num_of_class)

    def forward(self, x):
        print(x.size())
        x = x.view(-1, 3 * self.num_of_vertices).type(torch.FloatTensor)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x
