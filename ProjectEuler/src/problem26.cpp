//����ͨ������һ������ѭ��С�����ҳ�֮�еĹ��ɣ����統n=7ʱ��
//����1 / 7��
//1��λΪ10������10 % 7 = 3��
//3�ٽ�λΪ30��30 % 7 = 2��
//2�ٽ�λΪ20�� 20 % 7 = 6��
//6�ٽ�λΪ60�� 60 % 7 = 4��
//4�ٽ�λΪ40�� 40 % 7 = 5��
//5�ٽ�λΪ50�� 50 % 7 = 1��
//1�ٽ�λ����ʱ�Ѿ�������ѭ����
//�����ܽ��������һ�����ɣ�����һ��������n��1/n������ѭ��С����ѭ���ڵĳ��ȱ�ȻС��n-1��
//ͨ������ļ�����̺����׵ó�֤����ÿ��ȡ��֮��õ��������ֳ���n֮��������������������������ֹ���
//��ô�ͻ����ѭ���ڡ�
//����һ������n�������϶�����[0,n)����ô����ֻ��n��ѡ�����⵱����Ϊ0ʱ����ʾ�Ѿ��������Ͳ������
//ѭ�����ˣ���ˣ����ȱ�ȻС��n-1��
//�ٻص���������⣬ʵ�ʾ������������remain��һ�γ��ֵ�ʱ��Ϊ��i�ε�������remain�ڶ��γ��ֵ�ʱ��
//Ϊ��j�ε�������ôѭ���ڵĳ��Ⱦ���j-i��
//��������Ĺ��̣����Ǿ�Ҫ���ҵ�һ��remain�����remain����������ģ�ֻҪ�������remainʱ������ѭ������
//��һ�����ּ��ɡ�
//��ˣ���϶���1�������뵽һ���취�����Ǵ�1��ʼ��ÿ�ν�λ��nȡ�࣬����n�Σ���ô���ĵõ�remainʱ����
//�϶���ѭ�����У������ǵ�һ����Ҳ�����ǵ�m���������Ҫ������ѭ��С���ų�������
//Ȼ�󱣴������remain���ٴ�remain��ʼ��λ���������������´εõ����remainֵ��ʱ�򣬼�������ֵ��
//����ѭ���ڵĳ��ȡ�
//

int GetTheValueOfDLessThan1000ForWhich1DivideDContainsTheLongestRecurringCycleInItsDecimalFactionPart()
	{
	int n, i, len, maxlen, maxn;
	maxlen = 0;
	for(n = 2; n <= 1000; ++n)
		{
		int rest = 1;
		int remain;

		for(i = 0; i < n; i++)
			rest = (rest * 10) % n;

		remain = rest;
		len = 0;
		do
			{
			rest = (rest * 10) % n;
			len++;
			} while(rest != remain);

			if(len > maxlen)
				{
				maxn = n;
				maxlen = len;
				}
		}
	return maxn;
	}