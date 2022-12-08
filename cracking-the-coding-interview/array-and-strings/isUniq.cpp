#include <string>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

void isUniq(string s)
{
  bitset<26> histogram;
  for (int i = 0; i < s.size(); ++i)
  {
    int c = s[i] - 'a';
    if (histogram[c])
    {
      cout << "Not uniq" << endl;
      return;
    }
    histogram[c] = true;
  }
  cout << "Uniq" << endl;
  return;
}

int main()
{
  isUniq("");
  isUniq("hello");
  isUniq("helo");
  return 0;
}