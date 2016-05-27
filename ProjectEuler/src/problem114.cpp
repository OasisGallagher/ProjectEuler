#ifdef RecursiveCount
typedef char color;
static const color black = 1;
static const color red = -1;
static const color uninit = 0;

static __int64 recursive_count(int len, int from = 0, color last_color = uninit)
{
	__int64 result = 0;
	if(len < 0)
		return 0;
	if(len == 0)
		return 1;
	for(int block_len = 1; block_len <= len; ++block_len)
	{
		if(last_color != black)
			result += recursive_count(len - block_len, block_len + from, black);		// at least one black block.
		if(last_color != red)
			result += recursive_count(len - block_len - 2, block_len + from + 2, red);		// at least three red blocks.
	}
	return result;
}
#endif

__int64 dp_count(int len, int min_red)
{
	__int64* black_start = new __int64[len + 1](), *red_start = new __int64[len + 1]();
	black_start[0] = 1;
	red_start[0] = 1;

	for(int sub_len = 1; sub_len <= len; ++sub_len)
	{
		for(int from = 1; from <= sub_len; ++from)
		{
			// from之前的长度都是纯色,然后再增加其他颜色.
			// count_of_black[当前迭代总长度] = count_of_black[当前迭代总长度] + red_start[当前迭代总长度 - 当前开头的黑块的长度].
			// 黑块和红块必须分开.
			// 如果len - black_length == 0, 表示'len'长度的区块全部填满黑色,即red_start[0] = 1.
			black_start[sub_len] += red_start[sub_len - from];
			// 计算红块开头的方法总数.
			// 红色块至少为min_red.
			if(from >= min_red)
				red_start[sub_len] += black_start[sub_len - from];
		}
	}

	// 所有红块开始和黑块开始的和.
	__int64 result = black_start[len] + red_start[len];
	delete[] black_start;
	delete[] red_start;
	return result;
}

__int64 solve_114()
{
	return dp_count(50, 3);
}
