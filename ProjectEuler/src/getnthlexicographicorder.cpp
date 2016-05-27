#include <iostream>
#include <algorithm>

int 
Factorial(int n)
{
	int result = 1;
	while(n != 0)
	{
		result *= (n--);
	}
	return result;
}

void
CopyBackwards(char* dest, char* src, int sizeInByte)
{
	// Do not use size_t to iterate backward.
	for(--sizeInByte; sizeInByte >= 0; --sizeInByte)
		dest[sizeInByte] = src[sizeInByte];
}

bool
GetNthLexicographicOrder(int eleCount, int nth)
{
	if(eleCount > 10)
		eleCount = 10;
	const int elementCount = eleCount;
	char* buffer = new char[eleCount];
	char* BUFFER = buffer;
	for(int i = 0; i < eleCount; ++i)
		buffer[i] = '0' + i;
	char* cur = buffer;

	for(--nth; nth != 0 ;++cur)
	{
		int fac = Factorial(--eleCount);
		int count = nth / fac;
		
		if(count != 0)
		{
			char temp = *(cur + count);
			CopyBackwards(cur + 1, cur, count * sizeof(char));
			*cur = temp;
			nth -= count * fac;
		}
	}
	fwrite(buffer, 1, elementCount, stdout);
	printf("\n");

	delete[] BUFFER;
	return true;
}

int main()
{
	/*const int count = 10;
	int limit = Factorial(count);
	for(int i = 1; i <= limit; ++i)*/
	GetNthLexicographicOrder(10, 1000000);
}