//首先通过计算一个无限循环小数来找出之中的规律，例如当n=7时：
//对于1 / 7：
//1借位为10，计算10 % 7 = 3。
//3再借位为30，30 % 7 = 2。
//2再借位为20， 20 % 7 = 6。
//6再借位为60， 60 % 7 = 4。
//4再借位为40， 40 % 7 = 5。
//5再借位为50， 50 % 7 = 1。
//1再借位，这时已经发生了循环。
//可以总结出这样的一条定律，对于一个正整数n，1/n产生的循环小数的循环节的长度必然小于n-1。
//通过上面的计算过程很容易得出证明，每次取余之后得到的是数字除以n之后的余数，如果这个余数曾经出现过，
//那么就会产生循环节。
//对于一个数字n，余数肯定属于[0,n)，那么余数只有n种选择。另外当余数为0时，表示已经整除，就不会存在
//循环节了，因此，长度必然小于n-1。
//再回到上面的问题，实际就是求出当余数remain第一次出现的时候，为第i次迭代，当remain第二次出现的时候，
//为第j次迭代，那么循环节的长度就是j-i。
//有了上面的过程，我们就要先找到一个remain，这个remain可以是任意的，只要产生这个remain时，商是循环节中
//的一个数字即可。
//因此，结合定律1，可以想到一个办法，就是从1开始，每次借位对n取余，进行n次，那么最后的得到remain时的商
//肯定在循环节中，可能是第一个，也可能是第m个。（结果要是无限循环小数才成立）。
//然后保存下这个remain，再从remain开始借位迭代并计数，当下次得到这个remain值的时候，计数器的值，
//就是循环节的长度。
//

int GetTheValueOfDLessThan1000ForWhich1DivideDContainsTheLongestRecurringCycleInItsDecimalFactionPart()
	{
	int n, i, len, maxlen, maxn;
	maxlen = 0;
	for(n = 2; n <= 1000; ++n)
		{
		int rest = 1;
		int remain;

		for(i = 0; i < n; i++)
			rest = (rest * 10) % n;

		remain = rest;
		len = 0;
		do
			{
			rest = (rest * 10) % n;
			len++;
			} while(rest != remain);

			if(len > maxlen)
				{
				maxn = n;
				maxlen = len;
				}
		}
	return maxn;
	}
