#include <vector>
#include <algorithm>
#include <iostream>

int Triangle(int n)	{ return (n * (n + 1) / 2); }
int Square(int n) { return (n * n); }
int Pentagonal(int n) { return (n * (3 * n - 1) / 2);}
int Hexagonal(int n) { return (n * (2 * n - 1)); }
int Heptagonal(int n) { return (n * (5 * n - 3) / 2); }
int Octagonal(int n) {return (n * (3 * n - 2)); }

const int DEPTH = 6;
typedef std::vector<int> array_t;
typedef std::vector<array_t> matrix_t;
typedef int (*function)(int);
matrix_t matrix;

static int buffer[DEPTH];
static int fmt[DEPTH] = {0, 1, 2, 3, 4, 5};

static
void initMatrix()
	{
	function funcs[] = {Triangle, Square, Pentagonal, Hexagonal, Heptagonal, Octagonal};
	for(int i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i)
		{
		int dummy = funcs[i](0);
		for(int j = 1; dummy < 10000; ++j, dummy = funcs[i](j))
			if(dummy > 999)
				matrix[i].push_back(dummy);
		}
	}

static 
bool checkPrev(int first, int last)
	{
	return (first % 100 == last / 100);
	}

static
void dfs(int cur, int depth)
	{
	if(depth == DEPTH)
		{
		if(checkPrev(buffer[depth - 1], buffer[0]))
			{
			int sum = 0;
			for(int i = 0; i < DEPTH; ++i)
				sum += buffer[i];
			throw int(sum);
			}
		}
	else
		for(size_t i = 0; i < matrix[fmt[depth]].size(); ++i)
			{
			buffer[depth] = matrix[fmt[depth]][i];
			
			if(depth == 0 || checkPrev(buffer[depth - 1], buffer[depth]))
				dfs(cur + 1, depth + 1);
			}
	}
static
int callDfs()
	{
	try{ do { dfs(0, 0); }while (std::next_permutation(fmt, fmt + DEPTH));}
	catch(int result) {	return result; }
	return -1;
	}

int GetTheSumOfAllTheOnlyOrderedSetOf6Cyclic4DigitNumbersForWhichEachPolygonalTypeIsRepresentedByADifferentNumberInTheSet()
	{
	matrix.resize(6);
	initMatrix();
	return callDfs();
	}

