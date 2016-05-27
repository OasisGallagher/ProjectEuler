#include <vector>
#include <numeric>
// 关于这道题的题目的意思:
// 拿4个数来说,1, 2, 3, 4
// 可能的组合,两个组合都是1个数的话:
// 1 - 2
// 1 - 3
// 1 - 4
// 2 - 3
// 2 - 4
// 3 - 4
// 共有C(4,2) = 6种方法.
// 因为有:
// For this problem we shall assume that a given set contains n strictly increasing 
// elements and it already satisfies the second rule.
// 即所有的元素都是不同的,所以都是1个元素的时候肯定是可以的,不用检查子集合的相等性,他们必然不等.
// 又因为条件2:
// If B contains more elements than C then S(B) > S(C).
// 在题设中就已经满足,所以对于元素个数不同的两个子集也不用检查相等性,他们必然不等.
// 继续上面的讨论,当两个子集都是2个元素时:
// 1,2 - 3,4	(1)
// 1,3 - 2,4	(2)
// 2,3 - 1,4	(3)
// 对(1)来说,1<3,2<4,即对应位置的元素都是按照统一的大小关系的,因此也不用再检查相等性了.这点
// 对(2)依然成立.
// 但是对(3)来说,2>1,但是3<4,因此这个需要检查相等性.
// 所以对于4个数,需要检查的子集合组合数为1.

// number中有多少个1(二进制).
extern unsigned one_count(unsigned number);

// 清除number的最后一个1,并返回这个1在原number中的0索引的位置.
// 如果number中没有1或者number<0,那么返回-1.
static int EraseLastOne(int& number)
{
	int pos = -1;
	if(number <= 0)
		return pos;

	for(; !((1 << pos) & number); ++pos)
		;

	number &= (number - 1);
	return pos;
}

int solve_106()
{
	const int NumberCount = 12;
	int result = 0;
	std::vector<int> vec(NumberCount, 1);
	std::partial_sum(vec.begin(), vec.end(), vec.begin());

	const int Limit = 1 << NumberCount;
	for(int i = 0; i < Limit; ++i)
	{
		for(int j = i + 1; j < Limit; ++j)
		{
			if(i & j) continue;
			if(one_count(i) != one_count(j)) continue;
			if(one_count(i) == 1) continue;

			int tmp_i = i, tmp_j = j;
			int pos1 = EraseLastOne(tmp_i), pos2 = EraseLastOne(tmp_j);
			if(pos1 == -1 || pos2 == -1) continue;

			bool xbool = vec[pos1] < vec[pos2];
			for(; tmp_i != 0 && tmp_j != 0;)
			{
				pos1 = EraseLastOne(tmp_i), pos2 = EraseLastOne(tmp_j);
				if(vec[pos1] < vec[pos2] != xbool)
				{
					++result;
					break;
				}
			}
		}
	}
	return result;
}

// 这个问题似乎可以用排列组合的方法来解决.
