#include <cstdio>

double ExpectedNumber(int cA2, int cA3, int cA4, int cA5, int cSingle, double probility) {
	int cSheet = cA2 + cA3 + cA4 + cA5;
	double result = 0.0;
	if(cSheet == 1) {
		if(cA5 == 1) {
			return probility * cSingle;
		}

		// count of single sheet.
		++cSingle;
	}

	// 'cut in half'.
	if(cA2 > 0)
		result += ExpectedNumber(cA2 - 1, cA3 + 1, cA4 + 1, cA5 + 1, cSingle, probility * cA2 / cSheet);
	if(cA3 > 0) 
		result += ExpectedNumber(cA2, cA3 - 1, cA4 + 1, cA5 + 1, cSingle, probility * cA3 / cSheet);
	if(cA4 > 0)
		result += ExpectedNumber(cA2, cA3, cA4 - 1, cA5 + 1, cSingle, probility * cA4 / cSheet);
	if(cA5 > 0) 
		result += ExpectedNumber(cA2, cA3, cA4, cA5 - 1, cSingle, probility * cA5 / cSheet);

	return result;
}

int main() {
	printf("%lf\n", ExpectedNumber(1, 1, 1, 1, 0, 1.0));
}
