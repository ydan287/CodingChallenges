#include <string>
#include <iostream>

using namespace std;

int getCharNumber(char c)
{
  if (c <= 'Z' & c >= 'A')
  {
    c = c - 'A' + 'a';
  }
  return c - 'a';
}

void pelindromPermutation(string s)
{
  int isLetterOdd = 0;
  int numberOfOdds = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] < 'A' || s[i] > 'z')
    {
      continue;
    }
    int index = getCharNumber(s[i]);
    int mask = 1 << index;
    if (!(isLetterOdd & mask))
    {
      isLetterOdd |= mask;
    }
    else
    {
      isLetterOdd &= ~mask;
    }
  }
  if (isLetterOdd & (isLetterOdd - 1))
  {
    cout << s << ": False " << numberOfOdds << endl;
  }
  else
  {
    cout << s << ": True " << numberOfOdds << endl;
  }
};

int main(int argc, char const *argv[])
{
  // atcocta
  pelindromPermutation("tact coas");
  pelindromPermutation("Tact oCa");
  pelindromPermutation("aa");
  pelindromPermutation("aab");
  pelindromPermutation("aabc");
  pelindromPermutation("s");
  pelindromPermutation("aa1b23");
  return 0;
}
