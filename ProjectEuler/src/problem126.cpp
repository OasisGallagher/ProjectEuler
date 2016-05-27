#include <algorithm>
#include <vector>

struct Cubiod
{
	Cubiod(int L, int W, int H)
	{
		perimeter = L + W + H;
		aera = L * W + L * H + W * H;
	}
	int perimeter;
	int aera;
};

static int GetCount(int L, int W, int H, int Layer)
{	// See ../pe126-1st-layer.png, ../pe126-2nd-layer.png, ../pe126-3rd-layer.png.
	Cubiod cubiod(L, W, H);
	return cubiod.aera * 2 + (cubiod.perimeter + Layer - 2) * 4 * (Layer - 1);
}

int solve_126()
{
	for(int gusss = 1024; gusss < INT_MAX / 2; gusss *= 2)
	{
		std::vector<int> buffer(gusss);
		// Let len <= width <= height.
		for(int len = 1; GetCount(len, len, len, 1) < gusss; ++len)
			for(int width = len; GetCount(len, width, len, 1) < gusss; ++width)
				for(int height = width; GetCount(len, width, height, 1) < gusss; ++height)
					for(int layer = 1; GetCount(len, width, height, layer) < gusss; ++layer)
						++buffer[GetCount(len, width, height, layer)];

		std::vector<int>::difference_type diff =  std::distance(buffer.begin(), std::find(buffer.begin(), buffer.end(), 1000));
		if(diff < gusss)
			return diff;
	}
	return -1;
}
