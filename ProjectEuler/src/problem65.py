# Cos' C++ doesn't have BigInteger and it's boring to write it by myself.
def get():
	d = 2
	n = 3
	for i in range(3,101):
		c = 1
		if i % 3 == 0:
			c = (2 * i / 3);
		tmp = d
		d = n
		n = tmp + n * c
	result = 0
	for i in str(n):
		result += int(i)
	return result

print get()
input("""press "enter" to continue...""")
