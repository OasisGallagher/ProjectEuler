#include <iostream>
#define BUFF_SIZE	(3000)
typedef int Number;

static inline bool isps(const Number& number)
{
	Number tmp = (Number)ceil(sqrt((double)number));
	return tmp * tmp == number;
}

static inline Number solve142() {
	Number buffer[BUFF_SIZE];
	// 缓存一些完全平方数.
	for(unsigned i = 1; i <= BUFF_SIZE; ++i)
		buffer[i - 1] = Number(i) * i;
	// x + y = a, x + z = b, y + z = c .. a > b > c.	(1)
	// x - z = d, x - y = e, y - z = f.					(2)
	// 将x, y, z, d, e, f用a, b, c表示, 再枚举a, b, c.	(3)
	// 由1可知, 2(x + y + z) = a + b + c. 因此, 求出来的第一个a, b, c组合就是最小的x + y + z.
	for(unsigned pa = 2; pa < BUFF_SIZE; ++pa) {
		for(unsigned pb = 0; pb < pa; ++pb) {
			for(unsigned pc = 0; pc < pb; ++pc) {
				Number x = (buffer[pa] + buffer[pb] - buffer[pc]);
				if(x < 0 || x % 2 != 0) continue;
				x /= 2;

				Number y = (buffer[pa] - buffer[pb] + buffer[pc]);
				if(y < 0 || y % 2 != 0) continue;
				y /= 2;

				Number z = (buffer[pc] - buffer[pa] + buffer[pb]);
				if(z < 0 || z % 2 != 0) continue;
				z /= 2;

				if(!isps(buffer[pb] - buffer[pc]) || !isps(buffer[pa] - buffer[pc]) || !isps(buffer[pa]- buffer[pb])) continue;
				return x + y + z;
			}
		}
	}

	return 0;
}

int main() {
	std::cout << "result is " << solve142() << std::endl;
	return 0;
}
