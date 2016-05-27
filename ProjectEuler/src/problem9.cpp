// Another solution:
// a = 2mn, b = m^2 - n^2, c = m^2 + n^2.
// so 4(m^2)(n^2) - 2(m^2)(n^2) = 2(m^2)(n^2).
// so:
// 2mn + 2m^2 = 1000
// mn + m^2 = 500
// m(m + n) = 500
// a < c => 2mn < m^2 + n^2 => (m - n)^2 > 0 => m > n.
// n is not greater than m, so, m * ( m + m ) > 500, m ^ 2 > 250, m > 15.8.
// n is not less than 0, so m * m < 500, m < 22.4.
// that is 16 <= m <= 22.

int GetTheProductOfOnePythagoreanTripletForWhichAPlusBPlusCEqualsTo1000()
{
	for(int m = 16; m < 23; ++m)
		for(int n = 1; n < m; ++n)
		{
			if(m * (m + n) == 500)
				return 2 * m * n * ((m * m * m * m) - (n * n * n * n));
		}
	return 0;
}
