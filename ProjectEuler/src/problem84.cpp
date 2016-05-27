#include <cstdlib>
#include <iostream>
// Simulation.
// http://projecteuler.net/thread=84;page=7 by mr_kazz.
const char* solve_84()
	{
	int at(0), threeRoll(0), ccIndex(0), chIndex(0);
	int count[40] = { 0 }, goTo[6] = { 0, 10, 11, 24, 39, 5 };

	for(int i(0); i < 10000; i++)
		{
		int d1(rand() % 4 + 1), d2(rand() % 4 + 1);

		if(d1 == d2)
			threeRoll++;
		else
			threeRoll = 0;

		if(threeRoll == 3)
			{
			at = 10;
			threeRoll = 0;
			}
		else
			{
			at = (at + d1 + d2) % 40;

			if(at == 30)	// Go to Jail
				at = 10;
			else if(at == 2 || at == 17 || at == 33)	// Community Chest
				{
				if(ccIndex < 2)
					at = goTo[ccIndex];
				ccIndex = (ccIndex + 1) % 16;
				}
			else if(at == 7 || at == 22 || at == 36)	// Chance
				{
				if(chIndex < 6)
					at = goTo[chIndex];
				else if(chIndex < 8)
					{
					if(at == 7)
						at = 15;
					else if(at == 22)
						at = 25;
					else
						at = 5;
					}
				else if(chIndex  ==  8)
					{
					if(at == 22)
						at = 28;
					else
						at = 12;
					}
				else if(chIndex  ==  9)
					at -= 3;
				chIndex = (chIndex + 1) % 16;
				}
			}
		count[at]++;
		}
	static char buffer[7] = { 0 };

	for (int i(0); i < 3; i++)
		{
		int max(0), maxpos;
		for (int j = 0; j < 40; j++)
			if(count[j] > max)
				{
				max = count[j];
				maxpos = j;
				}
		itoa(maxpos, buffer + i * 2, 10);
		count[maxpos] = 0;
		}

	return buffer;
	}

