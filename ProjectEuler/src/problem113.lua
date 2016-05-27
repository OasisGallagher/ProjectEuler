-- link:
-- http://math.stackexchange.com/questions/73330/how-many-non-decreasing-sequences-of-7-decimal-digits-are-there
function fact(i)
	return (i <= 1) and 1 or i * fact(i - 1);
end

function sel(from, to)
	return fact(from) / fact(to) / fact(from - to);
end
-- 计算non-decreasing number的数目,sel(9 + digcount, digcount).
-- 再依次计算为N位数时,non-increasing number的数目.
-- 注意后者需要按位数逐个计算,因为对于043来说,也是non-increasing number.
function solve_113(digcount)
	-- 迭代中都计算了多余的0,因此要减去计算non-decresing时的1个,以及计算
	-- non-increasing时的digcount个.再减去诸如11,22...111...2222等重复项.
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
