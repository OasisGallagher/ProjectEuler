// Quote: http://www.mathblog.dk/project-euler-15/
long long int GetRoutesThroughA2020Grid()
{
	long long int arr[21][21] = {0};
	
	for(int i = 0; i < 21; ++i)
		arr[i][20] = 1, arr[20][i] = 1;

	for(int i = 19; i >= 0; --i)
		for(int j = 19; j >= 0; --j)
		{
			arr[i][j] = arr[i + 1][j] + arr[i][j + 1];
		}

	return arr[0][0];
}

/**
static const int gridSize = 20;

// call with progress(0, 0)
static int progress(int x, int y)
{
    int i = 0;

    if (x < gridSize)
        i += progress(x + 1, y);
    if (y < gridSize)
        i += progress(x, y + 1);

    if (x == gridSize && y == gridSize)
        return 1;

    return i;
}
*/

//���������ƶ�ΪR������ΪD����ô������4��������˵��
//RRDD, RDRD, RDDR, DDRR, DRDR, DRRD.
//Ҳ����˵����4ѡ2�����⣬ѡ���������������������λ����Ȼ�Ͷ��ˡ�
//���ԣ�20�����Ӿ���20ѡ10�����⡣

//Quote: http://projecteuler.net/thread=15
//This is what I find 2 months ago when I solved it:
//
//Each movement in the horizontal is a zero.
//Each movement in the vertical is a one.
//
//1st binary# in this series:
//0000000000000000000011111111111111111111
//last:
//1111111111111111111100000000000000000000
//For the numbers in between, the amount of
// zeros should be the same as ones. In other
// words, the ones and zeros have to be rearranged.
//
//The total is: 40!/(20!)(20!)
//Just use the MS calculator.
//137846528820
