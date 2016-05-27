-- 由于n趋向于正无穷, 可以使用斐波那契数列的通项公式来求和.
-- 求和之后化简, 得到y只要满足
-- 5yy + 2y + 1为完全平方数即可.
-- 即4yy + yy + 2y + 1 = (2y)^2 + (y + 1)^2为完全平方数.
-- 利用欧几里得计算勾股数的方法, 设2y为2mn, y + 1为mm - nn,
-- 只要m和n都是整数, 就可以使(mm - nn)^2 + (mn)^2为完全平方数, 即(m + n)^2.
-- 由于y = mn, y + 1 = mm - nn, 所以:
-- mn + 1 = mm - nn, m和n都为整数, 求出的mn就是y值.
-- 显然这是一个二次丢番图方程.
-- 求解得到:
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
