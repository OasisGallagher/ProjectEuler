// �����Ӽ��������뵽λ���㣬ǰ��������У��õ�������������һ����n��Ԫ�ص������Ӽ���������
// i��0��(1 << n)��ʼ���������λ�������Ӽ���
// ������������ƣ�������Ҫע����ǣ�һ������ֻ��6���棬�������Ҫ��֤����Ӽ�һ������
// 6��Ԫ�ء�
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
	{	// ѭ��������number�Ķ����Ʊ�ʾ�к���1�ĸ�����ͬ,���������ע�͵��ķ���.
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
	{	// ����������������Ҫ����,û��ѭ��,����λ����. http://bbs.bccn.net/thread-365855-1-1.html
	// ���Ȱ�32λ�ֳ�16��,ÿ��������,���������ÿ����������һ���ж��ٸ�1,��˶���ÿһ��,
	// ���1������n&010101...01,�ұ���(n>>1) & 0101..01. ���һ�κ�,��16��ÿ�ݴ�Ķ���ԭ����1�ĸ���.
	// ֮��16�ݱ�8��,8�ݱ�4��,ֱ�����1��.

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
