extern int GetPrimeList(int len, int *buffer);

//�����ж�һ����nλ��������number�ǲ�����������1��n��ɣ��ұ�֤1��n������һ�Ρ�
static
bool IsPandigitalEx(unsigned number)
	{
	int digits = 0, count = 0;
	for(; number > 0; ++count, number /= 10)
		{
		//Ԥ�ȱ���digit��ֵ��
		int tmp = digits;

		//��Ȼ��digit����(int)((number % 10) - 1)��
		//�����൱�ڶ�һ��32λ�����ӵ�0λ��ʼ���ֱ�������¼1��2��3����9��
		digits = digits | 1 << (int)((number % 10) - 1);

		//���digit���û�䣬����(int)((number % 10) - 1)���λ�Ѿ�Ϊ1�ˣ�����ֱ�ӷ���false��
		if (tmp == digits)
			return false;
		}
	//��������λû���ظ���
	//count��¼���������һ���ж���λ��
	//(1 << count) - 1ʱ��(1 << count)�õ�1+0����0��count��0����Ȼ���1���͵õ�1����1��count������
	//������Ҫ�����жϣ����number��13��������������λû���ظ������ǻᵼ��digitΪ101��
	//����ʱ�ģ�1<<count��-1 Ϊ11��Ҳ����˵�������ж�һ��nλ�������ǲ���1��n������n������
	return (digits == (1 << count) - 1);
	}

int GetTheLargestNDigitPanditalPrimeThatExists()
	{
	//9λ��Pandital������λ�ĺ�Ϊ1+2+3+4+5+6+7+8+9=45������������϶��ܱ�3���������Կ϶�����������
	//8λ��Pandital������λ�ĺ�Ϊ45-9=36������������϶��ܱ�3���������Կ϶�����������
	//7λ��Pandital������λ�ĺ�Ϊ36-8=28��7λ����ſ��ܴ���������
	const int limit = 10000000;
	int *buffer = new int[limit];
	int primeLen = GetPrimeList(10000000, buffer);
	int i = 0;
	
	for(i = (--primeLen); !IsPandigitalEx(buffer[i]); --i)
		;
	int result = buffer[i];
	delete buffer;

	return result;	
	}
