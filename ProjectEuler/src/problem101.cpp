//(拉格朗日插值)Lagrange interpolation.
#include <vector>
#include <cassert>
typedef std::vector<__int64> Vector;
template<class ReturnType>
ReturnType Power(int x, int e)
{
	return e <= 0 ? 1 : (x * Power<ReturnType>(x, e - 1));
}

static __int64 Basic(int x, int except, const Vector& vec)
{
	const int size = vec.size();
	__int64 tmp1 = 1, tmp2 = 1;
	for(int i = 0; i < size; ++i)
	{
		if(i != except)
		{
			tmp1 *= (x - (i + 1));
			tmp2 *= ((except + 1) - (i + 1));
		}
	}
	assert(tmp1 % tmp2 == 0);
	return tmp1 / tmp2;
}

static __int64 GetInvalidNumber(const Vector& vec)
{
	__int64 result = 0;
	const int size = vec.size();
	for(int i = 0; i < size; ++i)
	{
		result += vec[i] * Basic(size + 1, i, vec);
	}
	return result;
}

static __int64 GetNext(int x)
{
	return (Power<__int64>(x, 11) + 1) / (1 + x);
}

__int64 solve_101()
{
	Vector b(1, 1);
	__int64 result = 1;
	for(int i = 1; i < 10; ++i)
	{
		b.push_back(GetNext(i + 1));
		//__int64 tmp = GetInvalidNumber(b);
		//std::cout << tmp << std::endl;
		result += GetInvalidNumber(b);
	}

	return result;
}

// LUP解方程.
#if 0
#include "equation-solver.hpp"
template<class ReturnType>
ReturnType Power(int x, int e)
{
	return e <= 0 ? 1 : (x * Power<ReturnType>(x, e - 1));
}
static __int64 GetInvalidNumber(const EquationSolver::Vector& b)
{
	EquationSolver::Matrix elem;
	const int count = b.size();
	elem.reserve(count);

	for(int i = 0; i < count; ++i)
	{
		EquationSolver::Vector vec;
		for(int j = 0; j < count; ++j)
			vec.push_back(Power<EquationSolver::Number>(i + 1, j));
		elem.push_back(vec);
	}

	EquationSolver matrix;
	matrix.Initialize(elem);
	EquationSolver::Vector result;
	matrix.SolveFunc(b, &result);

	__int64 next_value = 0;
	double discard = 0.0;
	for(int i = 0; i < count; ++i)
	{
		double tmp = (Power<EquationSolver::Number>(count + 1, i) * result[i]);
		next_value += (__int64)tmp;
		discard += (tmp - (__int64)tmp);
	}
	return __int64(next_value + discard);
}

static __int64 GetNext(int x)
{
	__int64 tmp = Power<__int64>(x, 11) + 1;
	return (tmp) / (1 + x);
}

__int64 solve_101()
{
	__int64 result = 0;
	EquationSolver::Vector b;
	for(int i = 0; i < 10; ++i)
	{
		b.push_back((EquationSolver::Number)GetNext(i + 1));
		__int64 tmp = GetInvalidNumber(b);
		/*std::cout << i << ": " << tmp << std::endl;*/
		result += tmp;
	}
	return result;
}
#endif