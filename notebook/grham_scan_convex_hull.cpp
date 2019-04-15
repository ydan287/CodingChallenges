bool left(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3) {
	double cross = (p2.first - p3.first)*(p1.second - p3.second) - (p2.second - p3.second)*(p1.first - p3.first);
	if (fabs(cross) <= 1e-10) {
		return true;
	}
	if (cross > 0) {
	
		return true;
	}
	return false;
}

//put input in convex get output from convex_hull.
vector<pair<double, double>> convex;
vector<pair<double, double>> convex_hull;
void grhamScan() {
	convex_hull.clear();
	sort(convex.begin(), convex.end());
	vector < pair<double, double > >& lu = convex_hull;
	lu.push_back(convex[0]);
	lu.push_back(convex[1]);
	for (int i = 2; i < convex.size(); ++i) {
		lu.push_back(convex[i]);
		while (lu.size() > 2 && left(lu[lu.size() - 3], lu[lu.size() - 2], lu[lu.size() - 1])) {
			pair<double, double> tmp = lu.back();
			lu.pop_back();
			lu.pop_back();
			lu.push_back(tmp);
		}

	}
	vector < pair<double, double > > ll;
	ll.push_back(convex.back());
	ll.push_back(convex[convex.size() - 2]);
	for (int i = convex.size() - 3; i >= 0; --i) {
		ll.push_back(convex[i]);
		while (ll.size() > 2 && left(ll[ll.size() - 3], ll[ll.size() - 2], ll[ll.size() - 1])) {
			pair<double, double> tmp = ll.back();
			ll.pop_back();
			ll.pop_back();
			ll.push_back(tmp);
		}
	}
	for (int i = 1; i < ll.size() - 1; ++i) {
		lu.push_back(ll[i]);
	}
}

int main(){
	double x, y;
	while (cin >> x >> y) {
		if (x == -1) break;
		convex.push_back({ x,y });
	}
	grhamScan();
	for (int i = 0; i < convex_hull.size(); ++i) {
		cout << convex_hull[i].first << " " << convex_hull[i].second << endl;
	}
	return 0;
}