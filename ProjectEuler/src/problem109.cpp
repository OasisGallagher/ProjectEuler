#include <vector>

// 1: ����һ��doubleֵ,��������������ϾͿ�����.
typedef std::vector<int> Vector;
static const int MaxCheckOut = 100 - 1;

static const int MaxSize = 20 * 3 + 2;

static int count(int sum, int cur, int deepth, const Vector& arr)
{
	int result = 0;
	if(sum <= MaxCheckOut)
	{
		++result;
		if(deepth < 3)
			for(int i = cur; i < MaxSize; ++i)
				result += count(sum + arr[i], i, deepth + 1, arr);
	}

	return result;
}

int solve_109()
{
	Vector coin;
	coin.reserve(MaxSize);

	for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= 20; ++j)
			coin.push_back(i * j);

	coin.push_back(25);
	coin.push_back(50);

	int result = 0;
	// double-out 2k.
	for(int i = 2; i <= 40; i += 2)
		result += count(i, 0, 1, coin);
	// double-out 50.
	result += count(50, 0, 1, coin);

	return result;
}

#if 0	// �Լ��İ취,����,���Ǻܱ�.
#include <iterator>
#include <algorithm>
#include <map>
typedef std::map<int, int> Hash;
static Vector init_coin(Hash& hash, Vector& one_try)
{	// prepare coins.��ʼ��,����¼ֻ��һ��Ͷ���Ļ�,ÿ��ֵ�ж����ַ���.
	Vector singles, doubles, triples;

	for(int i = 1; i <= 20; ++i)
		singles.push_back(i);
	singles.push_back(25);

	for(Vector::iterator ite = singles.begin(); ite != singles.end(); ++ite)
	{
		doubles.push_back((*ite) * 2);
		triples.push_back((*ite) * 3);
	}
	triples.pop_back();
	Vector total;
	std::copy(singles.begin(), singles.end(), std::back_inserter(total));
	std::copy(doubles.begin(), doubles.end(), std::back_inserter(total));
	std::copy(triples.begin(), triples.end(), std::back_inserter(total));

	one_try.clear();
	one_try.resize(MaxCheckOut + 1);
	hash.clear();

	for(Vector::iterator ite = total.begin(); ite != total.end(); ++ite)
	{
		Vector::value_type tmp = *ite;
		++hash[tmp];
		++one_try[tmp];
	}

	return doubles;
}

static int ways_count(int bound, /*const */Hash& hash, Vector ways, const Vector& doubles)
{	// count the ways. hash is contant, but it's not convinent for operator[].
	// ways is a copy.
	// ��չ����1��2��Ͷ��,�ж����ַ���.
	Vector::value_type tmp = 0;
	for(Hash::const_iterator ite = hash.begin(); ite != hash.end() && (tmp = ite->first) < bound; ++ite)
	{
		for(int i = tmp + 1; i < bound; ++i)
		{	// use a 'tmp', target must be larger than 'tmp'.
			// add 1 for 3; 1, 2 for 4; 1, 2 for 5.
			// so, tmp is not larger than floor(i / 2).
			if(tmp <= i / 2)
			{
				if(tmp == i - tmp)
					ways[i] += (hash[tmp] + 1) * hash[tmp] / 2;
				else
					ways[i] += (hash[tmp] * hash[i - tmp]);
			}
		}
	}
	// 1,2��3��Ͷ��,һ�ο϶��Ǹ�double,������������������ֵ.
	int result = 0;
	for(Vector::const_iterator ite = doubles.begin(); ite != doubles.end(); ++ite)
	{
		int tmp = bound - *ite;
		if(tmp < 0)	// doubles is an increasing sequence.
			break;

		if(tmp > 0)
			result += ways[tmp];
		else	// tmp == 0
			++result;
	}
	return result;
}

int solve_109()
{
	Hash hash;
	Vector ways;
	Vector doubles = init_coin(hash, ways);

	int result = 0;
	for(int limit = 1; limit <= MaxCheckOut; ++limit)
	{
		result += ways_count(limit, hash, ways, doubles);
	}
	return result;
}
#endif