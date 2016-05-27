#pragma once

#include <cmath>	// std::ceil().
#include <xutility>	// std::fill().
#include <cassert>	// std::assert().

class VisitMatrix
	{
public:
	VisitMatrix(int row, bool val = false) :row_(row){ init(val); }
	~VisitMatrix(){ finalize(); }
	bool operator()(int left, int right)const;
	void set(int left, int right);
	void clear(int left, int right);
private:
	struct col_t
		{
		col_t(int m, int s) : main(m), sub(s) { }
		int main;
		int sub;
		};
	void init(bool val);
	void finalize();
	col_t column(int n)const { return col_t(n / 32, n % 32); }
	unsigned** matrix_;
	int row_;
	int col_;
	};
//
inline
void VisitMatrix::init(bool val)
	{
	// assert(sizeof(unsigned) == 32);
	col_ = (int)std::ceil(row_ / 32.0);
	unsigned fillVal = val ? 0xFFFFFFFF : 0;
	matrix_ = new unsigned*[row_];
	for(int i = 0; i < row_; ++i)
		{
		matrix_[i] = new unsigned[col_];
		std::fill(matrix_[i], matrix_[i] + col_, fillVal);
		}
	}
//
inline
void VisitMatrix::finalize()
	{
	for(int i = 0; i < row_; ++i)
		delete[] matrix_[i];
	delete[] matrix_;
	}
// If (left, right) is visited.
inline
bool VisitMatrix::operator ()(int left, int right)const
	{
	col_t col = column(right);
	return ((matrix_[left][col.main] & (1 << col.sub)) != 0);
	}
// Set (left, right) to be visited.
inline
void VisitMatrix::set(int left, int right)
	{
	assert(left < row_ && right < row_);
	col_t col = column(right);
	matrix_[left][col.main] |= (1 << col.sub);
	}
// Clear the flag at (left, right).
inline
void VisitMatrix::clear(int left, int right)
	{
	assert(left < row_ && right < row_);
	col_t col = column(right);
	matrix_[left][col.main] &= ~(1 << col.sub);
	}
