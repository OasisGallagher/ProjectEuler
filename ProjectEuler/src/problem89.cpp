// �������,�����뵽������Ǯ����,BFS�Ľⷨ.
// ��ʵ������ⲻ�������Ǯ�����е�:
// 1, 5, 12, ���������̰�ĵĻ�,�����12, 1, 1, 1�Ĵ�����(��Ȼ5,5,5������).
// ����,ֻ����subtractive combination���������ֵ�ʹ�þͿ�����.����ÿһ�ε���
// ��������������ַ�.
// ͨ��������ʽ:
#include <regex>
#include <string>
#include <fstream>
#include <iterator>

int solve_89()
	{
	std::string content((std::istreambuf_iterator<char>(std::ifstream("roman.txt"))), std::istreambuf_iterator<char>());
	return content.length() - regex_replace(content, std::tr1::regex("IIII|XXXX|CCCC|VIIII|LXXXX|DCCCC"), std::string("[]")).length();
	}