#include <fstream>
#include <math.h>

#pragma warning(disable:4996)

static bool
IsTriangleWord(const char* str)
	{
	int count = 0;
	
	for(int i = 1; str[i] != '\"'; ++i)
		count += (str[i] - 'A' + 1);

	//n^2+n=2*count. 
	int d = 1 + 8 * count;
	int t = (int)sqrt((double)d);
	return t * t == d;
	}

int GetTheCountOfTriangleWordsInTheFileNamedWordsDotTxt()
	{
	const int wordMaxLength = 32;
	char buffer[8192][wordMaxLength];

	const char* fileName = "words.txt";
	std::ifstream ifs(fileName);
	int i = 0;

	for(; ifs; ++i)
		{
		ifs.get(buffer[i], wordMaxLength, ',');
		ifs.ignore();	// Ignore ','.
		}
	
	int result = 0;
	for(int j = 0; j < i; ++j)
		result += IsTriangleWord(buffer[j]);

	return result;
	}
