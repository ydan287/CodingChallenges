#include <iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <random>
#include <numeric>
#include <vector>
#include <string>
using namespace std;

struct trieNode {
	unordered_map<char, trieNode*> sons;
	int cnt;
	trieNode() {
		sons.clear();
		cnt = 0;
	}
};

int postOrder(trieNode& curr) {
	int sum = 0;
	if (!curr.sons.empty()) {
		for (auto it : curr.sons) {
			sum += postOrder(*it.second);
		}
	}
	if (curr.cnt - sum >= 2)
		sum+=2;
	delete &curr;
	return sum;
}

int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		int N;
		cin >> N;
		trieNode* root = new trieNode();
		root->cnt = 0;
		for (int i = 0; i < N; i++)
		{
			string tmp;
			cin >> tmp;
			trieNode* curr = root;
			for (auto it = tmp.rbegin(); it != tmp.rend(); ++it) {
				if (curr->sons.find(*it) == curr->sons.end()) {
					curr->sons[*it] = new trieNode();
				}
				curr = curr->sons[*it];
				curr->cnt += 1;
			}
		}
		printf("Case #%d: %d\n", tc, postOrder(*root));
	}
	
	return 0;
}