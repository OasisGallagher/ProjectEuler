#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>

extern bool special_set(std::vector<int>& arr);

int solve_105()
{
	int result = 0;
	for(std::ifstream ifs("sets.txt"); ifs;)
	{
		char buffer[128] = { 0 };
		ifs.getline(buffer, _countof(buffer));
		if(buffer[0] == 0)
			break;

		std::stringstream ss;
		ss << buffer;
		std::vector<int> tmp;
		while(ss)
		{
			int number = 0;
			ss >> number;
			tmp.push_back(number);
			ss.ignore();
		}

		std::sort(tmp.begin(), tmp.end());
		if(special_set(tmp))
			result += std::accumulate(tmp.begin(), tmp.end(), 0);
	}

	return result;
}
