#include <fstream>

#define GSize	  9
#define GridCount (GSize * GSize)
static int grid[9][9];
#define Row(depth)		(depth / GSize)
#define Col(depth)		(depth % GSize)
#define IsEmpty(depth)	(grid[Row(depth)][Col(depth)] == 0)
#define Set(depth, val)	(grid[Row(depth)][Col(depth)] = val)

static bool check(int depth, int number)
{
	int row = Row(depth), col = Col(depth);

	for(int i = 0; i < 9; ++i)
		if(i != row && grid[i][col] == number)
			return false;

	for(int i = 0; i < 9; ++i)
		if(i != col && grid[row][i] == number)
			return false;

	row /= 3; row *= 3; col /= 3; col *= 3;

	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
		{
			int posX = row + i, posY = col + j;
			if((posX != Row(depth) || posY != Col(depth)) && grid[posX][posY] == number)
				return false;
		}
	return true;
}

static bool solveSudoku(int depth)
{
	if(depth >= GridCount)
		return true;
	else
	{
		if(!IsEmpty(depth))	// occupied.
			return solveSudoku(depth + 1);
		for(int i = 1; i < 10; ++i)
		{
			Set(depth, i);
			if(check(depth, i) && solveSudoku(depth + 1))
				return true;
			
			Set(depth, 0);
		}
	}
	return false;
}

int solve_96()
{
	std::ifstream ifs("sudoku.txt");
	char buffer[16] = { 0 };
	int result = 0;
	while(ifs.getline(buffer, _countof(buffer)))
	{
		for(int i = 0; i < 9; ++i)
		{
			ifs.getline(buffer, _countof(buffer));
			for(int j = 0; j < 9; ++j)
				grid[i][j] = buffer[j] - '0';
		}
		solveSudoku(0);
		int tmp = 0;
		for(int i = 0; i < 3; ++i)
			tmp = tmp * 10 + grid[0][i];
		result += tmp;
	}
	return result;
}