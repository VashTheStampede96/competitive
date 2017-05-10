#include<bits/stdc++.h>

/*
 * Make/Union/Find data structure.
 * Supports classic MUF problem, with keys in [0, n)
 */

class union_find {
private:
	std::vector<int> __parent, __weight;

public:
	union_find(int);

	void Make(int);
	void Union(int, int);
	int Find(int);
	
};

union_find:: union_find(int n)
{
	__parent.reserve(n);
	__weight  .reserve(n);
	
	for(int i=0; i<n; ++i)
		Make(i);
}

void union_find:: Make(int a)
{
	__parent.push_back(a);
	__weight.push_back(0);
}

void union_find:: Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if(a != b) {
		if(__weight[a] < __weight[b])
			std::swap(a, b);
		if(__weight[a] == __weight[b])
			++__weight[a];
		__parent[b] = a;
	}
}

int union_find:: Find(int a)
{
	while(__parent[a] != a)
		a = __parent[a];
	return a;
}

/*
 * Driver program:
 * 0 -> Make next element
 * 1 -> Union
 * 2 -> Find
 */

int main()
{
	int n, q;
	std::cin >> n >> q;

	union_find ufds(n);

	for(int i=0, x=n; i<q; ++i) {
		int t;
		std::cin >> t;
		if(t == 0) {
			ufds.Make(x++);
		}else if(t == 1) {
			int a, b;
			std::cin >> a >> b;
			ufds.Union(a, b);
		}else {
			int a;
			std::cin >> a;
			std::cout << ufds.Find(a) << "\n";
		}
	}
	
	return 0;
}
