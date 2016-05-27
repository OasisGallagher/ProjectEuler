#include <map>
#define cube(n) (n * n * n)
typedef unsigned long long ulonglong;
struct code
	{
	code(ulonglong ull)
		{
		for(buffer = 0i64; ull != 0; ull /= 10) selfAdd(ull % 10);
		}
	void selfAdd(int here)
		{
#ifdef USE_BINARY	//Each digit count can be up to 15(inclusive).Cos' we use 4 bits to save.
		// Get the bits in [here * 4, here * 4 + 4).
		// Then Right shift it to generate an regular number.
		ulonglong tmp = ((buffer & (0xFi64 << here * 4)) >> here * 4);
		// Self add.
		++tmp;
		// Clear the bits in [here * 4, here * 4 + 4).
		for(int i = here * 4; i < here * 4 + 4; ++i)
			buffer &= ~(ulonglong(1i64 << i));
		// Assign bits to [here * 4, here * 4 + 4).
		buffer |= (tmp << here * 4);
#else	// Each digit's count must be less equal to 9.For this problem, it's enough.
		ulonglong fmt = 1;
		for(int i = 0; i < here; ++i) fmt *= 10;
		buffer += fmt;
#endif
		}
	bool operator < (const code& other)const{ return buffer < other.buffer; } 
	ulonglong buffer;
	};

ulonglong GetTheSmallestCubeForWhichExactlyFivePermutationsOfItsDigitsAreCube()
	{
	std::map<code, int> table;
	code result(0);
	for(ulonglong i = 500; ;++i)
		if(++table[code(cube(i))] == 5)
			{
			result.buffer = code(cube(i)).buffer;
			break;
			}
	// Any good idea to avoid this? 
	//I really don't want to calculate cube numbers twice.
	for(ulonglong i = 500; ; ++i)
		if(code(cube(i)).buffer == result.buffer)
			return cube(i);
	return 0xFFFFFFFFFFFFFFFF;
	}
