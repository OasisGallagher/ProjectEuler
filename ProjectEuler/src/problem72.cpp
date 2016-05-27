/*
 * 关于这个问题，我尝试了3种方法：
 * 1) 由于两个相邻的分数的差是1/x，所以我不断更新下一个分数，然后计数，这个方法太慢。
 * 2) 想到了phi值，因此直接求每个数的phi值，然后相加，还是太慢。
 * 3) 想到2，4，8，16这些2的幂有相同的phi值，因此用一个筛子，计算完2的phi值后，将4，8，16等
 *    置为不用再计算，还是慢。
 * 最后去
 * http://www.mathblog.dk/project-euler-72-reduced-proper-fractions/
 * 上看别人的做法，他所认为的clever method；
 * 从2开始，2，4，6，8……步长为2，这些值都有一个2这样的因子，他们的phi值都有2*(2-1)这个部分，
 * 所以，为这些值先计算一次，即对于2，4，6，8，设为x，先计算x = x / 2 * (i-1)
 * 这样在下次用3这个因子的时候，继续这样更新这个值。
 * 这样的做法相当于每次都计算phi值的一部分，即把x的phi值，比如x有n1，n2，n3这些质因子，本来
 * phi值等于x * ((n1 - 1) / n1) * ((n2 - 1) / n2) * ((n3 - 1) / n3).这里将计算的过程分解为；
 * 先计算第一个因子x * ((n1 - 1)的。然后不急于计算下一个因子，而是等待检查下一个质数时，自动
 * 的填写。而这样的一部分的计算非常的巧妙。
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
