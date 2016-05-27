// 看到这个,首先想到的是找钱问题,BFS的解法.
// 其实这个问题不会存在找钱问题中的:
// 1, 5, 12, 如果单纯的贪心的话,会出现12, 1, 1, 1的错误结果(显然5,5,5更合适).
// 所以,只是用subtractive combination来减少数字的使用就可以了.而且每一次的替
// 换结果都是两个字符.
// 通过正则表达式:
#include <regex>
#include <string>
#include <fstream>
#include <iterator>

int solve_89()
	{
	std::string content((std::istreambuf_iterator<char>(std::ifstream("roman.txt"))), std::istreambuf_iterator<char>());
	return content.length() - regex_replace(content, std::tr1::regex("IIII|XXXX|CCCC|VIIII|LXXXX|DCCCC"), std::string("[]")).length();
	}