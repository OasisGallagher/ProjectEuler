#pragma once
#include <algorithm>

// the same as std::next_permutation.
template <class BinIt>
bool NextPermutation(BinIt first, BinIt last)
{
	BinIt smaller = last;

	// 确保序列至少存在2个值.
	if(first == last || first == --smaller)
		return false;

	for(; ; )
	{
		// 初始化指向最后一个值,small指向倒数第二个值.
		BinIt greater = smaller--;

		// 找到最右边的该指针值小于其后继的指针.
		if(*smaller < *greater)
		{
			// 继续找到值大于smaller的最右边的指针.
			// 结合smaller,找到最右边的一个升序对.
			// lastgr的值在smaller和greater之间(含).
			BinIt lastgr = last;
			for(; (*--lastgr <= *smaller); )
				;
			// 调整它们为降序
			std::iter_swap(smaller, lastgr);
			// greater之后的必然是递减的(否则就可以在这个区间找到升序对了).
			// 反转该区间,从而生成下一个字典序.
			std::reverse(greater, last);
			return true;
		}

		if(smaller == first)
		{	// 严格递减.
			std::reverse(first, last);
			return false;
		}
	}
	// 去除编译警告.
	return false;
}
