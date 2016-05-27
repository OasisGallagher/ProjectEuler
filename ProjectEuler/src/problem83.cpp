// See ./a-star-pathfinding-for-beginners.pdf for an A-Star tutorial.
// A* and dijkstra algorithm.
// Difference: from http://www.aiqus.com/questions/2273/difference-between-a-and-dijkstras-shortest-path-algorithm
// Actually, Dijkstra is a particular case of A* with the heuristic H set to always return 0.
// A* (f) uses two algorithms to balance each other:
// (g) - Favouring paths closest to start point (Dijkstra's shortest path)
// (h) - Favouring paths closest to end point (Best First Search)
// This is what makes up the elements of f(n) = g(n) + h(n). 
//Therefore if your h=0, then f(n) becomes g(n) or it becomes Dijkstra's algorithm.
//If your h='arbitrarily large number' then g(n) essentially gets ignored due to scale and 
//A becomes Best First Search. By having a heuristic that is admissible and at the same scale 
//as the path cost, it gives A the power to balance them both out and make a fast directed shortest path algorithm!
//
//自己的理解是这样的，对于下面的查找：
//			4
//		a	--	b
//	2	|       | 2
//		c		d
//	100  \      | 4
//		   e    f
//		  3 \  / 6
//		      g
// 起点在a，终点在g。
//如果采用的是dijkstra算法，起点在a，更新a的邻接表中，b的估计值变为4，c的估计值是2，所以下一个选择到的
//是c点。
//更新c的临界表，e的估计值变为102。
//此时选出b点，更新d的估计值为6，更新f为10，更新g为16，更新e为19，c不用再更新，因为c的估计值是2。
//队列中还有e，再继续更新，最后，各项的估计值，都是从a出发到这里的最短距离。也就是说，求出了所有的点的。
//然而，如果只需要知道a～g，那么用A*就更合适。
//假设H值为到g的边数，那么，更新a的，b的F值变为4 + 1 = 5，c的变为2 + 1 = 3。
//选择c，e的F值变为104。
//此时openlist中，有e(104)，b(5)，选择b，一路下去，可以一直到g。
//再更新g时，g被放到closelist中，检测到这一点，算法就结束了。
//实际上，这样的过程中，e点没被访问到，因为c到e的距离太大了。
//所以，对于这种求单个点的，A*更适合。
//
#include <queue>
#include <iostream>
#include <fstream>

typedef std::vector<int> Array;
#define Row(n)				(n / Size)	// For both.
#define Col(n)				(n % Size)	// For both.
#define Index(row, col)		((row) * Size + (col))	// For both.
enum { NoElementInQueue = -1,  Size = 80, Infinite = INT_MAX, EleCount = Size * Size};	// For both.
enum Locale{ Free, OpenList, CloseList };	// For A*

struct Estimator						// For dijkstra.
	{
	Estimator(){ est = Infinite; inQueue = true; }
	int est;
	bool inQueue; 
	};

struct Node								// For A*
	{
	Node(int iG, int iH, int iValue, Locale eLocal = Free)
		: G(iG), H(iH), Val(iValue), loc(eLocal){}
	int G;
	int H;
	int Val;
	Locale loc;
	};

static std::vector<Node> chessboard;	// For A*
static Array graph;						// For both.

typedef std::vector<Estimator> EArray;	// For dijkstra.
static EArray estimators;				// For dijkstra.

static int readArray(Array* arr)		// For both.
	{
	int min = Infinite;
	std::ifstream ifs("matrix.txt");
	for(std::ifstream ifs("matrix.txt"); ifs; )
		{
		int integer;
		ifs >> integer;
		arr->push_back(integer);
		ifs.ignore();
		if(min > integer) min = integer;
		}
	return min;
	}

static int relax(int vetex, int cur)	// For dijkstra.
	{
	if(estimators[vetex].est > estimators[cur].est + graph[vetex])
		estimators[vetex].est = estimators[cur].est + graph[vetex];
	return estimators[vetex].est;
	}

static int minElement(EArray& earray)	// For dijkstra.
	{
	int result = -1;
	int minVal = Infinite;

	for(int i = 0; i < (int)earray.size(); ++i)
		if(earray[i].est < minVal && earray[i].inQueue)
			minVal = earray[i].est, result = i;
	return result;
	}

static void initAStar()				// For A*.
	{
	chessboard.reserve(EleCount);
	graph.reserve(EleCount);

	int min = readArray(&graph);

	for(size_t i = 0; i < EleCount; ++i)
		chessboard.push_back(Node(0, min * (Col(i) + Row(i)), graph[i]));

	chessboard[0].G = graph[0];
	}

static void aStarRelax(int iAdj, int cur)	// For A*.
	{
	if(chessboard[iAdj].loc == CloseList) return;
	// Check if it's better if we use the current node(cur) to get there(iAdj).
	if(chessboard[iAdj].loc == OpenList)
		{
		if(chessboard[iAdj].G > chessboard[cur].G + chessboard[iAdj].Val)
			chessboard[iAdj].G = chessboard[cur].G + chessboard[iAdj].Val; 
		}
	else	// Node is not in open list already.
		{
		chessboard[iAdj].loc = OpenList;
		chessboard[iAdj].G = chessboard[cur].G + chessboard[iAdj].Val;
		}
	}

static int aStarLowestFValueInOpenList()	// For A*.
	{
	int curF = Infinite;
	int result = -1;
	for(size_t i = 0; i < EleCount; ++i)
		{
		if(chessboard[i].loc != OpenList) continue;
		int tmp = (chessboard[i].G + chessboard[i].H);
		if(curF > tmp)
			curF = tmp, result = i;
		}

	return result;
	}

