import numpy as np
import os
import scipy.io as sio


# Path: directory that contain all vertices
def read_vertices(path):
    labels = os.listdir(path)
    print(labels)

    all_vertices = []
    all_labels = []
    for l_i, label in enumerate(labels):
        files = os.listdir(os.path.join(path, label))

        for file in files:
            file = open(os.path.join(path, label, file), 'r')

            vertices_of_object = []
            for line in file.readlines():
                splits = line.split(' ')
                vertices_of_object.append([float(splits[1]), float(splits[2]), float(splits[3])])

            all_vertices.append(vertices_of_object)
            all_labels.append(l_i)

    return labels, np.array(all_vertices), np.array(all_labels)

def save_to_mat(model):
    fc1 = model.fc1.weight.data
    fc1 = np.transpose(fc1.numpy())

    fc2 = model.fc2.weight.data
    fc2 = np.transpose(fc2.numpy())

    fc3 = model.fc3.weight.data
    fc3 = np.transpose(fc3.numpy())

    np.savetxt('C:\\Users\\Emre\\source\\repos\\MatAPI\\MatAPI\\fc1.out', fc1, delimiter='\n')
    np.savetxt('C:\\Users\\Emre\\source\\repos\\MatAPI\\MatAPI\\fc2.out', fc2, delimiter='\n')
    np.savetxt('C:\\Users\\Emre\\source\\repos\\MatAPI\\MatAPI\\fc3.out', fc3, delimiter='\n')
