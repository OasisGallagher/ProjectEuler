//The maximum value for one digit is 9^5 = 59049. We can find out the maximum possible 
//sum for a given number of digits by multiplying 59049 with the number of digits.
//Let's say we're gonna check the number 123456789.
//That's 9 digits, so the maximum sum would be 9*59049 = 531441, which doesn't even come
//close to 123456789. So we know we can forget about any number 9-digit number because 
//we'll never be able to reach a big enough sum. And it'll only get worse with larger numbers :)
//
//9��5�η�Ϊ59049������һ��xλ����������perfect number����ô�����Ϊ59049x��
//��xΪ5ʱ����Ϊ6λ����
//��xΪ6ʱ����Ϊ354294��Ҳ��6λ����
//��xΪ7ʱ����Ϊ413343����Ȼ��6λ���������Ҳ��������x��ֵ��ʵ�ʽ����λ����ȵ�����ˡ�
//���Ե�xΪ6ʱ��perfect number��Ȼ���п��ܴ��ڵġ������ֵ����354294��
//��ˣ����Ͻ��� 9 * 9 * 9 * 9 * 9 * 6��
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
