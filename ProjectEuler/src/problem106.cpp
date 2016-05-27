#include <vector>
#include <numeric>
// ������������Ŀ����˼:
// ��4������˵,1, 2, 3, 4
// ���ܵ����,������϶���1�����Ļ�:
// 1 - 2
// 1 - 3
// 1 - 4
// 2 - 3
// 2 - 4
// 3 - 4
// ����C(4,2) = 6�ַ���.
// ��Ϊ��:
// For this problem we shall assume that a given set contains n strictly increasing 
// elements and it already satisfies the second rule.
// �����е�Ԫ�ض��ǲ�ͬ��,���Զ���1��Ԫ�ص�ʱ��϶��ǿ��Ե�,���ü���Ӽ��ϵ������,���Ǳ�Ȼ����.
// ����Ϊ����2:
// If B contains more elements than C then S(B) > S(C).
// �������о��Ѿ�����,���Զ���Ԫ�ظ�����ͬ�������Ӽ�Ҳ���ü�������,���Ǳ�Ȼ����.
// �������������,�������Ӽ�����2��Ԫ��ʱ:
// 1,2 - 3,4	(1)
// 1,3 - 2,4	(2)
// 2,3 - 1,4	(3)
// ��(1)��˵,1<3,2<4,����Ӧλ�õ�Ԫ�ض��ǰ���ͳһ�Ĵ�С��ϵ��,���Ҳ�����ټ���������.���
// ��(2)��Ȼ����.
// ���Ƕ�(3)��˵,2>1,����3<4,��������Ҫ��������.
// ���Զ���4����,��Ҫ�����Ӽ��������Ϊ1.

// number���ж��ٸ�1(������).
extern unsigned one_count(unsigned number);

// ���number�����һ��1,���������1��ԭnumber�е�0������λ��.
// ���number��û��1����number<0,��ô����-1.
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

// ��������ƺ�������������ϵķ��������.
