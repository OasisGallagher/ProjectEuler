#include <iostream>
#include <vector>
// cast int to bool, signed unsigned mismatch.
#pragma warning(disable:4800)
#undef Packing

typedef std::vector<int> Container;
typedef std::pair<int, int> Range;
struct Line {
#ifdef Packing
	Container line;
#endif
	Range range;
};

typedef std::vector<Line> Matrix;

// www.gottfriedville.net/mathprob/comb-subrect.html
// how to count rectangles.
static unsigned CountRect(const Matrix& cont) {
	struct Helper {
		static bool CombineRange(const Range& r1, const Range& r2, Range* result) {
			if(!ChkRange(r1) || !ChkRange(r2)) return false;

			Range::first_type f = std::max(r1.first, r2.first);
			Range::second_type s = std::min(r1.second, r2.second);
			if(f <= s) {
				result->first = f, result->second = s;
				return true;
			}
			return false;
		}
		static bool ChkRange(const Range& range) {
			return range.first <= range.second;	
		}

		static unsigned CountInRange(const Range& range) {
			unsigned dist = range.second - range.first;
			return (dist + 1) * dist / 2;
		}
	};

	unsigned result = 0;
	typedef int Size;
	Size size = cont.size();
	for(Size i = 0; i < size; ++i) {
		const Line& cur = cont[i];
		Range range = cur.range;
		result += Helper::CountInRange(range);

		for(int j = i - 1; j >= 0; --j) {
			const Line& prev = cont[j];
			if(!Helper::CombineRange(range, prev.range, &range))
				break;
			result += Helper::CountInRange(range);
		}
	}

	return result;
}

static unsigned CountRectangle(int length, int height, Matrix* cont) {
	if(!cont->empty()) cont->clear();

	cont->resize(height);
	for(Matrix::iterator ite = cont->begin(); ite != cont->end(); ++ite) {
#ifdef Packing
		ite->line.resize(length, 1);
#endif
		ite->range.first = 0;
		ite->range.second = length;
	}

	return CountRect(*cont);
}

static unsigned CountSlopRect(int length, int height, Matrix* cont) {
	struct Helper {
		static int Parse(int val) {
			return (val < 0) ? -1 : bool(val);
		}
		static unsigned CountUnitRect(int left, int right, Matrix* cont) {
			return std::max(left, right);
		}
		static unsigned CountNoneUnitRect(int left, int right, Matrix* cont) {
			int maxvalue = left + right;

			Line tmp;
#ifdef Packing
			tmp.line.resize(maxvalue);
#endif
			int pos = left - 1;
#ifdef Packing
			tmp.line[pos] = 1;
			tmp.line[pos + 1] = 1;
#endif
			tmp.range.first = pos;
			tmp.range.second = pos + 2;
			cont->push_back(tmp);

			int cur = 2;
			do {
#ifdef Packing
				tmp.line.clear();
				tmp.line.resize(maxvalue);
#endif
				cur += Helper::Parse(--left);
				pos += left == 0 ? 0 : left > 0 ? -1 : 1;

				cur += Helper::Parse(--right);
#ifdef Packing
				for(int i = 0; i < cur; ++i)
					tmp.line[pos + i] = 1;
#endif
				tmp.range.first = pos;
				tmp.range.second = pos + cur;

				cont->push_back(tmp);
			} while (cur != 2);

			return CountRect(*cont);
		}
	};

	if(!cont->empty()) cont->clear();
	unsigned result = 0;
	int left = height - 2 + 1;
	int right = length - 2 + 1;
	if(length < 2 || height < 2)
		result = Helper::CountUnitRect(left, right, cont);
	else
		result = Helper::CountNoneUnitRect(left, right, cont);
	return result;
}

int main() {
	Matrix cont;
	unsigned result = 0;
	for(int i = 1; i <= 47; ++i) {
		for(int j = 1; j <= 43; ++j) {
			unsigned __tmp = 0;
			__tmp += CountRectangle(i, j, &cont);

			__tmp += CountSlopRect(i, j, &cont);

			result += __tmp;

			//printf("(%d * %d) contains %u result(s).\n", i, j, __tmp);
		}
	}
	printf("%d results in total.\n", result);
	return 0;
}
