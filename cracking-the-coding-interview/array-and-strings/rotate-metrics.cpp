
#include <iostream>

using namespace std;

#define N 5

void printMetrix(int metrix[N][N])
{
  for (int r = 0; r < N; r++)
  {
    for (int c = 0; c < N; c++)
    {
      cout << metrix[r][c] << ", \t";
    }
    cout << endl;
  }
  cout << endl;
}

void SwapValue(int &a, int &b)
{
  int t = a;
  a = b;
  b = t;
}

void rotateMetrix(int metrix[N][N])
{
  for (int r = 0; r < N - r ; r++)
  {
    for (int c = r; c < N - 1 - r; c++)
    {
      cout << "r: " << r << " c: " << c << endl;
      printMetrix(metrix);
      swap(metrix[r][c], metrix[c][N - 1 - r]);
      swap(metrix[r][c],  metrix[N - 1 - r][N - 1 - c]);
      swap(metrix[r][c],  metrix[N - 1 - c][r]);
    }

  }
  printMetrix(metrix);
}

int main(int argc, char const *argv[])
{
  int metrix[N][N] = {1, 2, 3, 4, 5,
                      6, 7, 8, 9, 10,
                      11, 12, 13, 14, 15,
                      16, 17, 18, 19, 20,
                      21, 22, 23, 24, 25};
  rotateMetrix(metrix);

  /* code */
  return 0;
}
