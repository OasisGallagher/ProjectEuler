/************** Solution  1: Use STL next_permutation to try one by one ***************/
/*
static void
Swap(char* left, char* right)
	{
	char temp = *left;
	*left = *right;
	*right = temp;
	}

static void
Reverse(char* first, char* last)
	{
	char* mid = first + (last - first) / 2;
	--last;
	for(int i = 0; i != mid - first; ++i)
		Swap(first + i, last - i);
	}

static bool
NextPermutation(char* first, int len)
	{
	char* last = first + len;
	char* next = last;
	if(first == last || first == (--next))	// Less than 2 elements.
		return false;

	for(; ; )
		{ // Find the rightmost element less than it's successor.
		char* next2 = next;
		if(*(--next) < *next2)
			{	// Containes answer.
			char* mid = last;
			for(; *(--mid) <= *next; )	// Find the right most element less than next.
				;

			Swap(next, mid);
			// Range from next2 to last must be pure descending. Flip it.
			Reverse(next2, last);
			return true;
			}

		if(next == first)
			{ // Pure descending, flip all.
			Reverse(first, last);
			return false;	// No answer.
			}
		}
	}

char*
GetTheMillionthLexicographicPermutationOfTheDigits0123456789()
	{
	const int len = 10;
	static char buffer[len + 1];
	for(int i = 0; i < len; ++i)
		buffer[i] = '0' + i;
	buffer[len] = 0;
	int count = 1;
	
	while(NextPermutation(buffer, len) && ++count < 1000000)
		;
	return buffer;
	}
*/

/**************************************	Solution 2 **************************************/
/* Base on http://www.mathblog.dk/project-euler-24-millionth-lexicographic-permutation/ 
 * and http://projecteuler.net/thread=24
 * I'm not sure how md2perpe did it, but when I was developing this problem I initially solved it by hand.
 * We know that there are n! permutations for n distinct digits and, as we're working in lexicographical order, 
 * after 9! permutations the ten digit string will have become: 0987654321. The 9!+1 permutation will be 1023456789, 
 * the 2*9!+1=725761 permutation will be 2013456789. However, the 3*9!+1 permutation (3012456789) will be greater than one million.
 * So we now consider the permutations of the last nine digits, 013456789: 6*8!+1 will take it to 701345689. 
 * We have now computed 967681 permutations and arrived at the number 2701345689. Then we look at the last eight digits, 
 * and work out that a further 6*7!+1 takes it to the string 2780134569 and a total of 997921 permutations...
 * Once I discovered this method, and rather than continue by hand, I wrote a programme to complete this (tedious) task for any 
 * given number of permutations. 
 */
int 
Factorial(int n)
	{
	int result = 1;
	while(n != 0)
		result *= (n--);
	return result;
	}

void
CopyBackwards(char* dest, char* src, int sizeInByte)
	{
	// Do not use size_t to iterate backward.
	for(--sizeInByte; sizeInByte >= 0; --sizeInByte)
		dest[sizeInByte] = src[sizeInByte];
	}

char*
GetTheMillionthLexicographicPermutationOfTheDigits0123456789()
	{
	const int numberCount = 10;
	const int nthElement = 1000000;

	int eleCount = numberCount;
	int nth = nthElement;
	
	static char buffer[numberCount];

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
	return buffer;
	}
