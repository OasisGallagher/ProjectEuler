struct xpair { 
	enum Color{ Black = 0, Red, Green, Blue, ColorCount };
	void set(int c, int len) { color = Color(c); seg_len = len; }
	Color	color;
	int		seg_len;
};

static void init_segs(xpair segs[xpair::ColorCount])
{
	for(int i = xpair::Black; i < xpair::ColorCount; ++i)
		segs[i].set(i, i + 1);
}

static __int64 solve(__int64* buffer[xpair::ColorCount], int row_length, const xpair segs[xpair::ColorCount])
{
	for(int sub_len = 1; sub_len <= row_length; ++sub_len)
	{
		// from == len时,整个条形都是纯色.
		for(int from = 1; from <= sub_len; ++from)
		{
			for(int i = xpair::Black; i < xpair::ColorCount; ++i)
			{
				if(from == sub_len && from % segs[i].seg_len == 0)
				{
					++buffer[i][sub_len];
					continue;
				}

				for(int j = xpair::Black; j < xpair::ColorCount; ++j)
				{
					if(i != j && from % segs[i].seg_len == 0)
						buffer[i][sub_len] += buffer[j][sub_len - from];
				}
			}
		}
	}

	__int64 result = 0;
	for(int i = 0; i < xpair::ColorCount; ++i)
		result += buffer[i][row_length];

	return result;
}

static void alloc(__int64* buffer[xpair::ColorCount], int size)
{
	for(int i = 0; i < xpair::ColorCount; ++i)
		buffer[i] = new __int64[size + 1](), buffer[i][0] = 1;
}

static void dealloc(__int64* buffer[xpair::ColorCount])
{
	for(int i = 0; i < xpair::ColorCount; ++i)
		delete []buffer[i];
}

__int64 solve_117()
{
	const int Len = 50;
	xpair segs[xpair::ColorCount];
	init_segs(segs);

	__int64 *buffer[xpair::ColorCount];
	alloc(buffer, Len);

	__int64 result = solve(buffer, Len, segs);

	dealloc(buffer);

	return result;
}