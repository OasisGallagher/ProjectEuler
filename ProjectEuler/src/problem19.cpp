#define LeapYear(y) ((y) % 4 == 0 && (y) % 400 != 0)
#define Monday		0
#define Tuesday		1 
#define Wednesday	2
#define Thursday	3
#define Friday		4
#define Saturday	5 
#define Sunday		6
int monthdays[][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
int GetSundaysFellOnTheFirstOfTheMonthDuringTheTwentiethCentury(/*(1 Jan 1901 to 31 Dec 2000)*/)
{
	int days = LeapYear(1990) ? 366 : 365;
	int date = (days % 7 + Monday) % 7;
	int result = 0;
	for(int i = 1901; i <= 2000; ++i)
	{
		for(int j = 0; j < 12; ++j)
		{
			if(date == Sunday)
				++result;

			date = (monthdays[LeapYear(i)][j] - (7 - date)) % 7 + Monday;
		}
	}
	return result;
}
