#include <iostream>
#include <bitset>
#include <sstream>
#include <set>
#include <algorithm>

static const int GRAPH_SIZE = 5;
static int outer[GRAPH_SIZE];
static int numbers[GRAPH_SIZE];
static std::bitset<GRAPH_SIZE * 2> sieve;
static std::set<std::string> set;

static inline bool tryLock(int number) { return !((bool)sieve[number - 1]); }
static inline void lock(int number) { sieve[number - 1] = true; }
static inline void unlock(int number) { sieve[number - 1] = false; }
static bool compare(const std::string& left, const std::string& right) 
	{ return left.compare(right) < 0; }

int next(int number = 1)
	{
	const int size = (int)sieve.size();
	for(; number <= size; ++number)
		{
		if(tryLock(number))
			{
			lock(number);
			return number;
			}
		}
	return -1;
	}

int check(int i, int expect)
	{
	for(int tmp = next(), from = 0; tmp != -1;)
		{
		if(numbers[i] + numbers[i - 1] + tmp == expect)
			{
			int sub = i - 1;
			if(sub < 0) sub = GRAPH_SIZE - 1;
			outer[sub] = tmp;
			return tmp;
			}
		unlock(tmp);
		tmp = next(tmp + 1);
		}
	return 0;
	}

void outputResult()
	{
	int minOuterIndex = 0;
	for(int i = 1; i < GRAPH_SIZE; ++i)
		if(outer[i] < outer[minOuterIndex])
			minOuterIndex = i;

	std::stringstream ss;
	for(int i = 0; i < GRAPH_SIZE; ++i, minOuterIndex = (minOuterIndex + 1) % GRAPH_SIZE)
		ss << outer[minOuterIndex] << numbers[minOuterIndex % GRAPH_SIZE]
	<< numbers[(minOuterIndex + 1) % GRAPH_SIZE];

	std::string tmp = ss.str();
	if(tmp.length() == 16)
		set.insert(tmp);
	}

void get_result(int depth, int dest)
	{
	if((depth == GRAPH_SIZE))
		{
		outer[GRAPH_SIZE - 1] = next();
		if(numbers[0] + numbers[GRAPH_SIZE - 1] + outer[GRAPH_SIZE - 1] == dest)
			outputResult();
		unlock(outer[GRAPH_SIZE - 1]);
		}
	else
		{
		for(int i = 1; i <= GRAPH_SIZE * 2; ++i)
			{
			if((numbers[depth] = next(i)) == -1)
				break;
			int tmp = -1;
			if(depth == 0 || (tmp = check(depth, dest)) != 0)
				get_result(depth + 1, dest);

			unlock(numbers[depth]);
			if(tmp > 0)
				unlock(tmp);
			}
		}
	}

std::string GetTheMaximum16DigitStringForAMagic5GonRing()
	{
	for(int i = 10; i < 20; ++i)get_result(0, i);
	return *(std::max_element(set.begin(), set.end(), compare));
	}

//////////////////////////////////////////////////////////////////////////
//////////////////////// Another solution: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
using namespace std;

// cd is short for convertDigit
inline int cd(int d)
	{
	return d==0 ? 10 : d;
	}

// How the array is laid out:
//    "6"
//      \
//       0    2
//      /  \ /
//     7    1
//    /|    |
//   8 5----3----4
//     |
//     6
//
// Trys all permutations of digits 0-9 (not inc 6, which is fixed)
// We know answer starts with 6 as it is the largest possible smallest
// outside digit
void Solve()
	{
	int p[] = {9,8,7,5,4,3,2,1,0};

	do
		{
		// 10 (ie our 0) can't be on an inside node,
		// otherwise string would be 17 chars, not 16.
		if ( p[0]==0 || p[1]==0 || p[3]==0 || p[5]==0 || p[7]==0 )
			continue;

		// Outside nodes must not be less than 6
		if (cd(p[2]) < 6 || cd(p[4]) < 6 || cd(p[6]) < 6 || cd(p[8]) < 6 )
			continue;

		int x = 6 + cd(p[0]) + cd(p[1]);
		if ( cd(p[2])+cd(p[1])+cd(p[3]) != x )
			continue;
		if ( cd(p[4])+cd(p[3])+cd(p[5]) != x )
			continue;
		if ( cd(p[6])+cd(p[5])+cd(p[7]) != x )
			continue;
		if ( cd(p[8])+cd(p[7])+cd(p[0]) != x )
			continue;

		cout << "Solution Found - sum=" << x << ": ";
		cout << "6" << cd(p[0]) << cd(p[1]);
		cout << cd(p[2]) <<	cd(p[1]) <<	cd(p[3]);
		cout << cd(p[4]) <<	cd(p[3]) << cd(p[5]);
		cout << cd(p[6]) <<	cd(p[5]) << cd(p[7]);
		cout << cd(p[8]) << cd(p[7]) << cd(p[0]);
		cout << endl;
		// Can either finish here, or continue loop to see if there are any
		// more solutions. First one found will be the largest. That's why
		// I'm searching in reverse order
		}
		while( prev_permutation( &p[0], &p[9] ) );
	}