// 5 seconds.
static int aStar()	// For A*.
	{	// Fail to find the target square (chessboard[EleCount - 1].loc != CloseList),
		// and the open list is empty	 (cur = -1).
		// In this case, there is no path.
	initAStar();
	for(int cur = 0; chessboard[EleCount - 1].loc != CloseList; cur = aStarLowestFValueInOpenList())
		{
		chessboard[cur].loc = OpenList;
		//chessboard[cur].loc = CloseList; // It's OK to place this line here too.
		if(Col(cur) > 0) aStarRelax(Index(Row(cur), Col(cur) - 1), cur);
		if(Col(cur) < Size - 1) aStarRelax(Index(Row(cur), Col(cur) + 1), cur);
		if(Row(cur) > 0) aStarRelax(Index(Row(cur) - 1, Col(cur)), cur);
		if(Row(cur) < Size - 1) aStarRelax(Index(Row(cur) + 1, Col(cur)), cur);

		chessboard[cur].loc = CloseList;
		}
	return chessboard[EleCount - 1].G;
	}

// 8 seconds.
static int dijkstra()	// For dijkstra.
	{
	graph.reserve(EleCount);
	readArray(&graph);

	estimators.resize(EleCount);
	estimators[Index(0, 0)].est = graph[Index(0, 0)];

	for(int cur = Index(0, 0); cur != NoElementInQueue; cur = minElement(estimators))
		{
		estimators[cur].inQueue = false;

		if(Row(cur) > 0)
			relax(Index(Row(cur) - 1, Col(cur)), cur);
		
		if(Row(cur) < Size - 1)
			relax(Index(Row(cur) + 1, Col(cur)), cur);

		if(Col(cur) > 0)
			relax(Index(Row(cur), Col(cur) - 1), cur);

		if(Col(cur) < Size - 1)
			relax(Index(Row(cur), Col(cur) + 1), cur);
		}

	return estimators[EleCount - 1].est;
	}

int solve_83()
	{
	//return dijkstra();
	return aStar();
	}

#if 0
// Dijkstra algorithm..
// In this version, I care too much about the algorithm itself.
// Instead, the version above use a global array which performs much better
// than allocate memory from heap.
// 288 seconds ! 

#include <vector>
#include <algorithm>
#include <queue>

static const int LEN = 80;
typedef std::vector<std::vector<int> > Matrix;
extern void ReadMatrix(Matrix* matrix);

enum {Left, Up, Right, Down, AdjCount};

struct Node
	{
	const int val;
	int estimator;

	Node* adj[AdjCount];
	Node(int iVal, int iEstimator) : val(iVal), estimator(iEstimator)
		{
		memset(adj, NULL, sizeof(Node*) * AdjCount);
		}
	};

struct compHeap : public std::binary_function<Node*, Node*, bool> 
	{
	bool operator ()(Node* left, Node* right) const
		{
		return left->estimator > right->estimator;
		}
	};

struct PriorityQueue : public std::priority_queue<Node*, std::vector<Node*>, compHeap>
	{
	void rebuild() { std::make_heap(c.begin(), c.end(), comp); }
	};

static bool nodePtrComp(Node* left, Node* right)
	{
	return left->estimator < right->estimator;
	}

Node* buildPriorityQueue(const Matrix& matrix, PriorityQueue* queue)
	{
	std::vector<Node*> nodes;
	for(Matrix::const_iterator ite = matrix.begin(); ite != matrix.end(); ++ite)
		for(Matrix::value_type::const_iterator ite2 = ite->begin(); ite2 != ite->end(); ++ite2)
			nodes.push_back(new Node(*ite2, INT_MAX));

	for(std::vector<Node*>::size_type i = 0; i < nodes.size(); ++i)
		{
		const int row = i / LEN;
		const int col = i % LEN;

		if(col > 0) nodes[i]->adj[Left] = nodes[row * LEN + (col - 1)];			// Left.
		if(row > 0) nodes[i]->adj[Up] = nodes[(row - 1) * LEN + col];			// Up.
		if(col < LEN - 1) nodes[i]->adj[Right] = nodes[row * LEN + (col + 1)];	// Right.
		if(row < LEN - 1) nodes[i]->adj[Down] = nodes[(row + 1) * LEN + col];	// Down.
		}
	nodes[0]->estimator = matrix[0][0];

	for(std::vector<Node*>::iterator ite = nodes.begin(); ite != nodes.end(); ++ite)
		queue->push(*ite);

	return nodes.back();
	}

// Standard dijkstra algorithm from <Introduction to Algorithms>.
int solve_83()
	{
	int result = 0;
	Matrix matrix;
	ReadMatrix(&matrix);
	PriorityQueue queue;
	Node* dest = buildPriorityQueue(matrix, &queue);

	std::vector<Node*> save;
	while(!queue.empty())
		{
		Node* cur = queue.top();
		save.push_back(cur);
		queue.pop();

		for(int i = Left; i < AdjCount; ++i)
			{
			Node* vetex = cur->adj[i];
			if(vetex != NULL)
				{
				// Node: the heap is corrupted.
				// Relaxation.
				int weight = vetex->val;
				if(vetex->estimator > cur->estimator + weight)
					vetex->estimator = cur->estimator + weight;
				}
			}
		if(cur == dest)
			result =  cur->estimator;

		// Rebuild heap.
		queue.rebuild();
		}
	for(std::vector<Node*>::iterator ite = save.begin(); ite != save.end(); ++ite)
		delete *ite;
	return result;
	}
#endif
