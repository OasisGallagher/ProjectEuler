// Thanks to http://www.mathblog.dk/project-euler-15/
// which also help me on problem 15.

extern int Max(int, int);

int arr[][15] = {
	/*layer1[] = */{75},
	/*layer2[] = */{95, 64},
	/*layer3[] = */{17, 47, 82},
	/*layer4[] = */{18, 35, 87, 10},
	/*layer5[] = */{20, 4, 82, 47, 65},
	/*layer6[] = */{19, 1, 23, 75, 3, 34},
	/*layer7[] = */{88, 2, 77, 73, 7, 63, 67},
	/*layer8[] = */{99, 65, 4, 28, 6, 16, 70, 92},
	/*layer9[] = */{41, 41, 26, 56, 83, 40, 80, 70, 33},
	/*layer10[] = */{41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
	/*layer11[] = */{53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
	/*layer12[] = */{70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
	/*layer13[] = */{91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
	/*layer14[] = */{63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
	/*layer15[] = */{4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23}
	};

int GetTheMaximumTotalFromTopToBottomOfTheTriangle()
	{
	const int limit = 15 - 1;
	for(int i = limit; i != 0; --i)
		{
		for(int j = 0; j < i; ++j)
			arr[i - 1][j] += Max(arr[i][j], arr[i][j + 1]);
		}
	return arr[0][0];
	}
