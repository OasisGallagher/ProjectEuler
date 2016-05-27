const char *number1[] = {"one", "two", "three", "four", "five", "six", "seven", 
"eight", "nine"};
const char* number2[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", 
"fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char* number3[] = {"twenty", "thirty", "forty", "fifty", "sixty", 
"seventy", "eighty", "ninety"};
const char* number4[] = {"hundred", "thousand"};

#include <string.h>

size_t mystrlen(const char* str)
	{
	size_t len = 0;
	while(*str != '\0')
		++len;
	return len;
	}

int GetTheNumberOfLettersUsedToWriteAllTheNumberFrom1To1000OutInWords()
	{
	int len1[10], len2[10], len3[10], len4[3];
	for(int i = 1; i < 10; ++i)
		len1[i] = strlen(number1[i - 1]);
	len1[0] = 0;

	for(int i = 0; i < 10; ++i)
		len2[i] = strlen(number2[i]);

	for(int i = 2; i < 10; ++i)
		len3[i] = strlen(number3[i - 2]);
	len3[0] = 0, len3[1] = 0;

	for(int i = 1; i < 3; ++i)
		len4[i] = strlen(number4[i - 1]);
	len4[0] = 0;

	int lenand = strlen("and");

	int result = 0;
	for(int i = 1; i < 1000; ++i)
		{
		int div = i / 100;
		result += len1[div];

		result += len4[div != 0];

		div = i % 100;

		result += (div != 0 && i / 100 > 0) ? lenand : 0;

		if(div / 10 == 1)
			{
			result += len2[div - 10];
			continue;
			}
		result += len3[div / 10];
		result += len1[div % 10];
		}
	result += strlen("onethousand");
	return result;
	}
