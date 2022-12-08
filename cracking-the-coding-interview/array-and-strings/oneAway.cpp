#include <string>
#include <iostream>

using namespace std;

void oneAwayALonger(string A, string B)
{
  int replace = 0;
  int removes = 0;
  for (int ai = 0; ai <= A.size(); ++ai)
  {
    if (A[ai] != B[ai - removes])
    {
      if (replace + removes > 0)
      {
        cout << "A: " << A << " B: " << B << " result: False" << endl;
        return;
      }
      if (A.size() > B.size())
      {
        removes++;
      }
      else
      {
        replace++;
      }
    }
  }

  cout << "A: " << A << " B: " << B << " result: True" << endl;
}

void oneAway(string A, string B)
{

  A.size() >= B.size() ? oneAwayALonger(A, B) : oneAwayALonger(B, A);
}

int main(int argc, char const *argv[])
{
  oneAway("pale", "ple");
  oneAway("pales", "pale");
  oneAway("pale", "bale");
  oneAway("pale", "bake");
  return 0;
}
