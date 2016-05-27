#include <fstream>
#include <iostream>

#define INVALID_RESULT	0
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#define BothAreTrue(xbool1, xbool2)		(xbool1 && xbool2)
#define OneOfThemIsTrue(xbool1, xbool2)	(xbool1 || xbool2) && (!BothAreTrue(xbool1, xbool2))

static inline
char Replace(char ch)
	{
	return ch == 'T' ? ':' 
		: ch == 'J' ? ';' 
		: ch == 'Q' ? '<' 
		: ch == 'K' ? '=' 
		: ch == 'A' ? '>' 
		: ch;
	}

enum Score{ OnePair, TwoPairs, ThreeOfAKind, Straight, Flush, FullHouse,
	FourOfAKind, StraightFlush, RoyalFlush};

struct cards
	{
	char card;
	char suit;
	cards& operator = (const cards& other) { card = other.card; suit = other.suit; return *this;}
	bool operator < (const cards& other)const { return card < other.card; }
	};

typedef cards (&OneHand)[5];

static
bool cmpHighCard(OneHand hand1, OneHand hand2)
	{
	for(int i = 4; i >= 0; --i)
		if(hand1[i].card > hand2[i].card)
			return true;
		else if(hand1[i].card < hand2[i].card)
			return false;
	__asm int 3;
	}

static
char getOnePair(OneHand hand)
	{
	for(int i = 0, j; (j = i) < 5 && ++i < 5; )
		if(hand[i].card == hand[j].card)
			return hand[i].card;
	return INVALID_RESULT;
	}

static
char* getTwoPairs(OneHand hand)
	{
	static char pairs[2];
	memset(pairs, 0, 2);
	int pos = 0;

	for(int i = 0, j; (j = i) < 5 && (++i) < 5; )
		if(hand[i].card == hand[j].card)
			{
			if(pos < 2)
				pairs[pos++] = hand[i++].card;
			else
				return INVALID_RESULT;
			}
	return pos == 2 ? pairs : INVALID_RESULT;
	}

static
char getThreeOfAKind(OneHand hand)
	{
	char ch = hand[0].card;
	int count = 1;
	for(int i = 1; i < 5; ++i)
		{
		if(hand[i].card == ch)
			{
			++count;
			if(count == 3)
				return ch;
			}
		else
			ch = hand[i].card, count = 1;
		}
	return INVALID_RESULT;
	}

static
char getStraight(OneHand hand)
	{
	char first = hand[0].card;
	for(int i = 1; i < 5; ++i)
		if(hand[i].card != hand[i - 1].card + 1)
			return INVALID_RESULT;
	return hand[4].card;
	}

static
bool isFlush(OneHand hand)
	{
	char suit = hand[0].suit;
	for(int i = 1; i < 5; ++i)
		if(hand[i].suit != suit)
			return false;
	return true;
	}

static
char* getFullHouse(OneHand hand)
	{
	static char twoChars[2];
	memset(twoChars, 0, 2);

	if(hand[1].card != hand[0].card)
		return INVALID_RESULT;
	if(hand[2].card == hand[1].card && hand[3].card == hand[4].card)
		{
		twoChars[0] = hand[0].card;
		twoChars[1] = hand[4].card;
		return twoChars;
		}
	if(hand[2].card == hand[3].card && hand[3].card == hand[4].card)
		{	// 2, 3.
		twoChars[0] = hand[4].card;
		twoChars[1] = hand[1].card;
		return twoChars;
		}
	return INVALID_RESULT;
	}

static
char getFourOfAKind(OneHand hand)
	{
	if(hand[0].card != hand[1].card)
		{
		if(hand[1].card == hand[2].card && hand[2].card == hand[3].card
			&& hand[3].card == hand[4].card)
			return hand[1].card;
		}
	else if(hand[2].card == hand[1].card && hand[2].card == hand[3].card)
		return hand[1].card;
	return INVALID_RESULT;
	}

static
char getStraightFlush(OneHand hand)
	{
	if(!isFlush(hand))
		return INVALID_RESULT;
	return getStraight(hand);
	}

static
bool isRoyalFlush(OneHand hand)
	{
	if(!isFlush(hand))
		return false;
	return getStraight(hand) != INVALID_RESULT && hand[0].card == ':';
	}

static
void insertSortCards(cards* first, int count)
	{
	for(int i = 1; i < count; ++i)
		{
		cards key = first[i];
		int j = i - 1;
		for( ; j >= 0 && first[j].card > key.card; --j)
			first[j + 1] = first[j];

		first[j + 1] = key;
		}
	}

