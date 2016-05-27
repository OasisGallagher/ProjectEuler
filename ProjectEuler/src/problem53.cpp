#define LIMIT			1000000
#define INFINITE		LIMIT + 1

int GetCountWithYangHuiTriangle()
	{
	const int length = 5050 + 101;

	int* arr = new int[length];
	arr[0] = 1;
	int result = 0;
	int cur = 1;

	for(int step = 1; step < 101; ++step)
		{
		for(int i = 0; i <= step; ++i)
			{
			if(i == 0 || i == step)
				arr[cur] = 1;
			else
				{
				arr[cur] = arr[cur - step] + arr[cur - step - 1];
				if(arr[cur] > LIMIT)
					arr[cur] = INFINITE, ++result;
				}
			++cur;
			}
		}

	delete []arr;
	return result;
	}

int GetTheNumberOfValueOfCNRFor1LessEqualToNAndNLessEqualTo100AreGreaterThan1000000()
	{
	return GetCountWithYangHuiTriangle();
	}
