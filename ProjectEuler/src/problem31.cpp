//Quote: http://www.mathblog.dk/project-euler-31-combinations-english-currency-denominations/#comment-3855
//See ./coins.docx if the link above is broken.

//假如用1,2来凑1,2,3.
//初始情况下,设凑0的方法有一种.
//如果只用1,那么凑1,2,3都只用一种方法,即全1.
//如果用2来凑,那么,从2开始,因为已经确定了组合的一部分是2,那么只需要再知道另一部分
//有多少中组合方式,再加上之前的组合方式的个数,就是结果.
//也就是说,对2来说,再确定2-2=0的组合方式,即1种.所以组合2一共有2种方案.
//对3而言,组合的一部分是2,另一部分是3-2=1,对1来说,有一种组合方式,所以一共有三种方式.

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
	// maxCoin及以后的硬币都可选.
	int coins[8] = {200, 100, 50, 20, 10, 5, 2, 1};
    int result = 0;
    if(maxCoin == 7) return 1;	//表示只有面值1可选，所以返回1。
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
	//因为组合方式只可能是上述的面额，所以，对每个面额的个数逐个迭代。
	int ways = 0;
	const int dest = 2;
	for(int a = dest; a >= 0; a -= 200)							//a个200。
		for(int b = a; b >= 0; b -= 100)						//b个100。
			for(int c = b; c >= 0; c -= 50)						//c个50。
				for(int d = c; d >= 0; d -= 20)					//d个20。
					for(int e = d; e >= 0; e -= 10)				//e个10。
						for(int f = e; f >= 0; f -= 5)			//f个5。
							for(int g = f; g >= 0; g -= 2)		//g个i。
								++ways;
//需要注意的是，这里只迭代到2，因为，对于剩余的值，要用小于2的面额来凑（只可能是1），
//方法只有一种。即全为1。
//换句话说，最后，不能再选择选取几个1，一定是选择恰当的个数的1，使总数达到200。
	return ways;
}
