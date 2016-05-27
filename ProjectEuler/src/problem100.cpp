// 2b^2 - 2b = t^2 - t, 求整数解.
// 两个未知数, 方程形如:
// aX^2 + bXY + cY^2 + dX + eY + f = 0
// 求整数解的问题, 叫做: quadratic(二次) diophantine(丢番图) equation(方程).
// 这个地址给出了该方程的解法.
// http://www.alpertron.com.ar/QUAD.HTM
// ./solve100.docx给出这个问题的特定解法。
/**
	Xn+1 = P * Xn + Q * Yn + K
	Yn+1 = R * Xn + S * Yn + L

	P = 3
	Q = 2
	K = -2
	R = 4
	S = 3
	L = -3
**/

typedef __int64 i64_t;
static const int P = 3;
static const int Q = 2;
static const int K = -2;
static const int R = 4;
static const int S = 3;
static const int L = -3;

i64_t solve_100()
{
	i64_t b_x = 15, t_y = 21;
	for(; t_y < 1000000000000i64; )
	{
		i64_t tmp_b_x = P * b_x + Q *t_y + K;
		i64_t tmp_t_y = R * b_x + S * t_y + L;

		b_x = tmp_b_x;
		t_y = tmp_t_y;
	}
	return b_x;
}
