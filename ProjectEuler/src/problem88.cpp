#include <cmath>
#include <set>
#include <numeric>
#include <ctime>

#define Sqrt(X)				(int)(sqrt((double)X))
// ���׹�ʾ��log2Ϊ�׵Ķ�����
#define Log2(X)				((int)(log((double)X) / log(2.0)))
#define LIMIT	12000

// ����k,product-sum�����ֵ���ᳬ��2k,��Ϊ���������k,������һ��product-sumΪ2k,
// Ȼ��,�����2k - k - 1��1,�Ϳ��Գ�Ϊ���������ϵ�product-sum��.
#define BOUND	LIMIT * 2

static int result[LIMIT + 1];

static void subGetProc(int curDepth, int targetDepth, int* sum, int* mul, int lastStat = 1)
	{
	if(curDepth > targetDepth)
		{
		int tmp = *mul - *sum + targetDepth;
		if(tmp <= LIMIT)
			result[tmp] = std::min(result[tmp], *mul);
		}
	else if(curDepth != -1)		//��һ�ε���ʱ,curDepthΪ-1,�Ա����forѭ��.
		{
		if(curDepth == 1)	//ѭ���ĵ�һ��.
			*sum = 0, *mul = 1;
		for(int i = lastStat; i < BOUND; ++i)
			{
			int thisMul = *mul, thisSum = *sum;
			int tmp = thisMul * i;
			if(tmp > BOUND)
				break;
			thisMul = tmp;
			thisSum += i;
			subGetProc(1 + curDepth, targetDepth, &thisSum, &thisMul, i);
			}
		}
	else
		{
		for(int i = 2; i <= targetDepth; ++i)
			subGetProc(1, i, sum, mul);
		}
	}

int solve_88()
	{
	std::fill(result, result + LIMIT + 1, INT_MAX);
	int loopDepth = Log2(BOUND);	// �������ɶ��ٸ�2��ˡ�
	int sum = 0, mul = 1;
	subGetProc(-1, loopDepth, &sum, &mul);
	std::set<int> tmp(result + 2, result + LIMIT + 1);
	return std::accumulate(tmp.begin(), tmp.end(), 0);
	}

