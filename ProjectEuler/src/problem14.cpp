unsigned GetTheStartingNumberUnder1000000WhichProducesTheLongestChain()
{
	const int limit = 1000000;
	//缓存之前的结果，大大的提高了运行速度。
	//键就是要查找的值，值是要查找的值需要进行多少步迭代。
	int *hashtable = new int[limit];

	for(int i = 0; i < limit; ++i)
		hashtable[i] = 0;

	int count = 0;
	int result = limit;

	for(int i = 2; i < limit; ++i)
	{
		unsigned val = i;
		int length = 1;
		while(val != 1)
		{
			if(val % 2 == 0)
				val /= 2;
			else
				val = (3 * val + 1) / 2;
			++length;
			if(val < limit && hashtable[val] != 0)
			{
				length += hashtable[val];
				break;
			}
		}
		hashtable[i] = length;
		if(length > count)
		{
			count = length;
			result = i;
		}
	}
	delete []hashtable;
	return result;
}