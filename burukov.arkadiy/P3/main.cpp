#include "iostream"
#include <cstddef>
#include <cstdlib>

namespace burukov
{
  void destroyMatrix(int* matrix);
  int* createMatrix(size_t rows, size_t cols);
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


int main()
{

}