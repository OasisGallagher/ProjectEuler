#pragma once
#include <bitset>
#include <cassert>

#define _SieveSize(_Size)	((_Size >> 1) + 1)
#define _OddToPos(_Odd)		(((_Odd - 1) >> 1) - 1)
#define _IsEven(_Number)	((_Number & 1) == 0)
#define _IsOdd(_Number)		(!_IsEven(_Number))

template <unsigned _Size>
class PrSieve
{
public:
	PrSieve()
	{
		mSieve.flip();
		for(unsigned i = 3; i < _Size; i += 2)
		{
			unsigned pos = _OddToPos(i);
			if(mSieve[pos])
			{
				for(unsigned j = i + (i << 1); j < _Size; j += (i << 1))
				{
					unsigned p = _OddToPos(j);
					if(mSieve[p])
						mSieve[p] = false;
				}
			}
		}
	}
	bool IsPrime(unsigned _Number) const
	{
		return _IsEven(_Number) ? (_Number == 2) : mSieve[_OddToPos(_Number)];
	}
private:
	std::bitset<_SieveSize(_Size)> mSieve;
};