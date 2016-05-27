#include <iostream>
#include <ctime>

typedef unsigned __int64 Number;
// pascal���ǵ���, ��0��ʼ��.
// ����n!�к��ж��ٸ�7,  ����, ����35, ����֪��35!��, ����5��7����.
// Ȼ������49, ����7 + 1 = 8��7����, ��Ϊ49�к���2��.
// ���, ������������:
/*
unsigned Count7InNumberFact(unsigned n) {
	unsigned result = 0;
	for(; n != 0; n /= 7)
		result += (n / 7);
	return result;
}
*/
// �ɴ˿�֪, ����7�ı�������, ��Ȼֻ�в��ܱ�7��������, ������1.
// �����Ʋ��, ��[0, 7)����, ��28�����ܱ�7��������.
// �ڵ�7��, ��2�����ܱ�7��������, ���, �����Ʋ��, ��14��, ������.
// ��49����Ȼ������, ���, [0, 49)��, ��28 * 28��.
// ����������ɵ�ͼ��, ����sierpinski������, �пյĲ����ǿ��Ա�7������.
// �ӵ�49�п�ʼ, ֮����ɵ�ͼ����Ȼ��[0, 49)�е�����, ֻ�������θ߶����
// �Ľ���[0, 49)��..
// �Դ�����...

int main() {
	clock_t beg = clock();
	unsigned crows = 1000000000;
	Number result = 0;
	unsigned width = 1;
	unsigned product = 1;
	Number cell = 1;

	do {
		unsigned height = 1;

		cell = 1;
		for(; height * 7 < crows; height *= 7) cell *= 28;

		if(cell == 1) {
			crows = (1 + crows) * crows / 2;
			result += crows * product;
		}
		else {
			unsigned count = crows / height;

			unsigned sum = (1 + count) * count / 2;

			crows = crows % height;

			result += product * sum * cell;

			product *= (count + 1);
		}
	}while(cell != 1);

	std::cout << result << std::endl;
	std::cout << float(clock() - beg) / CLOCKS_PER_SEC << " second(s)." << std::endl;
	return 0;
}
