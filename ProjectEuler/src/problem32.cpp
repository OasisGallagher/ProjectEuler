#include <bitset>

bool IsPandigital(unsigned number)
	{
	std::bitset<10> bitset;

	for(; number != 0; )
		{
		unsigned remain = number % 10;
		if(remain == 0)
			return false;
		if(bitset[remain])
			return false;

		bitset[remain].flip();

		number /= 10;
		}

	return true;
	}

bool Overlapped(unsigned x, unsigned y)
	{
	// Both x and y won't contain 0.
	std::bitset<9> bitset;
	for(; x != 0; )
		{
		bitset[x % 10 - 1].flip();
		x /= 10;
		}
	for(; y != 0; )
		{
		if(bitset[y % 10 - 1])
			return true;
		bitset[y % 10 - 1].flip();
		y /= 10;
		}
	return false;
	}
bool SumNoOverlap(unsigned x, unsigned y, unsigned z)
	{
	// x, y and z won't contain 0.
	std::bitset<9> bitset;
	for(; x != 0; )
		{
		bitset[x % 10 - 1].flip();
		x /= 10;
		}
	for(; y != 0; )
		{
		bitset[y % 10 - 1].flip();
		y /= 10;
		}
	for(; z != 0; )
		{
		bitset[z % 10 - 1].flip();
		z /= 10;
		}
	bitset.flip();
	return bitset.none();
	}

#include <map>

unsigned GetTheSumOfAllProductsWhoseMultiplicandMultiplierProductIdentityCanBeWrittenAsA1Through9Pandigital()
	{
	unsigned result = 0;
	std::map<unsigned, bool> hashTable;

	for(unsigned x = 1; x < 9999; ++x)
		{
		if(!IsPandigital(x))
			continue;

		unsigned y = 1;
		for(; y < 9999; ++y)
			{
			unsigned mul = x * y;
			if(mul > 10000)
				break;

			if(!IsPandigital(y) || Overlapped(x, y))
				continue;
		
			if(IsPandigital(mul) && !Overlapped(x, mul) && !Overlapped(y, mul) && SumNoOverlap(x, y, mul))
				{
				if(!hashTable[mul])
					{
					hashTable[mul] = true;
					result += mul;
					}
				}
			}
		}
	return result;
	}
