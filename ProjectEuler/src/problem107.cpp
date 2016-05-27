#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <cassert>

static const int IntMax = std::numeric_limits<int>::max();
static const int GraphSize = 40;

template <class Ty>
class HeapTmpl
{
public:
	typedef Ty Type;
	typedef typename Type::KeyT KeyT;
	void Create(const std::vector<Ty>& line)
	{
		heap_.assign(line.begin(), line.end());
		std::make_heap(heap_.begin(), heap_.end(), std::greater<Ty>());
	}
	bool Contains(const Ty& _Val)const
	{
		return heap_.end() != std::find(heap_.begin(), heap_.end(), _Val);
	}
	int Search(int pos)
	{
		int tmp = std::distance(heap_.begin(), std::find(heap_.begin(), heap_.end(), pos));
		return tmp >= int(heap_.size()) ? -1 : tmp;
	}
	Ty ExactMin()
	{
		std::pop_heap(heap_.begin(), heap_.end(), std::greater<Ty>());
		Ty result = heap_.back();
		heap_.pop_back();
		return result;
	}
	Ty At(int pos)const 
	{
		return heap_.at(pos);
	}
	Ty Peek(int pos)const
	{
		return heap_[pos];
	}
	bool Empty()const
	{
		return heap_.empty();
	}
	bool Valid()const
	{
		return std::is_heap(heap_.begin(), heap_.end(), std::greater<Ty>());
	}
	void Decrease(int pos, const KeyT& val)
	{	// STL heap starts from 0, not 1.
		Ty& tmp = heap_[pos];
		assert(tmp.GetKey() > val);
		tmp.Copy(val);
		for(; pos > 0 && heap_[((pos - 1) / 2)] > heap_[pos]; pos = (pos - 1) / 2)
			std::swap(heap_[((pos - 1) / 2)], heap_[(pos)]);
	}
private:
	std::vector<Ty> heap_;
};

struct Node
{
	explicit Node(int _Pos, int _Key = IntMax) : position(_Pos), key(_Key){}
	bool operator > (const Node& other)const
	{
		return key > other.key;
	}
	bool operator == (const int _Pos)const
	{
		return _Pos == position;
	}
	typedef int KeyT;
	void Copy(const KeyT& _NewKey)
	{
		key = _NewKey;
	}
	const KeyT& GetKey()const
	{
		return key;
	}
	int position;
	KeyT key;
};

template <class Ty>
class MapTmpl
{
public:
	MapTmpl(int size = GraphSize)
	{
		map_size_ = size;
		map_.resize(size * size, IntMax);
	}
	int& at(int row, int col){ return map_[row * map_size_ + col]; }
	int accumulate()const
	{
		return std::accumulate(map_.begin(), map_.end(), Ty(), func);
	}
private:
	static int func(Ty tmp1, Ty tmp2)
	{
		return tmp2 != IntMax ? tmp1 + tmp2 : tmp1;
	}
	std::vector<Ty> map_;
	int map_size_;
};

typedef MapTmpl<int> Map;
typedef HeapTmpl<Node> Heap;
static int Read(Map* result)
{
	const char* filename = "network.txt";
	int line = 0;
	for(std::ifstream ifs(filename); ifs && line < GraphSize; ++line)
	{
		char buffer[256] = { 0 };
		ifs.getline(buffer, _countof(buffer));
		int col = 0;
		std::stringstream ss(buffer);
		for(; col < GraphSize; ++col)
		{
			int tmp = IntMax;
			ss >> tmp;
			if(ss.fail())
				ss.clear();
			result->at(line, col) = tmp;
			ss.ignore();
		}
	}
	return result->accumulate() / 2;
}

static void InitHeap(Heap* result)
{
	std::vector<Heap::Type> vec;
	vec.reserve(GraphSize);
	for(int i = 0; i < GraphSize; ++i)
		vec.push_back(Node(i));

	result->Create(vec);
}

int solve_107()
{
	Map matrix;
	int total = Read(&matrix);

	Heap heap;
	InitHeap(&heap);

	heap.Decrease(0, 0);
	assert(heap.Valid());
	int result = 0;
	while(!heap.Empty())
	{
		Node min = heap.ExactMin();
		result += min.key;
		const int line = min.position;
		for(int i = 0; i < GraphSize; ++i)
		{
			if(i == line) continue;	// itself.
			int tmp = matrix.at(line, i);
			int pos = heap.Search(i);
			if(pos != -1 && tmp < heap.At(pos).key)
				heap.Decrease(pos, tmp);
		}
	}

	return (total - result);
}
