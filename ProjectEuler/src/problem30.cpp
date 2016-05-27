//The maximum value for one digit is 9^5 = 59049. We can find out the maximum possible 
//sum for a given number of digits by multiplying 59049 with the number of digits.
//Let's say we're gonna check the number 123456789.
//That's 9 digits, so the maximum sum would be 9*59049 = 531441, which doesn't even come
//close to 123456789. So we know we can forget about any number 9-digit number because 
//we'll never be able to reach a big enough sum. And it'll only get worse with larger numbers :)
//
//9的5次方为59049，假设一个x位的数，它是perfect number，那么它最大为59049x。
//当x为5时，它为6位数。
//当x为6时，它为354294，也是6位数。
//当x为7时，它为413343，依然是6位数，其余的也不会满足x的值与实际结果的位数相等的情况了。
//所以当x为6时，perfect number依然是有可能存在的。且最大值就是354294。
//因此，其上界是 9 * 9 * 9 * 9 * 9 * 6。
static bool
IsPerfectNumber(int number)
{
	int sumOfDigits = 0;
	int num = number;
	for(; num != 0; )
	{
		int digit = num % 10;
		sumOfDigits += (digit * digit * digit * digit * digit);
		num /= 10;
	}
	return (number == sumOfDigits);
}

int
GetTheSumOfAllTheNumbersThatCanBeWrittenAsTheSumOfFifthPowersOfTheirDigits()
{
	const int limit = 9 * 9 * 9 * 9 * 9 * 6;
	int result = 0;
	for(int i = 10; i < limit; ++i)
	{
		if(IsPerfectNumber(i))
			result += i;
	}
	return result;
}
