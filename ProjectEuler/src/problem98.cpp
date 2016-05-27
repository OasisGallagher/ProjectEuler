#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <deque>

// 读取出所有的单词，然后去掉有重复字母的单词，并将单词按照各个字母所含字母，不考虑顺序，
// 作为键，保存在map里。
// 接着构造完全平方数，根据数字的位数，找到map中位数相同的字符串，并按照字符串的顺序进行
// 字典序并检查是不是完全平方数。

typedef std::map<int, std::vector<std::string> > Dictionary;
typedef std::map<int, std::vector<int> > IntegerDict;
typedef int Code;
#define InvalidCode		-1
#define Sqrt(Int)	(int)sqrt(double(Int))

static Code encode(const std::string& str)
{
	Code result = 0;
	for(std::string::const_iterator ite = str.begin(); ite != str.end(); ++ite)
	{
		Code old = result;
		result |= (1 << (*ite - 'a'));
		if(old == result)
			return InvalidCode;
	}
	return result;
}

int format_number(const std::string& from, const std::string& to, int number)
{
	std::deque<int> tmp;
	for(; number != 0; number /= 10)
		tmp.push_front(number % 10);

	std::vector<int> result(tmp.size(), 0);
	for(size_t i = 0; i < from.length(); ++i)
		result[to.find(from[i])] = tmp[i];

	int dig = 0;
	for(std::vector<int>::iterator ite = result.begin(); ite != result.end(); ++ite)
		dig = dig * 10 + *ite;
	return dig;
}

static int count_code(Code code)
{
	int result = 0;
	for(int i = 0; i < 26; ++i)
		result += ((code & (1 << i)) != 0);
	return result;
}

static int read_words(Dictionary* lpResult)
{
	int maxLength = 0;
	Dictionary& result = *lpResult;
	for(std::ifstream ifs("words98.txt"); ifs; )
	{
		char tmp[32] = { 0 };
		ifs.get(tmp, _countof(tmp), ',');
		int len = std::string(tmp).length() - 2;
		std::string str = std::string(tmp + 1).substr(0, len);

		Code code = encode(str);
		if(code != InvalidCode)
		{
			result[code].push_back(str);
		}
		ifs.ignore();
	}

	for(Dictionary::iterator ite = result.begin(); ite != result.end(); )
	{
		if(ite->second.size() <= 1)
			result.erase(ite++);
		else
			++ite;
	}

	for(Dictionary::iterator ite = result.begin(); ite != result.end(); ++ite)
		maxLength = std::max(maxLength, count_code(ite->first));

	return maxLength;
}

static inline int pow(int x, int y)
{
	return y == 0 ? 1 : x * pow(x, y - 1);
}

static int count_digit(int number)
{
	int result = 0;
	for(; number != 0; number /= 10, ++result)
		;
	return result;
}

static bool valid(int number)
{
	unsigned tmp = 0;
	for(; number != 0; number /= 10)
	{
		unsigned prev = tmp;
		tmp |= (1 << (number % 10));
		if(prev == tmp)
			return false;
	}
	return true;
}

static inline bool perfect_square(int number)
{
	int tmp = Sqrt(number);
	return tmp * tmp == number;
}

int solve_98()
{
	typedef std::vector<std::string>::iterator Iterator;
	Dictionary dict;

	int sieve = pow(10, read_words(&dict));
	int result = 0;
	const int Limit = Sqrt(sieve);
	for(int i = 2; i < Limit; ++i)
	{
		int check = i * i;
		if(!valid(check))
			continue;
		
		int digCount = count_digit(check);
		for(Dictionary::iterator ite = dict.begin(); ite != dict.end(); ++ite)
		{
			if(count_code(ite->first) == digCount)
			{
				std::vector<std::string> &vec = ite->second;

				for(size_t i = 1; i < vec.size(); ++i)
				{
					int next = format_number(vec[0], vec[i], check);

					if(count_digit(next) != count_digit(check))	// leading zero.
						continue;

					if(perfect_square(next))
					{
						result = std::max(result, next);
						result = std::max(result, check);
					}
				}
			}
		}
	}
	return result;
}
