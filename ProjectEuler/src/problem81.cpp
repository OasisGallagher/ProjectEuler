#include <vector>
#include <fstream>

typedef std::vector<std::vector<int> > Matrix;
static const int LEN = 80;
static Matrix arr;
static Matrix mins(LEN);

void ReadMatrix(Matrix* dest)
	{
	std::ifstream ifs("matrix.txt");

	for(int i = 0; i < 80; ++i)
		{
		std::vector<int> tmp;
		for(int j = 0; j < 80; ++j)
			{
			int integer;
			ifs >> integer;
			tmp.push_back(integer);
			ifs.ignore();
			}
		dest->push_back(tmp);
		}
	}
// I just wonder, is this dijkstra algorithm actually?
static void dijkstra(int sum, int i, int j)
	{
	if(i >= LEN || j >= LEN)return;

	sum += arr[i][j];
	if(sum < mins[i][j])
		{
		mins[i][j] = sum;
		dijkstra(sum, i, j + 1);
		dijkstra(sum, i + 1, j);
		}
	}

int solve_81()
	{
	ReadMatrix(&arr);
/*__ Dynamic Programming
	for(int i = LEN - 2; i >= 0; --i)
		arr[LEN - 1][i] += arr[LEN - 1][i + 1];

	for(int i = LEN - 2; i >= 0; --i)
		arr[i][LEN - 1] += arr[i + 1][LEN - 1];

	for(int i = LEN - 2; i >= 0; --i)
		for(int j = LEN - 2; j >= 0; --j)
			arr[i][j] += min(arr[i][j + 1], arr[i + 1][j]);

	return arr[0][0]; */

// __ Dijkstra algorithm.
	for(int i = 0; i < LEN; ++i)
		mins[i].resize(LEN, INT_MAX);

	dijkstra(0, 0, 0);

	return mins[LEN - 1][LEN - 1];
	}
