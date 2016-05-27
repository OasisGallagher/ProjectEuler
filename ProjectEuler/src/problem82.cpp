/* Dynamic programming.
 * MIT的公开课中,讲述dijkstra算法的教授说,他每年都会有动态规划有新的理解.
 * PE上这么描述这个问题: 
 * NOTE: This problem is a more challenging version of Problem 81.
 * 显然,这个问题是一个动态规划问题,当然,用dijkstra算法等最短路算法也可以解决.
 * 但是
 * http://www.mathblog.dk/project-euler-82-find-the-minimal-path-sum-from-the-left-column-to-the-right-column/
 * 上给出的动态规划算法确实让我对动态规划又有了新的理解.
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
	 * 这个问题不同于problem 81的地方在于,它允许向上移动,上述的博主用了一个类似这样的动态规划:
	 * 声明一个数组,result,这个数组下标是表格的列,值就是从这一列到最后一列的最短路径.
	 */
	std::vector<int> result(LEN);
	
	/*
	 * 初始化这个result,result中存储的是从LEN - 1列到LEN - 1列的最短长度,也就是第LEN - 1列的值.
	 */
	for(int i = 0; i < LEN; ++i)
		result[i] = arr[i][LEN - 1];
	/*
	 * 从倒数第二列开始迭代.
	 */
	for(int i = LEN - 2; i >= 0; --i)
		{
		/*
		 * 初始化result的第0下标的元素,因为在这个位置上,我们只能向右或者向下,这里的初始化考虑了
		 * 向右的情况.向下的将在后面的迭代中考虑.
		 */
		result[0] += arr[0][i];

		/*
		 * 从result的第1个下标开始,比较此时向上的路径长度:result[j - 1] + arr[j][i](这个点本身的值),
		 * 和直接向右的值,arr[j][i] + result[j],前面已经说过result[j]的意义,表是的正巧是从第j列到
		 * LEN - 1列的最小长度.
		 */
		for(int j = 1; j < LEN; ++j)
			result[j] = std::min(result[j - 1] + arr[j][i], result[j] + arr[j][i]);

		/*
		 * 上面的迭代可以看成是向下的迭代,每次比较向右和向上的值.
		 * 这次向上迭代,比较向右和向下的值.
		 * 因为最后一行不能向下迭代,只能向上或者向右,而这个值,在上面的迭代中就已经完成了.
		 * 因此,从倒数第2列开始,从这个点向上或者向右的情况已经计算过了,因此,用那个值,比较在此时
		 * 向下的值的大小.取最小值,更新这个值.
		 */
		for(int j = LEN - 2; j >= 0; --j)
			result[j] = std::min(result[j + 1] + arr[j][i], result[j]);
		}
	/*
	 * 最终,result中存储的是从(0,LEN)行的第0列到LEN - 1列的最小值,再找这里的最小值,就是答案!
	 */
	return *std::min_element(result.begin(), result.end());
	}

