#pragma once

#include <vector>
#include <cmath>
// TODO: û�м����޽�����Ĵ���.
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
		{	// ���в��Ҿ���ֵ��������Ϊ��Ԫ.
			int rowIndex = colMaxAbs(k);
			std::swap(replace[rowIndex], replace[k]);

			// ���н��н���.
			std::swap(element_[rowIndex], element_[k]);

			// �����(k + 1, k + 1)��ʼ��Schur��.
			schur(k);
		}

		// ����L, U.
		P->assign(replace.begin(), replace.end());
		buildPLU(L, U);
	}
	void initReplaceVertex(Vector* replace)
	{
		// ����Խ�����1���û�����.
		replace->resize(row());
		for(int i = 0; i < row(); ++i)
			replace->at(i) = i;
	}
	int colMaxAbs(int fromCol)
	{	// ��ʼλ�õ��к�������ȵ�,�����������дΪ��fromCol.
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

		// ����L.
		for(int i = 0; i < row(); ++i)
		{
			for(int j = 0; j <= i; ++j)
				L->element_[i][j] = (i == j) ? 1 : element_[i][j];
		}

		// ����U.
		for(int i = 0; i < column(); ++i)
		{
			for(int j = 0; j <= i; ++j)	// ����������ϰ벿��,���Խ���.
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
