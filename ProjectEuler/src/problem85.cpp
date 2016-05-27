#include <iostream>
#include <ctime>
static const int RECT_LIMIT = 2000000;

// Brute force.
/*
int RectCount(int cx, int cy)
	{
	int count = 0;
	for(int startX = 0; startX < cx; ++startX)
		for(int startY = 0; startY < cy; ++startY)
			count += (cx - startX) * (cy - startY);
	return count;
	}
*/
// _____________________________________________________________________________
//Combinatorics
//When we want to figure out how many rectangles we can make in a grid which is X*Y
//we want to figure out how many ways we can place two lines horizontally and two 
//lines vertically. There are X+1 choices on the width and Y+1 in the height since
//there are X+1 lines to make the X boxes.
static inline int RectCount(int cx, int cy)
	{
	return cx * (1 + cx) * cy * (cy + 1) / 4;
	}

static int UpperBound()
	{
	int test = 0;
	for(int i = 1; ; ++i)
		if((test += i) > RECT_LIMIT)
			return i;
	return -1;
	}

int solve_85()
	{
	const int UPPER_BOUND = UpperBound();
	int area(0), maxCount(0);

	for(int i(1); i < UPPER_BOUND; ++i)
		for(int j(i); j < UPPER_BOUND; ++j)
			{
			const int RECT_COUNT = RectCount(i, j);

			if(RECT_COUNT > RECT_LIMIT)
				break;

			if(RECT_COUNT < RECT_LIMIT && RECT_COUNT > maxCount)
				{
				maxCount = RECT_COUNT;
				area = i * j;
				}
			}

	return area;
	}
