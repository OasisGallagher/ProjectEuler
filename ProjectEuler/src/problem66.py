# see ./pe66.pdf for more details

from math import sqrt
class fac_t:
	def __init__(self):
		self.numerator = 0
		self.denominator = 1

def add(number, fac):
	fac.numerator += (number * fac.denominator)

def reciprocal(fac):
	tmp = fac.numerator
	fac.numerator = fac.denominator
	fac.denominator = tmp

def nextM(d, a, m):
	return int(d * a - m)

def nextD(S, m, d):
	return int((S - m * m) / d)

def nextA(a0, m, d):
	return int((a0 + m) / d)

def doGetResult():
	result = 0
	lagestD = 0

	for S in range(2, 1001):
		a = int(sqrt(S))
		if a * a == S:
			continue

		vec = []
		fac = fac_t()
		m = 0
		d = 1
		a0 = a
		count = 1
		vec.append(a)

		m = nextM(d, a, m)
		d = nextD(S, m, d)
		a = nextA(a0, m, d)
		vec.append(a)
		while a != 2 * a0:
			count += 1
			m = nextM(d, a, m)
			d = nextD(S, m, d)
			a = nextA(a0, m, d)
			vec.append(a)
		vec.pop()

		if(count % 2 != 0):
			tmp = vec[:]
			for i in tmp:
				vec.append(i)
	
		length = len(vec)
		for i in range(length - 1, -1, -1):
			add(vec[i], fac)
			reciprocal(fac)
		reciprocal(fac)
		if(result < fac.numerator):
			result = fac.numerator
			lagestD = S
	return lagestD

print "the result of this problem is %d" % doGetResult()

