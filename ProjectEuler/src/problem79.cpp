// By hand.
// An easy approach is to analyse the text and write down them in order they displayed.
// 7 must be the first number, and 0 the last, as for 5 and 4, which are not present.
// Further more, in order to get a shortest string, we also assume that no number appears
// twice. It's quite easy to get the answer: 73162890.

// An alg:
#include <fstream>
#include <iostream>
#include <algorithm>

static char* find(char arr[], char what)
	{
	for(size_t i = 0; ; ++i)
		if(arr[i] == what)
			return arr + i;
	throw "invalid char or string!";
	return NULL;
	}

static void sort3(char* ptr[3])
	{
	if(ptr[0] > ptr[1])
		std::iter_swap(ptr[0], ptr[1]);

	if(ptr[0] > ptr[2])
		std::iter_swap(ptr[0], ptr[2]);
	
	if(ptr[1] > ptr[2])
		std::iter_swap(ptr[1], ptr[2]);
	}

const char* solve_79()
	{
// Assume that no number appears twice.
	static char str[] = "01236789";

	for(std::ifstream ifs("keylog.txt"); ifs; )
		{
		int number;
		ifs >> number;
		
		int sieve = 100;
		char* ptr[3];
		char** cur = ptr;
		for(; sieve != 0; number %= sieve, sieve /= 10)
			{
			try {
			*cur++ = find(str, number / sieve + '0');
			}
			catch(...){
				return "fatal error !";
				}
			}

		sort3(ptr);
		}
	return str;
	}
