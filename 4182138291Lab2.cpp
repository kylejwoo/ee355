#include <iostream>
#include <fstream>
#include <vector>

class Matrix {
public:
    std::vector<std::vector<int>> value;
    int maximum;
    int minimum;
    Matrix() {
        value.resize(10, std::vector<int>(10, 0)); // Initializes a 10x10 matrix filled with zeros
        // Needed this to make sure we have a default constructor
    }
    
    Matrix(const std::string& filename) {
        std::ifstream file(filename);
        if (file) {
            int num;
            while (file >> num) {
                std::vector<int> row;
                row.push_back(num);
                for (int i = 1; i < 10; ++i) {
                    file >> num;
                    row.push_back(num);
                }
                value.push_back(row);
            }
        }
        file.close();
    }

    void findMaxMin() {
        maximum = value[0][0];
        minimum = value[0][0];
        for (const auto& row : value) {
            for (int num : row) {
                if (num > maximum)
                	maximum = num;
                if (num < minimum)
                	minimum = num;
            }
        }
    }

    std::pair<int, int> linearSearch(int target) {
        for (size_t i = 0; i < value.size(); ++i) {
            for (size_t j = 0; j < value[i].size(); ++j) {
                if (value[i][j] == target) {
                    return {i, j}; // Return the position as a pair (row, column)
                }
            }
        }
        return {-1, -1}; // Return {-1, -1} if the target is not found
    }
    
   void writeSearchResultsToFile(const std::string& filename) {
   	int firstNum = value[0][0];
        bool found = false;
        bool firstfound = true;
        std::pair<int, int> position = {-1, -1};
        maximum = value[0][0]; 
        minimum = value[0][0]; 

        // search to find the target index, max, and min
        for (int i = 0; i < value.size(); ++i) {
            for (int j = 0; j < value[i].size(); ++j) {
            	
            	if(firstfound){
            	    firstfound = false;	
            	}
                else if (value[i][j] == firstNum && !found) {
                    found = true;
                    position = {i, j};
                }
                if (value[i][j] > maximum) {
                    maximum = value[i][j];
                }
                if (value[i][j] < minimum) {
                    minimum = value[i][j];
                }
            }
        }

        // Write results to  file
        std::ofstream outFile(filename);
        outFile << "----------------------------------------\n";
        if (found) {
            outFile << "Target value in matrix is shown in row " << position.first + 1 << "\n";
        } else {
            outFile << "Target value in matrix is not shown\n";
        }
        outFile << "Maximum value is " << maximum << "\n";
        outFile << "Minimum value is " << minimum << "\n";
        outFile << "----------------------------------------\n";
        outFile.close();
    }
   
    
    
    
   
};
Matrix multiply(Matrix m1, Matrix m2)  {
        Matrix result;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                for (int k = 0; k < 10; ++k) {
                    result.value[i][j] += m1.value[i][k] * m2.value[k][j];
                }
            }
        }
        return result;
}
 Matrix add(Matrix m1, Matrix m2) {
        Matrix result;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                result.value[i][j] = m1.value[i][j] + m2.value[i][j]; //pointers and attributes
            }
        }
        return result;
}
 void writeMatrixToFile(const Matrix& mat, const std::string& filename) {
    std::ofstream outFile(filename);
    for (const auto& row : mat.value) {
        for (const auto& elem : row) {
            outFile << elem << ' ';
        }
        outFile << '\n';
    }
    outFile.close();
}

// Additional methods for matrix addition and multiplication would go here

int main() {
    Matrix mat1("matrix_1.txt");
    Matrix mat2("matrix_2.txt");
    
    // Use mat.linearSearch, mat.add, mat.mul, etc.
    mat1.writeSearchResultsToFile("output_Q1_1.txt");

    // Process and write results for matrix 2
    mat2.writeSearchResultsToFile("output_Q1_2.txt");
    
    
    Matrix result = add(mat1, mat2);
    writeMatrixToFile(result, "output_Q2.txt");

    result = multiply(mat1,mat2); //reusing the first created matrix to supply for the multiplicaation matrix
    writeMatrixToFile(result, "output_Q3.txt");

    return 0;
}
