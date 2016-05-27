/* Dynamic programming.
 * MIT�Ĺ�������,����dijkstra�㷨�Ľ���˵,��ÿ�궼���ж�̬�滮���µ����.
 * PE����ô�����������: 
 * NOTE: This problem is a more challenging version of Problem 81.
 * ��Ȼ,���������һ����̬�滮����,��Ȼ,��dijkstra�㷨�����·�㷨Ҳ���Խ��.
 * ����
 * http://www.mathblog.dk/project-euler-82-find-the-minimal-path-sum-from-the-left-column-to-the-right-column/
 * �ϸ����Ķ�̬�滮�㷨ȷʵ���ҶԶ�̬�滮�������µ����.
 */
 
#include <vector>
#include <algorithm>

static const int LEN = 80;
typedef std::vector<std::vector<int> > Matrix;

extern void ReadMatrix(Matrix* arr);

int solve_82()
	{
	Matrix arr;
	ReadMatrix(&arr);

	/*
	 * ������ⲻͬ��problem 81�ĵط�����,�����������ƶ�,�����Ĳ�������һ�����������Ķ�̬�滮:
	 * ����һ������,result,��������±��Ǳ�����,ֵ���Ǵ���һ�е����һ�е����·��.
	 */
	std::vector<int> result(LEN);
	
	/*
	 * ��ʼ�����result,result�д洢���Ǵ�LEN - 1�е�LEN - 1�е���̳���,Ҳ���ǵ�LEN - 1�е�ֵ.
	 */
	for(int i = 0; i < LEN; ++i)
		result[i] = arr[i][LEN - 1];
	/*
	 * �ӵ����ڶ��п�ʼ����.
	 */
	for(int i = LEN - 2; i >= 0; --i)
		{
		/*
		 * ��ʼ��result�ĵ�0�±��Ԫ��,��Ϊ�����λ����,����ֻ�����һ�������,����ĳ�ʼ��������
		 * ���ҵ����.���µĽ��ں���ĵ����п���.
		 */
		result[0] += arr[0][i];

		/*
		 * ��result�ĵ�1���±꿪ʼ,�Ƚϴ�ʱ���ϵ�·������:result[j - 1] + arr[j][i](����㱾���ֵ),
		 * ��ֱ�����ҵ�ֵ,arr[j][i] + result[j],ǰ���Ѿ�˵��result[j]������,���ǵ������Ǵӵ�j�е�
		 * LEN - 1�е���С����.
		 */
		for(int j = 1; j < LEN; ++j)
			result[j] = std::min(result[j - 1] + arr[j][i], result[j] + arr[j][i]);

		/*
		 * ����ĵ������Կ��������µĵ���,ÿ�αȽ����Һ����ϵ�ֵ.
		 * ������ϵ���,�Ƚ����Һ����µ�ֵ.
		 * ��Ϊ���һ�в������µ���,ֻ�����ϻ�������,�����ֵ,������ĵ����о��Ѿ������.
		 * ���,�ӵ�����2�п�ʼ,����������ϻ������ҵ�����Ѿ��������,���,���Ǹ�ֵ,�Ƚ��ڴ�ʱ
		 * ���µ�ֵ�Ĵ�С.ȡ��Сֵ,�������ֵ.
		 */
		for(int j = LEN - 2; j >= 0; --j)
			result[j] = std::min(result[j + 1] + arr[j][i], result[j]);
		}
	/*
	 * ����,result�д洢���Ǵ�(0,LEN)�еĵ�0�е�LEN - 1�е���Сֵ,�����������Сֵ,���Ǵ�!
	 */
	return *std::min_element(result.begin(), result.end());
	}

