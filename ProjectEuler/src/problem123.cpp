#define BUF_SIZE	(1000000)
#define EXCEED		(10000000000i64)
extern int GetPrimeList(int len, int *buffer);

int solve_123()
{
	int* buffer = new int[BUF_SIZE];
	int len = GetPrimeList(BUF_SIZE, buffer);

	int pos = 1;
	// buffer�е������±��Ǵ�0��ʼ��,�����еĵ�N������,ʵ������buffer��ĵ�N-1��ֵ.--!
	for(; pos < len && 2i64 * pos * buffer[pos - 1] <= EXCEED; pos += 2)
		;

	delete[] buffer;
	return pos < len ? pos : -1;
}