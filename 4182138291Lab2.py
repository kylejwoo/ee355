import numpy as np
import pickle

class Matrix:

## reading matrix and turning into an array

    def __init__(self, filename):
        # Read the matrix from a file and store it as a numpy array
        self.value = np.loadtxt(filename, usecols=range(10))
        self.maximum = np.max(self.value)
        self.minimum = np.min(self.value)
    
    def linear_search(self, target):
        found_first = False
        for i in range(self.value.shape[0]):
            for j in range(self.value.shape[1]):
                if self.value[i, j] == target:
                    if found_first:
                        return (i, j)
                    else:
                        found_first = True
        return (-1, -1)

## matrix functions

def matrix_addition(mat1, mat2):
    result = np.zeros_like(mat1.value) # makes aarray same size all filled with 0
    
    for i in range(result.shape[0]):# rows
        for j in range(result.shape[1]): # columns
            result[i, j] = mat1.value[i, j] + mat2.value[i, j]
    return result

def matrix_multiplication(mat1, mat2):
    result = np.zeros_like(mat1.value)
    for i in range(result.shape[0]):
        for j in range(result.shape[1]):
            for k in range(mat1.value.shape[1]):
                result[i, j] += mat1.value[i, k] * mat2.value[k, j]
    return result

# Create Matrix objects from files
mat1 = Matrix('matrix_1.txt')
mat2 = Matrix('matrix_2.txt')

# Perform operations
idx_row_mat_1 = mat1.linear_search(mat1.value[0, 0])
idx_row_mat_2 = mat2.linear_search(mat2.value[0, 0])

mat_add = matrix_addition(mat1, mat2)
mat_mul = matrix_multiplication(mat1, mat2)

## Collect results
results = {
    'idx_row_mat_1': idx_row_mat_1,
    'max_mat_1': mat1.maximum,
    'min_mat_1': mat1.minimum,
    'idx_row_mat_2': idx_row_mat_2,
    'max_mat_2': mat2.maximum,
    'min_mat_2': mat2.minimum,
    'mat_add': mat_add,
    'mat_mul': mat_mul
}


with open('output_py.pickle', 'wb') as f:
    pickle.dump(results, f)

