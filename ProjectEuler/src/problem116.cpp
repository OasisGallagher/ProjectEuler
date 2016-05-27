__int64 exactly_color_count(int len, int exactly_count)
{
	__int64* black_start = new __int64[len + 1](), *red_start = new __int64[len + 1]();
	black_start[0] = red_start[0] = 1;

	for(int sub_len = 1; sub_len <= len; ++sub_len)
	{
		// from == lenʱ,�������ζ��Ǵ�ɫ.
		for(int from = 1; from <= sub_len; ++from)
		{
			black_start[sub_len] += red_start[sub_len - from];
			// ����exactly_count,����Ҫ�����ı���.
			if(from % exactly_count == 0)
				red_start[sub_len] += black_start[sub_len - from];
		}
	}

	__int64 result = black_start[len] + red_start[len];
	delete[] black_start;
	delete[] red_start;
	// ��ȥһ��ȫΪ��ɫ���.
	return result - 1;
}

__int64 solve_116()
{
	const int arr[] = { 2, 3, 4 };
	const int Length = 50;

	__int64 result = 0;

	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
		result += exactly_color_count(Length, arr[i]);

	return result;
}