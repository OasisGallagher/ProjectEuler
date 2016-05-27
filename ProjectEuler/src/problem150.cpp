#include <iostream>
#include <ctime>
#include <cmath>

typedef __int64 Number;
#define MaxSize	500500
int buffer[MaxSize];
/*= {
	15, -14, -7, 20, -13,
	-5, -3, 8, 23, -26,
	1, -4, -5, -18, 5,
	-16, 31, 2, 9, 28,
	3
};
*/

// preCalSum[k] contains sum of array [0, k).
// preCalSum[j] - preCalSum[i] = sum of array [i, j).
Number preCalSum[MaxSize + 1];

void Generate() {
	int mod = (int)pow(2.f, 20);
	Number t = 0;
	preCalSum[0] = 0;
	for(int i = 1; i <= MaxSize; ++i) {
		t = (615949 * t + 797807) % mod;
		buffer[i - 1] = int(t - mod / 2);
		if(i >= 2) {
			preCalSum[i - 1] = preCalSum[i - 2] + buffer[i - 2];
		}
	}
	
	preCalSum[MaxSize] = preCalSum[MaxSize - 1] + buffer[MaxSize - 1];
}

#define GetStart(Line)	((Line - 1) * Line / 2)

#ifndef MAX_VALUE
#define MAX_VALUE 9223372036854775807i64
#endif

Number GetMinValue() {
	Number result = MAX_VALUE;
	const int lineCount = 1000;
	for(int line = 1; line <= lineCount; ++line) {
		int counter = line;
		for(int startpos = GetStart(line); counter-- > 0; ++startpos) {
			int numcount = 1;
			Number sum = 0;
			int countstart = startpos;
			for(int nextline = line; nextline <= lineCount; ++nextline) {
				sum += (preCalSum[countstart + numcount] - preCalSum[countstart]);
				result = std::min(sum, result);

				++numcount;
				countstart += nextline;
			}
		}
	}
	return result;
}

int main() {
	clock_t beg = clock();
	Generate();
	std::cout << GetMinValue() << std::endl;
	std::cout << (clock() - beg) / float(CLOCKS_PER_SEC) << " second(s)\n";
}
