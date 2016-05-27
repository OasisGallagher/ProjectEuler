long long int GetLargestPrimeFactorOf600851475143()
{
	long long int x = 600851475143;
	for(long long int i = 2; i < x; ++i)
	{
		if(x % i == 0)
		{
			x /= i;
			--i;
		}
	}
	return x;
}
