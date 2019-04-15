#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

int main() {
	int nx, ny;
	double w;
	vector<string> results;
	while (1) {
		cin >> nx;
		cin >> ny;
		cin >> w;
		if (nx == 0 && ny == 0 && w == 0) break;
		list<double> l1;
		list<double> l2;
		for (int i = 0; i < nx; ++i) {
			double tmp;
			cin >> tmp;
			l1.push_back(tmp);
		}
		l1.sort();
		for (int i = 0; i < ny; ++i) {
			double tmp;
			cin >> tmp;
			l2.push_back(tmp);
		}
		l2.sort();
		if (*(l1.begin()) - 0.5*w > 0) {
			results.push_back("NO");
			continue;
		}
		double max = *(l1.begin()) + 0.5*w;
		for (list<double>::iterator i = l1.begin(); i != l1.end(); ++i) {
			if (max >= *i - 0.5*w) max = *i + 0.5*w;
		}
		if (max < 75) {
			results.push_back("NO");
			continue;
		}
		if (*(l2.begin()) - 0.5*w > 0) {
			results.push_back("NO");
			continue;
		}
		max = *(l2.begin()) + 0.5*w;
		for (list<double>::iterator i = l2.begin(); i != l2.end(); ++i) {
			if (max >= *i - 0.5*w) max = *i + 0.5*w;
		}
		if (max < 100) {
			results.push_back("NO");
			continue;
		}
		results.push_back("YES");
	}
	for (vector<string>::iterator i = results.begin(); i != results.end(); ++i) {
		cout << *i << endl;
	}
	
}