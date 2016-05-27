#pragma once
#include <algorithm>

// the same as std::next_permutation.
template <class BinIt>
bool NextPermutation(BinIt first, BinIt last)
{
	BinIt smaller = last;

	// ȷ���������ٴ���2��ֵ.
	if(first == last || first == --smaller)
		return false;

	for(; ; )
	{
		// ��ʼ��ָ�����һ��ֵ,smallָ�����ڶ���ֵ.
		BinIt greater = smaller--;

		// �ҵ����ұߵĸ�ָ��ֵС�����̵�ָ��.
		if(*smaller < *greater)
		{
			// �����ҵ�ֵ����smaller�����ұߵ�ָ��.
			// ���smaller,�ҵ����ұߵ�һ�������.
			// lastgr��ֵ��smaller��greater֮��(��).
			BinIt lastgr = last;
			for(; (*--lastgr <= *smaller); )
				;
			// ��������Ϊ����
			std::iter_swap(smaller, lastgr);
			// greater֮��ı�Ȼ�ǵݼ���(����Ϳ�������������ҵ��������).
			// ��ת������,�Ӷ�������һ���ֵ���.
			std::reverse(greater, last);
			return true;
		}

		if(smaller == first)
		{	// �ϸ�ݼ�.
			std::reverse(first, last);
			return false;
		}
	}
	// ȥ�����뾯��.
	return false;
}
