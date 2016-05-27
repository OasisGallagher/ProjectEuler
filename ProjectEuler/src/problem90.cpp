// 生成子集，可以想到位运算，前面的问题中，用到过，比如生成一个含n个元素的所有子集的做法。
// i从0到(1 << n)开始迭代，检查位，产生子集。
// 这里的做法类似，但是需要注意的是，一个骰子只有6个面，因此我们要保证这个子集一定含有
// 6个元素。
#define NUM_MAX		10	// [0, 9]
// static bool contains6s(unsigned number)
// 	{
// 	unsigned result = 0;
// 	for(unsigned i = 0; i < 10; ++i)
// 		result += (0 != ((1 << i) & number));
// 	return result == 6;
// 	}
/*
static bool contains6s(unsigned number)
	{	// 循环次数与number的二进制表示中含有1的个数相同,优于上面的注释掉的方法.
	// 'number &= (number - 1)' erases the rightmost 1 in number.
	unsigned count = 0;
	for(; number != 0; number &= (number - 1), ++count)
		;
	return count == 6;
	}
*/

unsigned one_count(unsigned number)
	{
	number = (number & 0x55555555) + ((number >> 1) & 0x55555555);
	number = (number & 0x33333333) + ((number >> 2) & 0x33333333);
	number = (number & 0x0F0F0F0F) + ((number >> 4) & 0x0F0F0F0F);
	number = (number & 0x00FF00FF) + ((number >> 8) & 0x00FF00FF);
	return number = (number & 0x0000FFFF) + ((number >> 16) & 0x0000FFFF);
	}

static bool contains6s(unsigned number)
	{	// 这个比上面的两个还要优秀,没有循环,都是位运算. http://bbs.bccn.net/thread-365855-1-1.html
	// 首先把32位分成16份,每份两个数,我们先求出每相邻两个数一共有多少个1,如此对于每一份,
	// 左边1个数是n&010101...01,右边是(n>>1) & 0101..01. 如此一次后,这16份每份存的都是原数中1的个数.
	// 之后16份变8份,8份变4份,直到变成1份.

	return one_count(number) == 6;
	}
static inline bool non0_dig(unsigned who, unsigned which)
	{
	return 0 != (who & (1 << which));
	}

static inline bool check_helper(unsigned number1, unsigned number2, unsigned dig1, unsigned dig2)
	{
	return (non0_dig(number1, dig1) && non0_dig(number2, dig2)) 
		|| (non0_dig(number2, dig1) && non0_dig(number1, dig2));
	}

int solve_90()
	{
	const int BOUND = 1 << NUM_MAX;
	int result = 0;
	for(unsigned i = 0; i < BOUND; ++i)
		{
		if(!contains6s(i)) continue;
		for(unsigned j = i; j < BOUND; ++j)
			{
			if(contains6s(j))
				result += (check_helper(i, j, 0, 1)
				&& check_helper(i, j, 0, 4)
				&& (check_helper(i, j, 0, 9) || check_helper(i, j, 0, 6))
				&& (check_helper(i, j, 1, 6) || check_helper(i, j, 1, 9))
				&& check_helper(i, j, 2, 5)
				&& (check_helper(i, j, 3, 6) || check_helper(i, j, 3, 9))
				&& (check_helper(i, j, 4, 9) || check_helper(i, j, 4, 6))
				&& (check_helper(i, j, 6, 4) || check_helper(i, j, 9, 4))
				&& check_helper(i, j, 8, 1)
				);
			}
		}
	return result;
	}
