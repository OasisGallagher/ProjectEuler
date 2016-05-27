# http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation

def largestX(p, c):
	x = 1
	while Formula(x, p) <= c:
		x = x + 1
	return x - 1

def Formula(x, p):
	return x * ((20 * p) + x)

def strSqrt(number):
	result = ""
	c = number
	p = 0
	x = largestX(p, c)
	while c != 0:
		result += str(x)
		if len(result) == 100:
			break
		c = (c - Formula(x, p)) * 100
		p = p * 10 + x
		x = largestX(p, c)
	return result

from math import sqrt
total = 0
for i in range(2, 101):
	tmp = int(sqrt(i))
	if tmp * tmp == i:
		continue
	sr = strSqrt(i)
	for j in sr:
		total += int(j)
print total
