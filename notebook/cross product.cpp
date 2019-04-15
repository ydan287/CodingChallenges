struct PT {
	double x;
	double y;
};

//intput 3 points a -> b -> c
//output: cross prduct:
//	if cross > 0 - a->b->c is a left turn
//	if cross < 0 - a->b->c is a right turn
// if cross = 0 - a-> b-> c is one segment - c is on the segment a-b.

double cross_product(PT a, PT b, PT c) {
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}