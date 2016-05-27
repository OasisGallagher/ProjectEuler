#include <iostream>
#include "hdr.h"
#include <cassert>

static void reflect(Vector& start, Vector& impact) {
	// let k be the slope of the reflect line.
	// since the reflect line pass through the impact point.
	// the reflect line will be:
	// y - impact.y = k(x - impact.x).
	// combine this with the ellipse: 4xx + yy = 100, we get:
	// let X = x^2, Y = y^2, K = k^2.
	// 4X + K(x - impact.x)^2 + 2k * impact.y(x - impact.x) + (impact.y)^2 - 100 = 0.....(1)
	// since the ellipse pass through impact, =>
	// 4*(impact.x)^2 + impact.y^2 = 100 =>
	// impact.y^2 - 100 = -4 * impact.x^2.
	// (1) will be:
	// 4X + K(x - impact.x)^2 + 2k * impact.y(x - impact.x) - 4 * impact.x^2 = 0. =>
	// 4(X - impact.x^2) + K(x - impact.x)^2 + 2k * impact.y(x - impact.x) = 0. =>
	// 4(x + impact.x)(x - impact.x) + K(x - impact.x)^2 + 2k * impact.y(x - impact.x) = 0 =>
	// divide (x - impact.x), let x != impact.x(x = impact.x is one solution of this equation).
	// =>
	// 4(x + impact.x) + K(x - impact.x) + 2k * impact.y = 0 =>
	// x = (-4 * impact.x + K * impact.x - 2 * k * impact.y) / (4 + K).
	double fromslope = (start - impact).slope();
	double tangentslope = -4.0 * impact.x / impact.y;
	tangentslope = (2.0 * tangentslope) / (1.0 - tangentslope * tangentslope);
	double k = (tangentslope - fromslope) / (1.0 + tangentslope * fromslope);

	Vector next;
	next.x = (-4.0 * impact.x + k * k * impact.x - 2.0 * k * impact.y) / (4.0 + k * k);
	next.y = k * (next.x - impact.x) + impact.y;

	start = impact;
	impact = next;
}

int main() {
	Vector start(0, 10.1), impact(1.4, -9.6);
	int times = 0;
	for(; impact.y < 0 || fabs(impact.x) > 0.01; ++times) {
		reflect(start, impact);
		std::cout << "impact (" << impact.x << ", " << impact.y << ").\n";
	}

	std::cout << times << std::endl;
}

#if 0	// it works, but is too complicated.
static inline bool dbleq(double x, double y) {
	return fabs(x - y) < 0.00001;
}

static void reflect(Vector& start, Vector& impact) {
	// vector from impact to start.
	Vector impact2start(start - impact);
	// slope of the tangent.
	double k = -4 * impact.x / impact.y;
	// slope of the normal line.
	k = -1 / k;
	// y = kx + impact.y - k * impact.x.
	// vector of the normal line.
	Vector normal(0, impact.y - k * impact.x);
	normal -= impact;
	double len_mul = impact2start.length() * normal.length();
	double c = (normal * impact2start) / len_mul;
	double s = (normal ^ impact2start) / len_mul;

	// normal line lies on the clockwise of from.
	bool clockwise = (s > 0);
	s = fabs(s);

	if(clockwise) s = -s;

	double c2 = 2 * c * c - 1;
	double s2 = 2 * c * s;

	Vector impact2mirror(impact2start.x * c2 - impact2start.y * s2, impact2start.x * s2 + impact2start.y * c2);

	start = impact;

	double a = impact2mirror.y / impact2mirror.x;
	double b = impact.y - a * impact.x;
	double dt = 4 * a * a * b * b - 4 * (b * b - 100) * (4 + a * a);
	dt = sqrt(dt);
	double x = (-2 * a * b + dt) / (2 * (4 + a * a));
	double y = a * x + b;
	if(dbleq(x, impact.x) && dbleq(y, impact.y)) {
		x = (-2 * a * b - dt) / (2 * (4 + a * a));
		y = a * x + b;
	}
	assert(!dbleq(x, impact.x) || !dbleq(y, impact.y));
	impact.x = x;
	impact.y = a * x + b;

	assert(dbleq(100, 4 * impact.x * impact.x + impact.y * impact.y));
}
#endif