#include "tools/MyMatrix.h"
using namespace std;

int main()
{
  Matrix m = Matrix<int>::eye(3);
  cout<<m.toString();
}