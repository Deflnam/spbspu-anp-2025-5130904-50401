#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <fstream>

namespace burukov
{
  void destroyMatrix(int* matrix);
  int* createMatrix(size_t rows, size_t cols);
  int countLocalMinima(const int* matrix, size_t rows, size_t cols);
  int countLocalMaxima(const int* matrix, size_t rows, size_t cols);
}


void burukov::destroyMatrix(int* matrix)
{
  free(matrix);
}

int* burukov::createMatrix(size_t rows, size_t cols)
{
  int* matrix = nullptr;
  matrix = static_cast<int*>(malloc(rows * cols * sizeof(int)));
  return matrix;
}


int burukov::countLocalMinima(const int* matrix, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 1; i < rows - 1; ++i) {
    for (size_t j = 1; j < cols - 1; ++j) {
      const int current = matrix[i * cols + j];
      if (current < matrix[(i - 1) * cols + j] &&
          current < matrix[(i + 1) * cols + j] &&
          current < matrix[i * cols + (j - 1)] &&
          current < matrix[i * cols + (j + 1)]) {
        ++count;
      }
    }
  }
  return count;
}

int burukov::countLocalMaxima(const int* matrix, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 1; i < rows - 1; ++i) {
    for (size_t j = 1; j < cols - 1; ++j) {
      const int current = matrix[i * cols + j];
      if (current > matrix[(i - 1) * cols + j] &&
          current > matrix[(i + 1) * cols + j] &&
          current > matrix[i * cols + (j - 1)] &&
          current > matrix[i * cols + (j + 1)]) {
        ++count;
      }
    }
  }
  return count;
}




int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Error: ";
    if (argc < 4) {
      std::cerr << "Not enough arguments\n";
    } else {
      std::cerr << "Too many arguments\n";
    }
    return 1;
  }

  const char* numStr = argv[1];
  if (numStr[0] != '1' && numStr[0] != '2') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  
  if (numStr[1] != '\0') {
    std::cerr << "First parameter is not number\n";
    return 1;
  }

  const int num = numStr[0] - '0';
  const char* inputFileName = argv[2];
  const char* outputFileName = argv[3];

  std::ifstream input(inputFileName);
  if (!input.is_open()) {
    std::cerr << "Cannot open input file\n";
    return 1;
  }

  std::ofstream output(outputFileName);
  if (!output.is_open()) {
    std::cerr << "Cannot create output file\n";
    return 1;
  }

  try {
    size_t rows = 0;
    size_t cols = 0;
    if (!(input >> rows >> cols)) {
      std::cerr << "Cannot read matrix dimensions\n";
      return 2;
    }

    if (rows == 0 && cols == 0) {
      output << "0 0\n";
      return 0;
    }

    const size_t maxStaticSize = 10000;
    if (num == 1) {
      if (rows * cols > maxStaticSize) {
        std::cerr << "Matrix is too large for static array\n";
        return 2;
      }

      int matrix[maxStaticSize];
      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          size_t temp = 0;
          if (!(input >> temp)) {
            if (input.eof()) {
              std::cerr << "Not enough elements for matrix\n";
              return 2;
            } else if (input.fail()) {
              input.clear();
              std::cerr << "Unexpected input\n";
              return 2;
            }
          }
          const size_t maxInt = static_cast<size_t>(std::numeric_limits<int>::max());
          if (temp > maxInt) {
            std::cerr << "Number out of int range\n";
            return 2;
          }
          matrix[i * cols + j] = static_cast<int>(temp);
        }
      }

      const int resultMin = burukov::countLocalMinima(matrix, rows, cols);
      const int resultMax = burukov::countLocalMaxima(matrix, rows, cols);
      output << resultMin << '\n' << resultMax << '\n';
    } else {
      int* matrix = burukov::createMatrix(rows, cols);
      if (matrix == nullptr) {
        std::cerr << "Memory allocation failed\n";
        return 2;
      }
      
      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          size_t temp = 0;
          if (!(input >> temp)) {
            if (input.eof()) {
              burukov::destroyMatrix(matrix);
              std::cerr << "Not enough elements for matrix\n";
              return 2;
            } else if (input.fail()) {
              input.clear();
              burukov::destroyMatrix(matrix);
              std::cerr << "Unexpected input\n";
              return 2;
            }
          }
          const size_t maxInt = static_cast<size_t>(std::numeric_limits<int>::max());
          if (temp > maxInt) {
            burukov::destroyMatrix(matrix);
            std::cerr << "Number out of int range\n";
            return 2;
          }
          matrix[i * cols + j] = static_cast<int>(temp);
        }
      }

      const int resultMin = burukov::countLocalMinima(matrix, rows, cols);
      const int resultMax = burukov::countLocalMaxima(matrix, rows, cols);
      output << resultMin << "\n " << resultMax << "\n";
      burukov::destroyMatrix(matrix);
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 2;
  }

  return 0;
}