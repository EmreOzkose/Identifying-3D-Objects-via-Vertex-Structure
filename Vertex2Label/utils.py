import numpy as np
import os


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