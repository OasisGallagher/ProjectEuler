/*
 * ����������⣬�ҳ�����3�ַ�����
 * 1) �����������ڵķ����Ĳ���1/x�������Ҳ��ϸ�����һ��������Ȼ��������������̫����
 * 2) �뵽��phiֵ�����ֱ����ÿ������phiֵ��Ȼ����ӣ�����̫����
 * 3) �뵽2��4��8��16��Щ2��������ͬ��phiֵ�������һ��ɸ�ӣ�������2��phiֵ�󣬽�4��8��16��
 *    ��Ϊ�����ټ��㣬��������
 * ���ȥ
 * http://www.mathblog.dk/project-euler-72-reduced-proper-fractions/
 * �Ͽ����˵�������������Ϊ��clever method��
 * ��2��ʼ��2��4��6��8��������Ϊ2����Щֵ����һ��2���������ӣ����ǵ�phiֵ����2*(2-1)������֣�
 * ���ԣ�Ϊ��Щֵ�ȼ���һ�Σ�������2��4��6��8����Ϊx���ȼ���x = x / 2 * (i-1)
 * �������´���3������ӵ�ʱ�򣬼��������������ֵ��
 * �����������൱��ÿ�ζ�����phiֵ��һ���֣�����x��phiֵ������x��n1��n2��n3��Щ�����ӣ�����
 * phiֵ����x * ((n1 - 1) / n1) * ((n2 - 1) / n2) * ((n3 - 1) / n3).���ｫ����Ĺ��̷ֽ�Ϊ��
 * �ȼ����һ������x * ((n1 - 1)�ġ�Ȼ�󲻼��ڼ�����һ�����ӣ����ǵȴ������һ������ʱ���Զ�
 * ����д����������һ���ֵļ���ǳ������
 */
static const size_t LMT = 1000000;
unsigned long long solve_72()
	{
	unsigned *phi = new unsigned[LMT + 1];
	unsigned long long total = 0;
	for(size_t i = 0; i <= LMT; ++i)
		phi[i] = i;

	for(size_t i = 2; i <= LMT; ++i)
		{
		if(phi[i] == i)	// untouched, must be indexed by a prime.
			{	// phi[i] must be a prime.
			// use factor i.
			// erase all the numbers' prime fractor equals to i.
			for(size_t j = i; j <= LMT; j += i)	
				phi[j] = phi[j]  / i * (i - 1);
			}
		// all prime factors of i have been used.
		//
		total += phi[i];
		}
	delete []phi;
	return total;
	}
