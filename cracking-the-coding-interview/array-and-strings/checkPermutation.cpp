#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void checkPermutation(string A, string B)
{
  unordered_map<char, int> histA;
  unordered_map<char, int> histB;
  if (A.size() != B.size())
  {
    cout << "Not Permutation" << endl;
  }
  for (int i = 0; i < A.size(); i++)
  {
    histA[A[i]] = histA.contains(A[i]) ? histA[A[i]] + 1 : 1;
    histB[B[i]] = histB.contains(B[i]) ? histB[B[i]] + 1 : 1;
  }

  for (int i = 0; i < A.size(); i++)
  {
    if (histA[A[i]] != histB[A[i]])
    {
      cout << "Not Permutation" << endl;
      return;
    }
  }
  cout << "Permutation" << endl;
}

int main()
{
  checkPermutation("abc", "cba");
  checkPermutation("", "hello");
  checkPermutation("aaaaabcc", "cbacaaaa");
  return 0;
}