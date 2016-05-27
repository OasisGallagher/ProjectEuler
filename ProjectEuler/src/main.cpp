#include <iostream>
#include <ctime>
#include <exception>
#include "../include/problemall.hpp"
#include <iomanip>

int main()
{
	clock_t beg = clock();
	try{
		std::cout << solve_96() << std::endl;
	}
	catch(const std::exception& exp) {
		std::cout << "cought an exception: " << exp.what() << std::endl;
	}
	catch(...){
		std::cout << "cought an unknown exception.\n";
	}

	std::cout << ">> " << std::fixed << std::setprecision(4) << double(clock() - beg) / CLOCKS_PER_SEC << " seconds in total.\n";
}
