#include <fstream>
#define FileName	"triangles102.txt"
// 使用向量的叉积.
class Triangle
{
public:
	class Point;
	Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		_point[0]._x = x1, _point[0]._y = y1, _point[1]._x = x2,
		_point[1]._y = y2, _point[2]._x = x3, _point[2]._y = y3;
		//sort3();
	}
	bool PtInTriangle(const Point& point)const
	{
		bool suk = sunken();
		for(int i = 1; i < 4; ++i)
		{
			if(suk != distance(_point[i - 1], _point[i % 3], point))
				return false;
		}
		return true;
	}
	class Point
	{
	public:
		Point(int x, int y):_x(x), _y(y){}
		Point(){}
		bool operator > (const Point& other)const
		{
			return _x != other._x ? _x > other._x : _y > other._y;
		}
		Point& operator -=(const Point& other)
		{
			_x -= other._x;
			_y -= other._y;
			return *this;
		}
		int _x;
		int _y;
	};
private:
	/*void sort3()
	{
		if(_point[0] > _point[1]) std::swap(_point[0], _point[1]);
		if(_point[0] > _point[2]) std::swap(_point[0], _point[2]);
		if(_point[1] > _point[2]) std::swap(_point[1], _point[2]);
	}*/
	bool distance(Point base, Point pt1, Point pt2)const
	{
		// 计算叉积,判断pt1是否在pt2的相对于base的顺时针方向.
		pt1 -= base;
		pt2 -= base;
		return (pt1._x * pt2._y - pt1._y * pt2._x) > 0;
	}
	bool sunken()const
	{	// 对于该三角形,所判定的点应该在第一个向量的顺时针方向(false)还是逆时针方向(true).
		// 其它两个向量和第一个是一致的.
		return distance(_point[0], _point[1], _point[2]);
	}
	Point _point[3];
};

int solve_102()
{
	int count = 0;

	for(std::ifstream ifs(FileName); ifs; )
	{
		int arr[6];
		for(int i = 0; i < 6; ++i)
		{
			ifs >> arr[i];
			ifs.ignore();
		}

		Triangle t(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
		count += t.PtInTriangle(Triangle::Point(0, 0));
	}

	return count;
}