static
bool doesPlayer1Win(const char* _1, const char* _2)
	{
	cards crd1[5];
	int index = 0;
	for(int i = 0; i < 14; i += 3, ++index)
		crd1[index].card = Replace(_1[i]), crd1[index].suit = Replace(_1[i + 1]);
	
	insertSortCards(crd1, 5);
	
	cards crd2[5];
	index = 0;
	for(int i = 0; i < 14; i += 3, ++index)
		crd2[index].card = Replace(_2[i]), crd2[index].suit = Replace(_2[i + 1]);
	insertSortCards(crd2, 5);

	char xResult1, xResult2;
	xResult1 = isRoyalFlush(crd1);
	xResult2 = isRoyalFlush(crd2);
	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;
	
	xResult1 = getStraightFlush(crd1);
	xResult2 = getStraightFlush(crd2);

	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;
	else if(BothAreTrue(xResult1, xResult2))
		return cmpHighCard(crd1, crd2);

	xResult1 = getFourOfAKind(crd1);
	xResult2 = getFourOfAKind(crd2);

	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;
	else if(BothAreTrue(xResult1, xResult2))
		return xResult1 != xResult2 ? xResult1 > xResult2 : cmpHighCard(crd1, crd2);
	
	char *ptrResult1, *ptrResult2;
	char tmpBuffer1[2], tmpBuffer2[2];

	ptrResult1 = getFullHouse(crd1);
	ptrResult1 != NULL ? strncpy(tmpBuffer1, ptrResult1, 2) : __noop;

	ptrResult2 = getFullHouse(crd2);
	ptrResult2 != NULL ? strncpy(tmpBuffer2, ptrResult2, 2) : __noop;

	if(OneOfThemIsTrue(ptrResult1, ptrResult2))
		return ptrResult1 != INVALID_RESULT;
	else if(BothAreTrue(xResult1, xResult2))
		return tmpBuffer1[0] != tmpBuffer2[0] ?
			tmpBuffer1[0] > tmpBuffer2[0] : tmpBuffer1[1] > tmpBuffer2[1];

	xResult1 = isFlush(crd1);
	xResult2 = isFlush(crd2);
	
	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;

	xResult1 = getStraight(crd1);
	xResult2 = getStraight(crd2);

	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;
	else if(BothAreTrue(xResult1, xResult2))
		return xResult1 > xResult2;

	xResult1 = getThreeOfAKind(crd1);
	xResult2 = getThreeOfAKind(crd2);

	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;
	else if(BothAreTrue(xResult1, xResult2))
		return xResult1 != xResult2 ? xResult1 > xResult2 : cmpHighCard(crd1, crd2);
	
	ptrResult1 = getTwoPairs(crd1);
	ptrResult1 ? strncpy(tmpBuffer1, ptrResult1, 2) : __noop;
	ptrResult2 = getTwoPairs(crd2);
	ptrResult2 ? strncpy(tmpBuffer2, ptrResult2, 2) : __noop;
	
	if(OneOfThemIsTrue(ptrResult1, ptrResult2))
		return ptrResult1 != INVALID_RESULT;
	else if(BothAreTrue(ptrResult1, ptrResult2))
		{
		if(max(tmpBuffer1[0], tmpBuffer1[1]) != max(tmpBuffer2[0], tmpBuffer2[1]))
			return max(tmpBuffer1[0], tmpBuffer1[1]) > max(tmpBuffer2[0], tmpBuffer2[1]);
		if(min(tmpBuffer1[0], tmpBuffer1[1]) != min(tmpBuffer2[0], tmpBuffer2[1]))
			return min(tmpBuffer1[0], tmpBuffer1[1]) > min(tmpBuffer2[0], tmpBuffer2[1]);
		return cmpHighCard(crd1, crd2);
		}

	xResult1 = getOnePair(crd1);
	xResult2 = getOnePair(crd2);
	if(OneOfThemIsTrue(xResult1, xResult2))
		return xResult1 != INVALID_RESULT;
	else if(BothAreTrue(xResult1, xResult2))
		return xResult1 != xResult2 ? xResult1 > xResult2 : cmpHighCard(crd1, crd2);

	return cmpHighCard(crd1, crd2);
	}

int GetTheTimesDoesPlayer1Win()
	{
	int result = 0;
	char buffer[32] = { 0 };
	std::ifstream ifs("poker.txt");

	for(; ifs.getline(buffer, sizeof(buffer) * sizeof(char)); )
		{
		if(doesPlayer1Win(buffer, buffer + 15))
			++result;
		}
	return result;
	}
