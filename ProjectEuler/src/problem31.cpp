//Quote: http://www.mathblog.dk/project-euler-31-combinations-english-currency-denominations/#comment-3855
//See ./coins.docx if the link above is broken.

//������1,2����1,2,3.
//��ʼ�����,���0�ķ�����һ��.
//���ֻ��1,��ô��1,2,3��ֻ��һ�ַ���,��ȫ1.
//�����2����,��ô,��2��ʼ,��Ϊ�Ѿ�ȷ������ϵ�һ������2,��ôֻ��Ҫ��֪����һ����
//�ж�������Ϸ�ʽ,�ټ���֮ǰ����Ϸ�ʽ�ĸ���,���ǽ��.
//Ҳ����˵,��2��˵,��ȷ��2-2=0����Ϸ�ʽ,��1��.�������2һ����2�ַ���.
//��3����,��ϵ�һ������2,��һ������3-2=1,��1��˵,��һ����Ϸ�ʽ,����һ�������ַ�ʽ.

static int faceValue[] = {1, 2, 5, 10, 20, 50, 100, 200};
static const size_t factValueCount = 8;

int
GetTheCountOfDifferentWaysCan200pBeMadeUsingAnyNumberOfEnglandCoins(int, int)
{
	// Dynamic Programming.
	const int destination = 200;
	int waysCount[destination + 1] = { 0 };
	waysCount[0] = 1;

	for(int indexCoin2Give = 0; indexCoin2Give < factValueCount; ++indexCoin2Give)
		for(int indexValueNeed2Pay = faceValue[indexCoin2Give]; 
			indexValueNeed2Pay <= destination; ++indexValueNeed2Pay)
			waysCount[indexValueNeed2Pay] 
					+= waysCount[indexValueNeed2Pay - faceValue[indexCoin2Give]];

	return waysCount[200];
}

//Here's a very nice recursion

int GetTheCountOfDifferentWaysCan200pBeMadeUsingAnyNumberOfEnglandCoins2(int money, int maxCoin)
{
	// maxCoin���Ժ��Ӳ�Ҷ���ѡ.
	int coins[8] = {200, 100, 50, 20, 10, 5, 2, 1};
    int result = 0;
    if(maxCoin == 7) return 1;	//��ʾֻ����ֵ1��ѡ�����Է���1��
    for(int i = maxCoin; i < 8; i++)
    {
        if (money - coins[i] == 0)
			result += 1;

        if (money - coins[i] > 0) 
			result += GetTheCountOfDifferentWaysCan200pBeMadeUsingAnyNumberOfEnglandCoins(
							money - coins[i], i);
    }
    return result;
}

int
GetTheCountOfDifferentWaysCan200pBeMadeUsingAnyNumberOfEnglandCoins3(int, int)
{
	//��Ϊ��Ϸ�ʽֻ�����������������ԣ���ÿ�����ĸ������������
	int ways = 0;
	const int dest = 2;
	for(int a = dest; a >= 0; a -= 200)							//a��200��
		for(int b = a; b >= 0; b -= 100)						//b��100��
			for(int c = b; c >= 0; c -= 50)						//c��50��
				for(int d = c; d >= 0; d -= 20)					//d��20��
					for(int e = d; e >= 0; e -= 10)				//e��10��
						for(int f = e; f >= 0; f -= 5)			//f��5��
							for(int g = f; g >= 0; g -= 2)		//g��i��
								++ways;
//��Ҫע����ǣ�����ֻ������2����Ϊ������ʣ���ֵ��Ҫ��С��2��������գ�ֻ������1����
//����ֻ��һ�֡���ȫΪ1��
//���仰˵����󣬲�����ѡ��ѡȡ����1��һ����ѡ��ǡ���ĸ�����1��ʹ�����ﵽ200��
	return ways;
}
