#include <ctime>
#include <iostream>

#define Width	2000
#define Length	2000
static int buffer[Width * Length];

static int MaxSumOfSubLine(int from, int to) {
	int result = INT_MIN;
	int prev = 0;

	for(; from < to; ++from) {
		if(prev > 0)
			prev += buffer[from];
		else
			prev = buffer[from];
		result = std::max(prev, result);
	}
	return result;
}

static int Generate() {
	int linemax = INT_MIN;
	for(size_t i = 1; i <= Width * Length; ++i) {
		if(i < 56)
			buffer[i - 1] = ((100003i64 - 200003i64 * i + 300007i64 * i * i * i) % 1000000 - 500000);
		else
			buffer[i - 1] = ((buffer[i - 24 - 1] + buffer[i - 55 - 1] + 1000000) % 1000000 - 500000);
		
		if(i % Length == 0)
			linemax = std::max(linemax, MaxSumOfSubLine(i - Length, i));
	}

	return linemax;
}

static int MaxSumOfSubCol() {
	int maxvalue = INT_MIN;
	for(int i = 0; i < Length; ++i) {
		int prev = 0;
		for(int j = i; j < Length * Width; j += Length) {
			if(prev > 0)
				prev += buffer[j];
			else
				prev = buffer[j];
			maxvalue = std::max(prev, maxvalue);
		}
	}

	return maxvalue;
}

static int MaxSumOfDiagonal() {
	int result = INT_MIN;
	for(int first = 0; first < Length * Width; 
		first += (first != (Length - 1) && first % Length != (Length - 1)) ? 1 : Length) {
		int prev = 0;

		for(int next = first; ;) {
			int __tmp = buffer[next];
			if(prev > 0)
				prev += buffer[next];
			else
				prev = buffer[next];
			result = std::max(prev, result);
			if(first == 0 || first == Length * Width - 1) break;
			if(next != first && (next % Length == 0 || next / Width == Width - 1)) break;

			next += (Length - 1);
		}
	}

	return result;
}

static int MaxSumOfAntiDiagonal() {
	int result = INT_MIN;
	int prev = 0;

	for(int first = (Width - 1) * Length; first != (Length - 1);
		first -= (first != 0 && first % Length == 0) ? Length : (-1)) {
		
		prev = 0;
		for(int next = first; ; ) {
			int __tmp = buffer[next];
			if(prev > 0)
				prev += buffer[next];
			else
				prev = buffer[next];
			result = std::max(prev, result);

			if(first == (Width - 1) * Length || first == Length - 1) break;
			if(next != first && (next / Width == Width - 1 || next % Length == Length - 1)) break;

			next += (Length + 1);
		}
	}

	if(prev > 0) prev += buffer[Length - 1];
	else prev = buffer[Length - 1];

	return std::max(prev, result);
}

// 52852124
int main() {
	clock_t beg = clock();
	int maxvalue = Generate();
	maxvalue = std::max(maxvalue, MaxSumOfSubCol());
	maxvalue = std::max(maxvalue, MaxSumOfDiagonal());
	maxvalue = std::max(maxvalue, MaxSumOfAntiDiagonal());
	std::cout << maxvalue << std::endl;
	std::cout << float(clock() - beg) / CLOCKS_PER_SEC << " second(s)." << std::endl;
	return 0;
}