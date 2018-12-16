import torch
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from sklearn.model_selection import train_test_split

from model import V2L
from utils import read_vertices


# Read Data
class_names, x, y = read_vertices('data\\vertices\\')

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=42, shuffle=True)
data = [torch.from_numpy(X_train), torch.from_numpy(y_train).type(torch.LongTensor)]
val_data = [torch.from_numpy(X_test), torch.from_numpy(y_test).type(torch.LongTensor)]

# Learning Paramter Stuff
lr = 0.001
epochs = 20

# Initialize the model
model = V2L()

criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=lr, momentum=0.9)

for epoch in range(epochs):  # loop over the dataset multiple times

    running_loss = 0.0
    # TODO: add batch
    for i, da in enumerate(['d']): # enumerate(trainloader, 0):
        # get the inputs
        inputs, labels = data


        # zero the parameter gradients
        optimizer.zero_grad()

        # forward + backward + optimize
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        # TODO: print stat. edit here

print('Finished Training')

# Test the model
images, labels = val_data

correct = 0
total = 0
with torch.no_grad():
    images, labels = val_data
    outputs = model(images)
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum().item()

print('Accuracy of the network on the %d test images: %d %%' % (total ,
    100 * correct / total))

# TODO: Print accuracy for each class
