#include <fstream>
#include <vector>

typedef std::vector<int> array_t;
typedef std::vector<array_t> triangle_t;
extern int Max(int, int);
const char* FILE_NAME = "triangle.txt";

static
void getTriangleNumbers(triangle_t* triangle)
	{
	int count = 1;
	std::ifstream ifs(FILE_NAME);
	for(; ; ++count)
		{
		array_t arr;
		for(int i = 0; i < count; ++i)
			{
			int tmp = -1;
			ifs >> tmp;
			if(!ifs)
				break;
			arr.push_back(tmp);
			}
		if(!ifs)
			break;

		triangle->push_back(arr);
		}
	}

int GetMaxPathSumII()
	{
	triangle_t triangle;
	getTriangleNumbers(&triangle);

	const int limit = 100 - 1;
	for(int i = limit; i != 0; --i)
		{
		for(int j = 0; j < i; ++j)
			triangle[i - 1][j] += Max(triangle[i][j], triangle[i][j + 1]);
		}
	return triangle[0][0];
	}
