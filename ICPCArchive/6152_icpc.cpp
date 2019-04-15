#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;
int find_min_moves(string s, string t) {
	int moves = 0;
	list<int> question_marks;
	for (int i = 0; i < s.length(); ++i) {
		if (s == t) return moves;
		else if (s[i] == t[i]) continue;
		else if (s[i] == '0') {
			int j;
			for (j = i + 1; j < s.length(); ++j) {
				if (s[j] == '1' && t[j] == '0') {
					s[j] = '0';
					s[i] = '1';
					moves++;
					break;
				}
			}
			if (j == s.length()) {
				s[i] = '1';
				moves++;
			}
		}
		else if (s[i] == '1') {
			int j;
			for (j = i + 1; j < s.length(); ++j) {
				if (s[j] == '0' && t[j] == '1') {
					s[j] = '1';
					s[i] = '0';
					moves++;
					break;
				}
			}
			if (j == s.length()) {
				for (j = i + 1; j < s.length(); ++j) {
					if (s[j] == '?' && t[j] == '1') {
						s[i] = '0';
						s[j] = '1';
						moves += 2;
						break;
					}
				}
			}
		}
		else {
			question_marks.push_back(i);
		}
	}
	for (list<int>::iterator i = question_marks.begin(); i != question_marks.end(); ++i) {
		if (t[*i] == '0') {
			s[*i] = '0';
			moves++;
		}
		else {
			int j;
			for (j = *i + 1; j < s.length(); ++j) {
				if (s[j] == '1' && t[j] == '0') {
					s[*i] = '1';
					s[j] = '0';
					moves += 2;
					break;
				}
			}
			if (j == s.length()) {
				s[*i] = '1';
				moves++;
			}
		}
	}

	return (s == t) ? moves : -1;
}

int main() {
	int C;
	cin >> C;
	list<int> l;
	for (int i = 0; i < C; ++i) {
		string s, t;
		cin >> s;
		cin >> t;
		l.push_back(find_min_moves(s, t));
	//	l.push_back(recursive(s, t, 0));
	}
	int i = 1;
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it) {
		cout << "Case " << i++ << ": " << *it << endl;
	}


}
/*
1
??11101
1101111

*/