#include <fstream>
#pragma warning(disable:4996)

static void 
InsertSort(char buffer[8192][16], int count)
	{
	for(int i = 1; i < count; ++i)
		{
		char key[16];
		strcpy(key, buffer[i]);
		int j = i - 1;
		for(; j >= 0 && strcmp(buffer[j], key) > 0; --j)
			strcpy(buffer[j + 1], buffer[j]);
		strcpy(buffer[j + 1], key);
		}
	}

static int 
GetScore(const char* str, int number)
	{
	int score = 0;
	for(int i = 1; str[i] != '\"'; ++i)
		score += (str[i] - 'A' + 1);
	return number * score;
	}

long long int GetTheTotalOfAllTheNameScoresInTheFileNamedNamesTxt()
	{
	char buffer[8192][16];
	
	const char* fileName = "names.txt";
	std::ifstream ifs(fileName);
	int i = 0;
	
	for(; ifs; ++i)
		{
		ifs.get(buffer[i], 16, ',');
		ifs.ignore();	// Ignore ','.
		}

	InsertSort(buffer, i);
	long long int result = 0;
	for(int j = 0; j < i; ++j)
		result += GetScore(buffer[j], j + 1);

	return result;
	}
