/*
 * I DONOT KNOW HOW TO SOLVE THIS PROBLEM !
 */
#if 0
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>

#define BUF_LEN	255
#define ischar(_Int)	((_Int) >= 'a' && (_Int) <= 'z')

static inline
int decode(int number, char key[3], int cur)
	{
	return key[(cur % 3)] ^ number;
	}

static inline
void calcMax3(std::vector<int> number, char result[3])
	{
	std::vector<int>::iterator ite = std::max_element(number.begin(), number.end());
	result[0] = std::distance(number.begin(), ite);
	*ite = -1;
	
	ite = std::max_element(number.begin(), number.end());
	result[1] = std::distance(number.begin(), ite);
	*ite = -1;

	ite = std::max_element(number.begin(), number.end());
	result[2] = std::distance(number.begin(), ite);

	if(result[0] < result[1])
		std::swap(result[0], result[1]);
	if(result[0] < result[2])
		std::swap(result[0], result[2]);
	if(result[1] < result[2])
		std::swap(result[1], result[2]);
	}

static
void guessKey(char result[3])
	{
	for(int i = 0; i < 3; ++i)
		for(int j = 1; j < 256; ++j)
			{
			if(ischar(result[i] ^ j))
				result[i] ^= j;
			}

	if(result[0] > result[1])
		std::swap(result[0], result[1]);
	if(result[0] > result[2])
		std::swap(result[0], result[2]);
	if(result[1] > result[2])
		std::swap(result[1], result[2]);
	}

int GetTheSumOfASCIIValuesOfTheOriginalText()
	{
	std::vector<int> numbers;
	numbers.resize(BUF_LEN);

	std::ifstream ifs("cipher1.txt");
	std::string buffer((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	typedef std::string::size_type Size;
	
	Size offset = 0;
	for(Size pos = 0; (pos = buffer.find(',', offset)) != std::string::npos;
		offset = (pos + 1))
		{
		++numbers[atoi(buffer.substr(offset, pos - offset).c_str())];
		}

	++numbers[atoi(buffer.substr(offset, buffer.size() - offset - 1).c_str())];

	int numberCount = std::accumulate(numbers.begin(), numbers.end(), 0);

	char result[3];
	calcMax3(numbers, result);
	
	guessKey(result);

	std::swap(result[0], result[1]);
	std::swap(result[1], result[2]);

	int total = 0;
	ifs.seekg(0);
	int number;
	int i = 0;
	std::cout << result[0] << result[1] << result[2] << std::endl;
	while(ifs >> number)
		{
		std::cout << (char)(result[i % 3] ^ number);

		total += (char)(result[i % 3] ^ number);
		ifs.ignore();
		++i;
		}
	std::cout << std::endl;
	ifs.close();
	return total;
	}

#endif
