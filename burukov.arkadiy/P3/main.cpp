#include "iostream"
#include <cstddef>
#include <cstdlib>

namespace burukov
{
  void destroyMatrix(int* matrix);
  int* createMatrix(size_t rows, size_t cols);
  int countLocalMinima(const int* matrix, size_t rows, size_t cols);
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




int main()
{

}