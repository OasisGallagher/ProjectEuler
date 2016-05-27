-- link:
-- http://math.stackexchange.com/questions/73330/how-many-non-decreasing-sequences-of-7-decimal-digits-are-there
function fact(i)
	return (i <= 1) and 1 or i * fact(i - 1);
end

function sel(from, to)
	return fact(from) / fact(to) / fact(from - to);
end
-- ����non-decreasing number����Ŀ,sel(9 + digcount, digcount).
-- �����μ���ΪNλ��ʱ,non-increasing number����Ŀ.
-- ע�������Ҫ��λ���������,��Ϊ����043��˵,Ҳ��non-increasing number.
function solve_113(digcount)
	-- �����ж������˶����0,���Ҫ��ȥ����non-decresingʱ��1��,�Լ�����
	-- non-increasingʱ��digcount��.�ټ�ȥ����11,22...111...2222���ظ���.
	-- 1:0, 9 * digit_count:1~9,11~99..., digit_count-1:all other zeros when
	-- calculating non-incresing numbers.
	local minus = 1 + digcount + 9 * digcount;
	local result = 0;
	result = result + 2 * sel(9 + digcount, digcount);
	digcount = digcount - 1;
	while digcount > 0 do
		result = result + sel(9 + digcount, digcount);
		digcount = digcount - 1;
	end
	return result - minus;
end

print(solve_113(100));
