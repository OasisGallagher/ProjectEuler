-- ����n������������, ����ʹ��쳲��������е�ͨ�ʽ�����.
-- ���֮�󻯼�, �õ�yֻҪ����
-- 5yy + 2y + 1Ϊ��ȫƽ��������.
-- ��4yy + yy + 2y + 1 = (2y)^2 + (y + 1)^2Ϊ��ȫƽ����.
-- ����ŷ����ü��㹴�����ķ���, ��2yΪ2mn, y + 1Ϊmm - nn,
-- ֻҪm��n��������, �Ϳ���ʹ(mm - nn)^2 + (mn)^2Ϊ��ȫƽ����, ��(m + n)^2.
-- ����y = mn, y + 1 = mm - nn, ����:
-- mn + 1 = mm - nn, m��n��Ϊ����, �����mn����yֵ.
-- ��Ȼ����һ�����ζ���ͼ����.
-- ���õ�:
-- x0 = 1, y0 = 0.
-- y(n + 1) = x(n) + y(n)
-- x(n + 1) = 2 * x(n) + y(n)

function NextTerm(xn, yn)
	return 2 * xn + yn, xn + yn
end

local x = 1
local y = 0
local count = 0
repeat
	x, y = NextTerm(x, y)
	count = count + 1
until count == 15

print(x * y)
