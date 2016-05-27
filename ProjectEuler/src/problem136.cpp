#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE		50000000 - 1
#define MOD_4(x)	(((x) & 3) == 0)
int main()
{
	clock_t beg = clock();
	char* ptr = new char[SIZE + 1];

	memset(ptr, 0, sizeof(char) * SIZE);

	int count = 0;

	for(int i = 1; i <= SIZE; ++i)
	{
		int mul;
		for(int j = 1; (mul = i * j) <= SIZE; ++j)
		{
			if(MOD_4(i + j) && (3 * j > i) && MOD_4(3 * j - i))
			{
				if(ptr[mul] == 0)
				{
					++count;
					ptr[mul] = 1;
				}
				else if(ptr[mul] == 1)
				{
					--count;
					ptr[mul] = -1;
				}
			}
		}
	}

	printf("%d\n", count);
	printf("%.2f second(s) elapsed.\n", (clock() - beg) / 1000.f);
	delete[] ptr;

	return 0;
}
