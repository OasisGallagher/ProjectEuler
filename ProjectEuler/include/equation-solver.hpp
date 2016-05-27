#pragma once

#include <vector>
#include <cmath>
// TODO: 没有加入无解情况的处理.
class EquationSolver
{
public:
	typedef double Number;
	typedef std::vector<Number> Vector;
	typedef std::vector<Vector> Matrix;
	EquationSolver(){}

	void Initialize(const Matrix& elem)
	{
		const int size = elem.size();
		std::copy(elem.begin(), elem.end(), std::back_inserter(element_));
	}

	void SolveFunc(const Vector& b, Vector* result)
	{
		EquationSolver L, U;
		Vector P;
		lupDecomposition(&P, &L, &U);

		Vector tmpY(row(), 0);
		for(int i = 0; i < row(); ++i)
		{
			double tmp = 0;
			for(int j = 0; j < i; ++j)
				tmp += L.element_[i][j] * tmpY[j];
			tmpY[i] = (b[int(P[i])] - tmp);
		}

		result->resize(row(), 0);
		for(int i = row() - 1; i >= 0; --i)
		{
			double tmp = 0;
			for(int j = i + 1; j < row(); ++j)
				tmpY[i] -= U.element_[i][j] * result->at(j);

			result->at(i) = tmpY[i] / U.element_[i][i];
		}
	}
private:
	void allocate(int rowCount, int colCount)
	{
		element_.clear();
		element_.resize(rowCount);
		for(int i = 0; i < rowCount; ++i)
			element_[i].resize(colCount);
	}

	void lupDecomposition(Vector* P, EquationSolver* L, EquationSolver* U)
	{	// PA = LU.
		Vector replace;
		initReplaceVertex(&replace);

		for(int k = 0, p = 0; k < row(); ++k)
		{	// 按列查找绝对值最大的数作为主元.
			int rowIndex = colMaxAbs(k);
			std::swap(replace[rowIndex], replace[k]);

			// 整行进行交换.
			std::swap(element_[rowIndex], element_[k]);

			// 计算从(k + 1, k + 1)开始的Schur补.
			schur(k);
		}

		// 构造L, U.
		P->assign(replace.begin(), replace.end());
		buildPLU(L, U);
	}
	void initReplaceVertex(Vector* replace)
	{
		// 构造对角线是1的置换矩阵.
		replace->resize(row());
		for(int i = 0; i < row(); ++i)
			replace->at(i) = i;
	}
	int colMaxAbs(int fromCol)
	{	// 起始位置的行和列是相等的,所以这里参数写为了fromCol.
		double maxAbs = 0.0;
		int whichRow = fromCol;
		int fromRow = fromCol;
		for(; fromRow < row(); ++fromRow)
		{
			double tmp = abs(element_[fromRow][fromCol]);
			if(tmp > maxAbs)
				maxAbs = tmp, whichRow = fromRow;
		}
		if(maxAbs == 0.0) throw "singluar matrix";
		return whichRow;
	}

	void schur(int base)
	{
		for(int i = base + 1; i < row(); ++i)
		{
			element_[i][base] /= element_[base][base];
			for(int j = base + 1; j < row(); ++j)
				element_[i][j] -= element_[i][base] * element_[base][j];
		}
	}

	void buildPLU(EquationSolver* L, EquationSolver* U)
	{
		L->allocate(row(), row());
		U->allocate(row(), row());

		// 构造L.
		for(int i = 0; i < row(); ++i)
		{
			for(int j = 0; j <= i; ++j)
				L->element_[i][j] = (i == j) ? 1 : element_[i][j];
		}

		// 构造U.
		for(int i = 0; i < column(); ++i)
		{
			for(int j = 0; j <= i; ++j)	// 拷贝矩阵的上半部分,含对角线.
				U->element_[j][i] = element_[j][i];
		}
	}
	inline bool empty()const
	{
		return element_.empty();
	}
	inline int row()const 
	{
		return element_.size();
	}
	inline int column()const
	{
		if(empty()) throw "empty matrix";
		return element_[0].size();
	}
	Matrix element_;
};
