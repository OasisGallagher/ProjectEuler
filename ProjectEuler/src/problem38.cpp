#include <math.h>
//��Ϊ��Ҫ���ֵ���������ȼ������ֵ��9��ʼ�ġ�
//�����ʼ��������ͬ�������е�192��n����3λ������ô2��n��4λ����3��n��4λ������������9λ��������
//���n��2λ������ô2��n��3λ����3��n��3λ������ʱ�Ѿ�ռ����8λ��������Ҳ�����ܡ�
//���n��1λ����Ҳ����9����ô���Ϊ918273645��
//����4λ�����ԣ�Ϊ9xyz�����x����4����ô2��n�ͻ���19ijk�����뿪ʼ����λ���е�9��ͻ�����ԣ�
//���4λ�����Ͻ�Ӧ�ü��ٵ�9487��
//���������½磬��ΪҪ9��ͷ������9123�����ǣ�����2��n��һ����1hijk�����������Ϊʲôȷ����19xxx����
//���ԣ���ʼ�������в�������1�������½��ȷ��9234��
extern bool IsPandigital(unsigned number);

static inline
unsigned ConcatentNumbers(unsigned number1, unsigned number2)
	{
	return number1 * ((int)pow(10.0, 1 + (int)log10((double)number2))) + number2;
	}

unsigned GetTheLargest1To9Pandigital9DigitNumberThatCanBeFormedAsTheConcatenatedProductOfAnIntegerWith1ToNWhereNIsGreaterThan1()
	{
	for(unsigned i = 9487; i >= 9234; --i)
		{
		unsigned temp = ConcatentNumbers(i, 2 * i);
		if(IsPandigital(temp))
			return temp > 918273645 ? temp : 918273645;
		}
	return -1;
	}
