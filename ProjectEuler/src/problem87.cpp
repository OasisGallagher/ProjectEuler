#include <bitset>
#include <algorithm>
#include <cmath>
#include <cstdio>
#pragma warning(disable:4244)	// Assign __int64 to int.

#define LIMIT			50000000
#define Square(x)		(((__int64)x) * (x))
#define Sqrt(x)			((int)sqrt((double)x))

extern int GetPrimeList(int len, int *buffer);

int solve_87()
	{
	int primeCount = Sqrt(LIMIT);
	int* primeBuffer = new int[primeCount];
	primeCount = GetPrimeList(primeCount, primeBuffer);

	bool* hash = new bool[LIMIT]();
	
	__int64* buffer[3];
	for(int i = 0; i < 3; ++i)
		buffer[i] = new __int64[primeCount];
	
	for(int i = 0; i < primeCount; ++i)
		{
		buffer[0][i] = Square(primeBuffer[i]);
		buffer[1][i] = buffer[0][i] * primeBuffer[i];
		buffer[2][i] = buffer[1][i] * primeBuffer[i];
		}
	delete []primeBuffer;
	
	int result = 0;
	for(int x = 0; x < primeCount; ++x)
		{
		for(int y = 0; y < primeCount; ++y)
			{
			for(int z = 0; z < primeCount; ++z)
				{
				const __int64 TMP = 
					buffer[0][x] + buffer[1][y] + buffer[2][z];

				if(TMP >= LIMIT) break;

				if(!hash[TMP])
					{
					hash[TMP] = true;
					++result;
					}
				}
			}
		}

	delete []hash;
	for(int i = 0; i < 3; ++i)
		delete[] buffer[i];

	return result;
	}