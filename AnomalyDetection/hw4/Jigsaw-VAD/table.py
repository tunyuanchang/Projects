import itertools
import numpy as np

permutations = itertools.permutations(np.arange(5))
label = dict()
for index, value in enumerate(permutations):
    label[''.join(map(str, value))] = index

def find_index(perm):
    return label[''.join(map(str, perm))]